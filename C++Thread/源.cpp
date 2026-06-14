#include<iostream>
#include<thread>
#include<mutex>
#include<string>

class Log {
public:
	Log() {};
	Log(const Log& log) = delete;
	Log& operator=(const Log& log) = delete;

	//static Log instance;//饿汉模式

	static Log& GetInstance() {
		//static Log log; //懒汉模式
		//return log;
		static Log* log = nullptr;
		if (!log) log = new Log;
		return *log;
	}

	void PrintLog(std::string msg) {
		std::cout <<__TIME__<< msg << std::endl;
	}
};


int main() {

	Log::GetInstance().PrintLog("error");

	return 0;
}