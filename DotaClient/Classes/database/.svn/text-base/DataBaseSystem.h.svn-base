 

#ifndef __DATABASESYSTEM_H__
#define __DATABASESYSTEM_H__

#include "./base/Global.h"
#include "./base/Singleton.h"
#include "./database/DataBase.h"
#include "./database/DataBaseDefine.h"

#include <map>
class DataBaseSystem : public  Singleton<DataBaseSystem>
{

	DECLARE_SINGLETON(DataBaseSystem)

public:
	DataBaseSystem();
	virtual ~DataBaseSystem();

public:
	 
	X_VOID				Initial();
	X_VOID				Release();
	X_VOID				OpenAllDataBase();
	X_VOID				CloseAllDataBase();
	const DataBase*	GetDataBase(X_INT idDataBase) const;
	//const DataBase*	GetDataBase(wstring& tableName) const;

private:
	std::map<X_INT, DataBase*>		m_mapDataBaseBuf;
	//std::map<wstring, X_INT>		m_mapNameToID;

};
#endif