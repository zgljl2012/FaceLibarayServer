#include "Server.h"
#include "Log.h"
#include "Command.h"
#include "MyFaceRecognizer.h"

class MyReceiver : public Server::OnReceiverListener {
private:
	Command command;
	Log* log;
	string last;

public:
	MyReceiver() {
		log = &Log::getInstance();
	}
public:
	void started(SOCKADDR_IN clientsocket){
		log->print("连接建立");
	}

	void receive(string msg, Server::OnSenderHandler* sender){
		log->print(msg);
		if (msg == command.ADD) {
			sender->sendMsg("add");
		}
		else if (msg == command.PREDICT) {
			sender->sendMsg("predict");
		}
		else if (msg == command.CLOSE) {
			sender->sendMsg("close");
		}
		else {
			sender->sendMsg("...");
		}
	};

	void stopped(SOCKADDR_IN clientsocket, Server::OnSenderHandler* sender){

	}
};

void main(){
	Server server;
	server.startListen(4000, 10, new MyReceiver());
}


