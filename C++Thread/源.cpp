#include<iostream>
#include<thread>
#include<mutex>

int a = 0;
std::mutex mtx;

void func() {
	for (int i = 0;i < 10000;i++) {
		mtx.lock();
		a++;
		mtx.unlock();
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