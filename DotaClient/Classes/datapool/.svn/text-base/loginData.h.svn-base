#ifndef __LOGINDATA_H__
#define __LOGINDATA_H__

#include "./base/Global.h"

class LoginData
{
public:
	LoginData();
 
public:
	//账号
	X_VOID setUserId(string strId)
	{
		m_userId = strId;
	}
	string getUserId()const;
	 
	//服务器
	/*X_VOID setServerId(X_INT id)
	{
		m_serverId = id;
	}
	X_INT getServerId()const
	{
		return m_serverId;
	}*/
	string getLoginName()const;
	 
	X_VOID setLoginName(const string &str) 
	{
		m_name = str;
	}
protected:
	//	玩家账号
	mutable string    m_userId;
	//	服务器组号
	X_INT	  m_serverId;

	mutable string    m_name;

	static  const    char * m_randomName[];
	static  const    char * m_randomFirstName[];
 

};
 
#endif // !__LOGINDATA_H__


