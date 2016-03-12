#pragma once




#include "MySocket.h"
#include "../message.h"
#include <hash_map>
#include <vector>
#include "../json/json.h"
#pragma comment (lib ,"lib_json.lib")


/*  session status */
typedef enum _sessionStatus{

	session_active,
	session_hangup,
	session_connect,
	session_disconnect,
	session_unknown
} SessionStattus;


typedef unsigned long uLong;
////
typedef pair<uLong, MySocket *> ScoketPair;

class SessionManage;
class ClientSocket;
class Session;
class MyServerSocket
{
private :
	int _socketHandle;
	int _port;
	string _name;
	HANDLE _threadHandle;
	//hash_map<uLong, MySocket *> clients;
public:
	SocketStatus status;
	MyServerSocket(string ,int);
	bool start();
	bool stop();
	ClientSocket * createClient(uLong, uLong, int);
	void onAccept(sockaddr_in * ,int);
	~MyServerSocket();
	friend DWORD WINAPI listen_thread(void *);
};
////////////////////////
////////////*session*///
////////////////////////

class ClientSocket :public MySocket
{
private:
	unsigned long _session_id;
	int _windows_handle;
	
	vector<Message *> Messages;

public:
	SessionStattus s_status;
	ClientSocket(uLong, uLong, int);
	virtual void onRecevice(int, const char*);
	void notifyWindows();
	void stopSession();
	void MsgToBuffer(Message *, char **);
	void BufferToMsg(Message * s_msg, const  char  *buffer);
	void sendText(int type,const  char *);
	void onMessage(Message * s_msg, const char  *buffer);
	bool sendMessage(Message *);
	~ClientSocket();
};

