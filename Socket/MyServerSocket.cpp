#include "MyServerSocket.h"
#include "../Session.h"
#include "../user.h"
#include "../SessionManager.h"
#include "../DataManager.h"

DWORD WINAPI listen_thread(void * d){
	MyServerSocket *that = (MyServerSocket *)d;
	sockaddr_in client;
	int size = sizeof(client);
	while (1){
		ZeroMemory(&client, size);
		if (that->status == socket_ready){
			int handle = ::accept(that->_socketHandle,(sockaddr*) &client, &size);
			if (handle < 0){
				int err = WSAGetLastError();
				if (err == WSAEWOULDBLOCK){
					Sleep(2000);
				}
				else{
					that->status = socket_err;
					break;
				}
				
			}
			else{
				that->onAccept(&client, handle);
			}
			Sleep(100);
		}
		else{
			break;
		}
	}
	that->status = socket_err;
	return NULL;
}
MyServerSocket::MyServerSocket(string name, int port) :_socketHandle(-1),_name(name)
, _port(port)
, status(socket_unknown)
, _threadHandle(0)
{
}

bool MyServerSocket::start(){
	WSADATA ws; 
	WSAStartup(MAKEWORD(2, 0), &ws);
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	serveraddr.sin_port = htons(_port);
	this->_socketHandle = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_socketHandle == INVALID_SOCKET){
		this->_socketHandle = socket_err;
		return false;
	}

	int opt = 1;
	setsockopt(this->_socketHandle, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
	if (bind(this->_socketHandle, (sockaddr*)&serveraddr, sizeof(serveraddr)) == SOCKET_ERROR){
		this->status = socket_err;
		return false;
	}
	u_long optt = 1;
	int iResult = ioctlsocket(this->_socketHandle, FIONBIO, &optt);//���÷�����
	if (iResult != NO_ERROR){
		this->status = socket_err;
		this->stop();
		return false;
	}
	if (listen(this->_socketHandle, 50)==SOCKET_ERROR){
		this->_socketHandle = socket_err;
		return false;
	}
	this->status = socket_ready;
	_threadHandle =	CreateThread(NULL, 0, listen_thread,(void*) this, NULL, NULL);
	if (_threadHandle == INVALID_HANDLE_VALUE){
		this->_socketHandle = socket_err;
		return false;
	}
	
	return true;
}
ClientSocket * MyServerSocket::createClient(uLong id, uLong ipAddr, int port){
	ClientSocket * socket = new ClientSocket(id, ipAddr, port);
	return socket;
}
bool  MyServerSocket::stop(){
	if (this->status != socket_ready){
		WSACleanup();
		return true;
	}
	else{
		::closesocket(this->_socketHandle);
		this->status = socket_disconnect;
	}
	WSACleanup();
	return true;
}
void MyServerSocket::onAccept(sockaddr_in * addr, int handle){

	uLong user_id = (addr->sin_addr).s_addr;
	ClientSocket * socket = createClient((addr->sin_addr).s_addr, (addr->sin_addr).s_addr, ntohs(addr->sin_port));
	socket->OnAccept(handle);
	socket->status = socket_ready;
	socket->s_status = session_connect;
	/*  �ɹ���ֵ��  Ϊ�Σ�*/
	socket->Recevice();
	User user((addr->sin_addr).s_addr, inet_ntoa(addr->sin_addr), (addr->sin_addr).s_addr);
	Session * session = new Session(user, socket);
	SessionManager *sm = SessionManager::GetInstance();
	sm->addSession(session);
	/*
	add sessions
	*/
	//clients.insert(ScoketPair(user_id, socket));
}

MyServerSocket::~MyServerSocket()
{
}




ClientSocket::ClientSocket(uLong session_id, uLong ipAddr, int port)
:MySocket(ipAddr,port)
,_session_id(session_id)
, _windows_handle(-1)
,s_status(session_unknown)
{
}

void ClientSocket::onRecevice(int size, const char *msg){
	Message s_msg;
	BufferToMsg(&s_msg, msg);
	//MySocket::sendMessage("5151515515");
	DataManager *dm = DataManager::getInstance();
	dm->handleServiceDiscoverMsg(s_msg);
}
void ClientSocket::notifyWindows(){
	/*    
	ʵ��
	*/
}
void ClientSocket::stopSession(){
	MySocket::Close(this->status);
}
void ClientSocket::sendText(int type, const char * text){
	Message s_msg;
	s_msg.msg_type = type;
	ClientSocket::sendMessage(&s_msg);
}
bool ClientSocket::sendMessage(Message * s_msg){

	char * buf=NULL;
	s_msg->MsgTobuffer(&buf);

	return MySocket::sendMessage(string(buf));
	//free(buf);
}

void ClientSocket::onMessage(Message * s_msg, const char  *buffer){
}

void ClientSocket::BufferToMsg(Message * msg, const  char  *buffer){
	string getMsg(buffer);
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(getMsg, root))  // reader��Json�ַ���������root��root������Json��������Ԫ��  
	{
		//std::stringstream strValue;


		msg->msg_type = root["msg_type"].asInt();  // ���ʽڵ㣬upload_id = "UP000000"  
		msg->content = root["content"].asString();  // ���ʽڵ㣬upload_id = "UP000000"  
		string timestr = root["time"].asString();  // ���ʽڵ㣬upload_id = "UP000000"  
		int    a, b, c, d, e, f;
		sscanf_s(timestr.c_str(), "%d-%d-%d %d:%d:%d", &a, &b, &c, &d, &e, &f);
		CTime    time(a, b, c, d, e, f);
		msg->time = time;
		string from_id = root["FromID"].asString();
		sscanf_s(from_id.c_str(), "%ul", &(msg->FromID));
		string to_id = root["ToID"].asString();

		sscanf_s(to_id.c_str(), "%ul", &(msg->ToID));
		msg->myWPragam = root["myWPragam"].asInt();
	}
	/*
	ʵ��
	*/
}
ClientSocket::~ClientSocket()
{
}
