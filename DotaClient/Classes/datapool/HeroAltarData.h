#ifndef __HERO_ALTAR_DATA_H__
#define __HERO_ALTAR_DATA_H__

#include "./base/Global.h"
#include "./DataBase/DataBaseSystem.h"

class HeroAltar
{
	friend class HeroAltarData;
public:

	X_INT getID()const;
	X_INT getOpenLevel()const;
	//X_INT getCostgold()const;
	X_INT getCostItem()const;
	X_INT getCostItemNum()const;
	string getCostItemName()const;

	X_INT getLimit()const;

	//可能的掉落物品
	vector<string> getAwardItems(bool Apparitions);
protected:

	const stDBC_FILR_SACRIFICE	* m_pTableData;
};


class HeroAltarData
{
public:
	X_VOID Initial();
	X_VOID Release();
public:

	const vector<HeroAltar*>  & getHeroAltar()
	{
		return m_HeroAltars;
	}

protected:

	vector<HeroAltar*>   m_HeroAltars;;
};

 


#endif // !__HERO_ALTAR_DATA_H__
