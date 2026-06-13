#include <iostream>
#include <thread>
#include <string>

void printHelloWorld(std::string msg) {
	std::cout << msg << std::endl;
}

int main() {
	//1.创建线程
	std::thread thread1(printHelloWorld,"Hello,Thread");

	//thread1.join(); //等待线程结束
	
	//thread1.detach(); //分离线程，线程结束后会自动回收资源

	bool isjoin = thread1.joinable(); //判断线程是否可连接
	if (isjoin) {
		thread1.join(); //等待线程结束
	}

	return 0;
}