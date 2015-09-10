/*==========================================================
* 文件名 : Server
* 日期	 : 2015/9/8
* 功能   : 实现C++人脸识别服务器
* ==========================================================*/

#ifndef _SERVER_H_
#define _SERVER_H_

#include <WINSOCK2.H>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;

#pragma comment(lib,"ws2_32.lib")

class Server {

public:
	// 端口号
	int mPort;
	// 最大连接数
	int mMaxConnectCount;
	// 客户端输入结束标识符
	char* eof;
	// 客户端结束会话标识符
	char* quit;
	// Recv缓存区大小
	static const int recvBufferCount = 10000;

public:
	// 内部类，将在Receiver中给调用者以实例，让调用者可用之发送消息
	class OnSenderHandler {
	public:
		virtual void sendMsg(string msg) = 0;
	};
	// 内部类，当客户端发来信息时的接收器类
	class OnReceiverListener {
	public:
		// 连接建立时的回调接口
		virtual void started(SOCKADDR_IN clientsocket){};
		// 接收器回调接口
		virtual void receive(string msg, OnSenderHandler* sender) = 0;
		// 断开连接时的回调接口
		virtual void stopped(SOCKADDR_IN clientsocket, OnSenderHandler* sender){};
	};

public:
	// 默认构造器
	Server();
	// 开始监听
	void startListen(int _port, int _maxConnectCount, OnReceiverListener* listener);
	// 结束监听
	void stopListen();
	// 使用自定义的发送函数发送消息
	static int self_send(SOCKET socket, const char* buffer, int len);

private:
	OnReceiverListener* mListener;

private:
	// 实现的OnSenderHandler
	class SenderHandler : public OnSenderHandler{
	public:
		SOCKET serConn;
		void sendMsg(string msg) {
			int success = self_send(serConn, msg.c_str(), msg.length() + 1);
			if (success == -1) {
				cout << "发送数据出错！" << endl;
			}
		}
	};
	SenderHandler mSenderHandler;
};

// 默认构造器
Server::Server(){
	mPort = 3000;
	mMaxConnectCount = 10;
	eof = ".";
	quit = "quit";
}

int Server::self_send(SOCKET socket, const char* buffer, int len) {
	int bytes_left;
	int written_bytes;
	const char *ptr;

	ptr = buffer;
	bytes_left = len;
	while (bytes_left>0)
	{

		written_bytes = send(socket, ptr, bytes_left, 0);
		if (written_bytes <= 0)
		{
			// 错误为EINTR(eintr)表示在写的时候出现了中断错误
			if (errno == EINTR)
				written_bytes = 0;
			else
				return(-1);
		}
		bytes_left -= written_bytes;
		ptr += written_bytes;
	}
	return(0);
}

void Server::startListen(int _port, int _maxConnectCount,
	OnReceiverListener* listener){
	mPort = _port;
	mMaxConnectCount = _maxConnectCount;
	mListener = listener;
	
	while (1) {
		//创建套接字
		WORD myVersionRequest;
		WSADATA wsaData;                    //包含系统所支持的WinStock版本信息
		myVersionRequest = MAKEWORD(1, 1);  //初始化版本1.1
		int err;
		err = WSAStartup(myVersionRequest, &wsaData);
		if (!err){
			cout << ("已打开套接字\n");
		}
		else{
			//进一步绑定套接字
			cout << ("套接字未打开!");
			return;
		}
		SOCKET serSocket = socket(AF_INET, SOCK_STREAM, 0);//创建了可识别套接字
		//需要绑定的参数
		SOCKADDR_IN addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//ip地址
		addr.sin_port = htons(this->mPort);//绑定端口
		//将套接字绑定到指定的网络地址
		bind(serSocket, (SOCKADDR*)&addr, sizeof(SOCKADDR));//绑定完成
		listen(serSocket, this->mMaxConnectCount);          //第二个参数代表能够接收的最多的连接数
		SOCKADDR_IN clientsocket;
		int len = sizeof(SOCKADDR);
		SOCKET serConn;
		//等待客户端的连接
		serConn = accept(serSocket, (SOCKADDR*)&clientsocket, &len);
		cout << "客户端" << inet_ntoa(clientsocket.sin_addr) << "已连接" << endl;
		//客户端已连接
		if (mListener != NULL) {
			mListener->started(clientsocket);
		}
		// 开始接收客户端传入的数据，直到传入的是输入结束符
		while (1) {
			string msg="";
			//while (1) {
			// 缓存区需要初始化
			char receiveBuf[recvBufferCount] = {0};
				// 接收客户端传来的信息
				int success = recv(serConn, receiveBuf, sizeof(receiveBuf), 0);
				if (success <= 0) {
					// 这里需要接收错误码处理
					cout << "接收数据出错！" << endl;
					break;
				}
				
				if (!strcmp(receiveBuf, eof)){
					//输入结束
					//break;
				}
				msg += receiveBuf;
			//}
			if (mListener != NULL) {
				mSenderHandler.serConn = serConn;
				this->mListener->receive(msg, &mSenderHandler);
			}
			//如果客户端传来了quit信号，则服务端等待下一个客户端
			if (msg == quit) {
				break;
			}
		}
		cout << "客户端" << inet_ntoa(clientsocket.sin_addr) << "已关闭" << endl;
		if (mListener != NULL) {
			this->mListener->stopped(clientsocket, &mSenderHandler);
		}
		closesocket(serConn);   //关闭
		WSACleanup();           //释放资源的操作
	}
}



#endif


