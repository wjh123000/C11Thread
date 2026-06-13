#include <iostream>
#include <thread>

void printHelloWorld() {
	std::cout << "Hello World!" << std::endl;
}

int main() {
	//1.创建线程
	std::thread thread1(printHelloWorld);
	return 0;
}