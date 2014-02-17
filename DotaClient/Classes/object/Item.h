#ifndef __ITEM_H__
#define __ITEM_H__
#include "./base/Global.h"
#include "./object/Object.h"
#include "./ItemData.h"
#include "./DataBase/DataBaseSystem.h"

class ObjectHero;
 
enum RULE
{
	EM_Discard,
	EM_Sale,
	EM_USE,
	EM_CONSUME,
	EM_GETBIND,
	EM_USEBIND,
	EM_UNIQUE,
	EM_Bank,
};
 
enum CommonItemType
{
	ITEM_TYPE_INVALID = 0,
	ITEM_EXPERIENCE = 2,
	ITEM_SKILL      = 3,
	ITEM_TOOLS      = 4,
};
enum DROP_TYPE
{
	DROP_TYPE_INVALID =-1,
	DROP_TYPE_ALTAR,
	DROP_TYPE_COPYSCNE,
};
class Item  :public Object
{

 public:
		
	 friend class ObjectManager;
 
	struct UBI_BASE_ITEM_DATA
	{
		X_UINT					m_ItemIndex;									//物品的客户端索引
		X_CLIENT_GUID			m_OwnerGUID;									//拥有者的guid
		EM_ITEM_CONTAINER_TYPE	m_PositionType;									//容器类型
		X_UINT					m_Position;										//容器位置
	 
		UBI_BASE_ITEM_DATA()
		{
			CleanUp();
		}

		X_VOID CleanUp()
		{
			m_ItemIndex						= INVALID_INDEX;
			m_OwnerGUID						= X_CLIENT_GUID(INVALID_INDEX);
			m_PositionType					= EM_ITEM_CONTAINER_INVALID;
			m_Position						= INVALID_VALUE;
		  
		}
	};
public:
	
	virtual X_VOID Release();
	X_VOID	SetItemIndex(const X_UINT nItemIndex);
	virtual X_VOID	SetItemData(const ItemData*	pData);
	virtual X_VOID SetTableId(X_INT nTableID);
	X_VOID  SetRule(X_INT ruleId);

	X_VOID  SetItemVectorType(EM_ITEM_CONTAINER_TYPE continer);
	X_VOID  SetItemVectorPos(X_UINT pos);
	X_VOID  SetItemOwnerGUID(X_CLIENT_GUID guid);
	X_VOID SetBind(X_UCHAR bind);
	X_VOID SetCount(X_UINT count);
	X_CLIENT_GUID  GetItemOwnerGUID()const;
	bool   isHeroBindEquip(const ObjectHero *phero)const;
	bool   isBindEquip()const;

	EM_ITEM_CONTAINER_TYPE  GetItemVectorType()const
	{
		if (m_pBaseData)
		{
			return  m_pBaseData->m_PositionType;
		}
		return EM_ITEM_CONTAINER_INVALID;
	}
	X_UINT  GetItemVectorPos()const
	{
		if (m_pBaseData)
		{
			return  m_pBaseData->m_Position;
		}
		return -1;
	}
	
	EM_ITEM_CLASS GetClass()const;
	X_BOOL Rule(RULE rule)const;
	X_UINT	GetItemIndex()const;
	X_INT GetTableType()const;
	virtual X_CHAR * GetIcon()const = 0;
	virtual X_CHAR * GetName()const = 0;
	virtual X_CHAR * GetColor()const= 0;

	virtual X_CHAR * GetType()const= 0;
	virtual X_CHAR * GetInfo()const= 0;
 	virtual X_INT  GetLevel()const;

	X_INT GetCount()const;
	virtual X_INT GetMaxCount()const;

	X_VOID SetPrice(X_INT Price)
	{
		m_Price = Price;
	}
	X_INT GetPrice()const;
	 
 
	X_VOID SetShopFloatPriceTime(X_INT time1,X_INT time2)
	{
		m_ShopFloatPriceTimeBegin = time1;
		m_ShopFloatPriceTimeEnd = time2;
	}
 
	X_VOID SetFloatPrice(X_INT Price)
	{
		m_FloatPrice = Price;
	}
 
	X_INT GetTableID()const
	{
		return m_TableId;
	}
	bool isVirtual()const
	{
		return m_bVirtual;
	}
	X_VOID SetVirtual(bool bVirtual)
	{
		 m_bVirtual = bVirtual;
	}
	//获得出售价格 
	virtual X_INT GetSalePrice()const{return 0 ;}

	static X_BOOL  getCommonItemInfoById(X_INT nTableId,string &name,string &color,string &icon  ,X_INT &level);
	static X_BOOL  getGemItemInfoById(X_INT nTableId,string &name,string &color,string &icon ,X_INT &level );
	static X_BOOL  getQuestItemInfoById(X_INT nTableId,string &name,string &color,string &icon  ,X_INT &level);
	static X_BOOL  getEquipInfoById(X_INT nTableId,string &name,string &color,string &icon ,X_INT &level);

protected:
	Item(X_CLIENT_GUID guid);
	virtual ~Item();
	 
protected:
 
	   const stDBC_FILE_ITEM_RULER* m_stRule;
	   UBI_BASE_ITEM_DATA*		m_pBaseData; //基础数据
	   X_UCHAR		m_bBind;
	   X_INT		m_nCount;	//当前数量
	   X_INT        m_TableId;
	   X_INT		m_Price;
	   //X_INT		m_SaleMoneyType;
	   bool			m_bVirtual;
	   X_INT		m_FloatPrice;
	   X_INT		m_ShopFloatPriceTimeBegin;
	   X_INT		m_ShopFloatPriceTimeEnd;
};

 


#endif //__ITEM_H__