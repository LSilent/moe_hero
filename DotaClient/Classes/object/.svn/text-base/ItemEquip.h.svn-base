#ifndef __ITEMEQUIP_H__
#define __ITEMEQUIP_H__
#include "./base/Global.h"
#include "./object/Item.h"


enum  Equip_Sub_Class
{
	EM_NORMAL  = 0,
	EM_MATERIAL,
	EM_FINALE
};
class ItemEquip  :public Item
{
protected:
	friend class ObjectManager;
	friend class Item;
	ItemEquip(X_CLIENT_GUID guid);
	virtual ~ItemEquip();
public:
	
	struct Attr
	{
		X_INT attrId;
		X_INT attrValue;
		Attr()
		{

		}
		X_VOID CleanUp()
		{
			attrId = -1;
			attrValue = -1;
		}
	};
	virtual X_VOID	SetItemData(const ItemData*	pData);
	X_VOID SetStar(X_UCHAR level);
	X_VOID SetEquiped(X_BOOL bEquiped);
	virtual X_VOID SetTableId(X_INT nTableID);
	bool isEquiped()const;
	virtual X_CHAR * GetIcon()const;
	virtual X_CHAR * GetName()const;
	virtual X_CHAR * GetColor()const;
	virtual X_CHAR * GetType()const;
	virtual X_CHAR * GetInfo()const;
	virtual X_INT  GetSalePrice()const;
	virtual X_INT  GetLevel()const;
	bool  CanLevelUp()const;
	 

	X_VOID SetCounterNum(X_INT CounterNum);
	X_INT GetCounterNum()const;

	X_INT getAttack()const;
	X_INT getDefense()const;
	X_INT getHP()const;;
	X_INT getMP()const;;

	vector<string> getAddAttr()const; 

	X_INT getAddAttr(EM_ATTRIBUTE id);

	const stDBC_FILE_EQUIP_ITEM *m_pTableData;

	 X_VOID  getDropInfo(DROP_TYPE &type,X_INT &id)const;


	  Equip_Sub_Class  GetSubClass()const;
	  bool isMaterial()const;// 材料 碎片 等
protected:
	X_INT  m_Attack;
	X_INT  m_Defense;
	X_INT  m_HP;
	X_INT  m_MP;
	X_INT  m_Weight;
  
	vector<Attr> m_Attr;
	X_UCHAR		m_Star;		//强化星级

	
	X_BOOL	     m_bEquiped;
	X_INT		 m_CounterNum;//图鉴计数用	

};

 

 


#endif //__ITEMCOMMON_H__