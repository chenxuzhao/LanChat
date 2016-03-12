#pragma once

using namespace std;
class Session;
typedef pair<uLong, Session *> SessionPair;

class SessionManager
{
private:
	
	 static  SessionManager *m_pSingleInstance;
	
	 SessionManager();
	 ~SessionManager();
	 //find

public:
	bool hasUser(long UserID);
	hash_map<unsigned long, Session*> sessions;
	void addSession(Session*);
	hash_map<unsigned long, Session*> getSessions();
	//	void addSession(Session);
	static SessionManager * GetInstance();
	Session* getSessionByUserID(unsigned long);
};

