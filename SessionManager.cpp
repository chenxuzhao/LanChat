#include "stdafx.h"


#include "Session.h";

SessionManager*  SessionManager::m_pSingleInstance(NULL);
SessionManager::SessionManager(){

}
SessionManager* SessionManager::GetInstance(){
	if (m_pSingleInstance == NULL){
		m_pSingleInstance = new SessionManager();

	/*	User user(inet_addr("192.168.1.107"), "Íõ°ØÔª", inet_addr("192.168.1.107"));
		Session* session = new Session(user);

		User user2(inet_addr("192.168.1.109"), "³ÂÐñ", inet_addr("192.168.1.109"));
		Session* session2 = new Session(user2);

		m_pSingleInstance->addSession(session);
		m_pSingleInstance->addSession(session2);*/
	}
		

	return m_pSingleInstance;
}


SessionManager::~SessionManager()
{
	delete m_pSingleInstance;
}
void SessionManager::addSession(Session* session){
	unsigned long id = (session->m_user).ID;
	hash_map<unsigned long, Session*>::iterator it = sessions.find(id);
	if (it != sessions.end()){
		if (((Session*)(it->second))->se_status == se_connect)
			return;
		else{
			sessions.erase(it);
			sessions.insert(SessionPair(id, session));
		}
	}
	else{
		sessions.insert(SessionPair(id, session));
	}
	//DataManager* datamn = DataManager::getInstance();
	AfxGetApp()->m_pMainWnd->SendMessage(WM_LISTCHANGE_MESSAGE, 0, NULL);
}
hash_map<unsigned long, Session*>  SessionManager::getSessions(){
	return this->sessions;
}
Session* SessionManager::getSessionByUserID(unsigned long id){
	//sessions = &SessionManager::Sessions;
	hash_map<unsigned long, Session*>::iterator it = sessions.find(id);
	if (it != sessions.end()){
		return it->second;
	}
	else{
		return NULL;
	}

}