#include<iostream>
#include<thread>
#include<mutex>
#include<string>
#include<condition_variable>
#include<queue>
#include<vector>
#include<functional>

std::mutex cout_mtx;

class ThreadPool {
public:
	ThreadPool(int numThreads) :stop(false) {
		for (int i = 0;i < numThreads;i++) {
			threads.emplace_back([this] {
				while (1) {
					std::unique_lock<std::mutex> lock(mtx);
					condition.wait(lock, [this] {
						return !tasks.empty()||stop;
					});
					if (stop && tasks.empty()) {
						return;
					}

					std::function<void()> task(std::move(tasks.front()));
					tasks.pop();
					lock.unlock();
					task();

				}
				});
		}
	}
	~ThreadPool() {
		{
			std::unique_lock<std::mutex> lock(mtx);
			stop = true;
		}
		condition.notify_all();
		for (auto& t : threads) {
			t.join();
		}
	}
	template<class F,class... Args>
	void enqueue(F&& f, Args&&... args) {
		std::function<void()>task=std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		{
			std::unique_lock<std::mutex> lock(mtx);
			tasks.emplace(std::move(task));
		}
		
		condition.notify_one();
	}
private:
	std::vector<std::thread> threads;
	std::queue<std::function<void()>> tasks;

	std::mutex mtx;
	std::condition_variable condition;

	bool stop;

};


int main() {
	ThreadPool pool(4);

	for (int i = 0;i < 10;i++) {
		pool.enqueue([i] {
			// 打印加锁，解决输出错乱
			std::lock_guard<std::mutex> lk(cout_mtx);
			std::cout << "Task " << i << " is running\n";
			});

		// 模拟任务耗时
		std::this_thread::sleep_for(std::chrono::seconds(1));

		pool.enqueue([i] {
			std::lock_guard<std::mutex> lk(cout_mtx);
			std::cout << "Task " << i << " is done\n";
			});
	}
	
	return 0;


}
