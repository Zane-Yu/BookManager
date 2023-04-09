#ifndef LOAD
#define LOAD

#include<iostream>
#include<ctime>
#include<chrono>
#include<string>
#include<thread>
#include<cstdlib>

class Load {
public:
	Load(int len) :_str_len(len) {};
	void info(std::string msg) {
		std::cout << msg << "......" << std::endl;
		int num_ptr = 0;

		int rand_num, wait_rand;
		srand((unsigned)time(NULL));
		rand_num = rand() % 4 + 1;
		std::cout << '[';
		while (num_ptr < _str_len) {
			num_ptr += rand_num;
			if (num_ptr > _str_len) rand_num -= num_ptr - _str_len;
			std::cout << std::string(rand_num, '=');

			wait_rand = rand() % 10;
			std::this_thread::sleep_for(std::chrono::milliseconds(_idx[wait_rand]));

			rand_num = rand() % 4 + 1;
		}
		std::cout << "]\n";
	}
private:
	int _str_len;
	int _idx[10] = { 800,500,300,200,200,100,100,50,50,0 };
};

static Load load(25);


#endif // !LOAD
