#pragma once

//class ClientSocket;
#include "user.h"
#include "message.h"
#include "socket/MyserverSocket.h"
#include <vector>

typedef enum MySessionStatus{
	se_disconnect,
	se_connect,
	se_active,
	se_unknown
};
class ChatDialog;

class Session
{

public:
	unsigned long session_id;
	MySessionStatus se_status;
	bool isOnline;
	User m_user;
	unsigned long m_my_ID;
	Session(User);
	Session(User, ClientSocket *);
	void connect();
	vector<Message> messageList;
	ChatDialog* chatDialog;
	ClientSocket * client;
	bool sendMessage( Message *text);
	void setOnline(bool);
	void setDialog(ChatDialog*);
	~Session();
};
