#include<iostream>
#include<thread>
#include<memory>
std::thread t;

//void foo(int& x) {
//	x += 1;
//}
//
//void test() {
//	int a = 1;
//	t = std::thread(foo, std::ref(a));//局部变量 a，将join()放外面会报错
//	t.join();
//} 

//void foo(int* x) {
//	std::cout << *x << std::endl;
//}

//class MyClass {
//public:
//	void func() {
//		std::cout << "Thread "<<std::this_thread::get_id()<<" started" << std::endl;
//		//do some work
//		std::cout << "Thread " << std::this_thread::get_id() << " finished" << std::endl;
//	}
//};


class A {
private:
	friend void thread_foo();
	void foo() {
		std::cout << "Hello" << std::endl;
	}
};

void thread_foo() {
	std::shared_ptr<A> a = std::make_shared<A>();
	std::thread t(&A::foo, a);
	t.join();
}

int main() {
	//test();
	//int a = 1;
	//std::thread t(foo, std::ref(a));
	
	//std::cout << a << std::endl;

	//int* ptr = new int(1);
	//std::thread t(foo, ptr);
	//delete ptr;//立马释放会报错，运行不完
	//t.join();

	//MyClass obj;
	//std::thread t(&MyClass::func, &obj);
	//obj被提前销毁了，会导致未定义的行为
	//t.join();

	//std::shared_ptr<MyClass> a = std::make_shared<MyClass>();
	//std::thread t(&MyClass::func, a);

	//t.join();

	//std::shared_ptr<A> a = std::make_shared<A>();
	//std::thread t(&A::foo, a);
	//t.join();

	thread_foo();

	return 0;
}