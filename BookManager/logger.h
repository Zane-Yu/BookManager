#ifndef LOGGER
#define LOGGER

#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<time.h>

class Logger {
public:
	void info(std::string msg) {
		level_str = "INFO";
		output(msg);
	}
	void warn(std::string msg) {
		level_str = "WARN";
		output(msg);
	}
	void error(std::string msg) {
		level_str = "ERROR";
		output(msg);
	}

	std::string get_tiem() {
		std::time_t now = std::time(nullptr);
		struct tm local_time;
		localtime_s(&local_time, &now);

		std::stringstream ss;
		ss << std::put_time(&local_time, "%F");
		std::string timestamp = ss.str();
		return timestamp;
	}

private:
	std::string level_str;

	void output(std::string msg) {
		std::time_t now = std::time(nullptr);
		struct tm local_time;
		localtime_s(&local_time, &now);

		std::stringstream ss;
		ss << std::put_time(&local_time, "%F %T");
		std::string timestamp = ss.str();

		std::cout << "[" << level_str << "] "
				  << "[" << timestamp << "] " << msg << std::endl;
	}
};

static Logger logger;

#endif // !LOGGER


