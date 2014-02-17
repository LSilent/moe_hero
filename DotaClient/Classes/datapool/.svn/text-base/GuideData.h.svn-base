#ifndef __GUIDE_DATA_H__
#define __GUIDE_DATA_H__

#include "./base/Global.h"
#include "./DataBase/DataBaseSystem.h"

class GuideData
{
public:
	X_VOID Initial();
	X_VOID Release();

	X_VOID SetTipGroup(X_INT id);


public:
	static const stDBC_FILE_GUIDE* getTableData(X_INT id);

	X_INT GetCurrentTipId(){  return m_TipId;}
	X_VOID HandleTip(X_INT id = -1);

protected:
	X_INT   m_TipGroup;
	X_INT	m_TipId;
	X_INT   m_PreTipId;
	map<X_INT ,vector<X_INT> > m_Tips;
};

#endif