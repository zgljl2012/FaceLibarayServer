/*==========================================================
* 文件名 : Log
* 日期	 : 2015/9/10
* 功能   : 日志记录
* ==========================================================*/

#ifndef _LOG_H_
#define _LOG_H_
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::endl;

class Log {
public:
	static Log getInstance();
	void print(string log);
	void print(string tag, string log);

private:
	static Log log;
	Log(){

	}
};

Log Log::getInstance() {
	return log;
}

void Log::print(string log) {
	cout << "[" << log << "]" << endl;
}

void Log::print(string tag, string log) {
	cout << "[" << tag << "]" 
		 << "[" << log << "]" 
		 << endl;
}

#endif
