#include<iostream>
#include<thread>
#include<mutex>

int a = 0;
std::timed_mutex mtx;

void func() {
	for (int i = 0;i < 2;i++) {
		//std::unique_lock<std::mutex> lg(mtx);

		//std::unique_lock<std::mutex> lg(mtx, std::defer_lock);//构造函数什么都不做，加锁需要手动调用，可以自动unlock
		//lg.lock();

		std::unique_lock<std::timed_mutex> lg(mtx, std::defer_lock);
		//lg.try_lock_for(std::chrono::seconds(5));//尝试加锁，成功返回true，失败返回false
		if (lg.try_lock_for(std::chrono::seconds(2))) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			a++;
		}
		
		
	} 
}

int main() {
	std::thread t1(func);
	std::thread t2(func);
	t1.join();
	t2.join();

	std::cout << a << std::endl;

	return 0;
}