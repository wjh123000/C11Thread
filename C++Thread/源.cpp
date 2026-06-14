#include<iostream>
#include<thread>
#include<mutex>

std::mutex m1,m2;

void func_1() {
	for (int i = 1;i <= 50;i++) {
		m1.lock();
		m2.lock();
		m1.unlock();
		m2.unlock();
	}
	
}

void func_2() {
	for (int i = 1;i <= 50;i++) {
		m1.lock();
		m2.lock();
		m1.unlock();
		m2.unlock();
	}
	
}

int main() {
	std::thread t1(func_1);
	std::thread t2(func_2);
	t1.join();
	t2.join();

	std::cout << "over" << std::endl;

	return 0;
}