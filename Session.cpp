
#include "Session.h"

string GetMyLocalIpAddress()
{
	char local[255] = { 0 };
	gethostname(local, sizeof(local));
	hostent* ph = gethostbyname(local);
	if (ph == NULL)
		return "";
	in_addr addr;
	memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr)); // 这里仅获取第一个ip  
	string localIP;
	localIP.assign(inet_ntoa(addr));
	return localIP;
}

Session::Session(User iUser) :m_user(iUser), se_status(se_unknown)
{
	this->chatDialog = nullptr;
	session_id = iUser.ID;
	m_my_ID = inet_addr(GetMyLocalIpAddress().c_str());
}
Session::Session(User user, ClientSocket * ct) : m_user(user), client(ct), se_status(se_connect)
{
	this->se_status = se_connect;
	this->chatDialog = nullptr;
	session_id = user.ID;
	m_my_ID = inet_addr(GetMyLocalIpAddress().c_str());
}


void Session::connect(){
	if (this->se_status != se_connect){
		client = new ClientSocket(m_user.ID, this->m_user.ID, 7081);
		if (client->Connect()){
			this->se_status = se_connect;
			client->Recevice();
		}
	}
}


bool Session::sendMessage( Message*text){
	if (this->se_status != se_connect){
		Session::connect();
	}
	bool  result =  client->sendMessage(text);
	if (!result){
		this->se_status = se_disconnect;
	}
	return result;
}

/*
Session::Session(User iUser) :m_user(iUser)
{
	char * ipaddr = NULL;
	char addr[20];
	in_addr inaddr;
	inaddr.s_addr = iUser.ID;
	ipaddr = inet_ntoa(inaddr);
	strcpy(addr, ipaddr);


	client = new ClientSocket(iUser.ID, addr, 7081);
}*/


Session::~Session()
{
}
void Session::setOnline(bool online){

}
void Session::setDialog(ChatDialog* chatDialog){
	this->chatDialog = chatDialog;
}

