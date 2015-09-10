/*==========================================================
* 文件名 : Command
* 日期	 : 2015/9/8
* 功能   : 提供与客户端交互时指定的命令
* ==========================================================*/

#ifndef _COMMAND_H_
#define _COMMAND_H_

class Command {
public:
	// 往特征库里添加人脸
	static const char* ADD;
	// 识别人脸
	static const char* PREDICT;
	// 关闭连接
	static const char* CLOSE;

};

const char* Command::ADD = "add";
const char* Command::PREDICT = "predict";
const char* Command::CLOSE = "close";

#endif


