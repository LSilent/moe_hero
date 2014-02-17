 
#include "./Packets/Item/GCItemDeletePacket.h"
#include "./datapool/DataPool.h"
#include "./object/Item.h"
#include "./event/EventSystem.h"
#include "./Packets/Item/GCItemListNotifyPacket.h"
X_INT GCItemDeletePacketHandler::Execute( GCItemDeletePacket* pPacket, Player* pPlayer ) 
{
	if(pPacket == X_NULL) return 0;
	EM_ITEM_CONTAINER_TYPE container = (EM_ITEM_CONTAINER_TYPE)pPacket->GetContainerType();
	X_INT num = pPacket->GetCount();

	SelfBagData*  pBag = DataPool::GetSingleton()->getBagData();

	X_INT pos = 0;
	for (X_INT i = 0;i<num;i++)
	{
		pos = pPacket->GetItemPos(i);
		pBag->DelItemFromBag(pos,container,XTRUE);
	}
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BAGOWN_UPDATA);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLINSPECT_UPDATA);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROUPGRADE_UPDATA);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENT_SELL_UPDATA);
	EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTALL_UPDATA);

	return 1;
}
X_INT GCItemListNotifyPacketHandler::Execute( GCItemListNotifyPacket* pPacket, Player* pPlayer ) 
{
		if(pPacket == X_NULL) return 0;
		X_INT num = pPacket->GetCount();
		//X_INT itemid,itemNUm ;
		vector<tipItem> vec;
		vec.clear();
		tipItem item;
		for (X_INT i = 0;i<num;i++)
		{
			pPacket->GetItem(i,item.itemID,item.itemNum);
			vec.push_back(item);
		}
		DataPool::GetSingleton()->setTipItems(vec);
	   // EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIPITEM_SHOW);

 
		vector<string> strV;strV.clear();
		string name,icon ,color;X_INT level;
		for (X_INT i = 0;i<num;i++)
		{
			DataPool::GetSingleton()->getObjectManager()->getItemInfoById(vec[i].itemID,name,color,icon,level);
			strV.push_back(name);
		}
		
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		return 1;
}