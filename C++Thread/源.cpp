#include<iostream>
#include<thread>
#include<mutex>

int a = 1;
std::mutex mtx;

void func() {
	for (int i = 0;i < 10000;i++) {
		std::lock_guard<std::mutex> lg(mtx);
		a++;
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