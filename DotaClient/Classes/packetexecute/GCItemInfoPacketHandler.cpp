 
#include "./Packets/Item/GCItemInfoPacket.h"
#include "./datapool/DataPool.h"
#include "./object/Item.h"
#include "./object/ItemEquip.h"
#include "./event/EventSystem.h"
X_INT GCItemInfoPacketHandler::Execute( GCItemInfoPacket* pPacket, Player* pPlayer )
{
	if(pPacket == X_NULL) return 0;
	EM_ITEM_CONTAINER_TYPE container = (EM_ITEM_CONTAINER_TYPE)pPacket->GetContainerType();
	X_INT pos = pPacket->GetItemPos();
 
	SelfBagData*  pBag = DataPool::GetSingleton()->getBagData();
    Item *pItem = X_NULL;
	pItem = pBag->getItem(pos,container);

	if (pItem == X_NULL) return 0;
	 
	EM_ITEM_CLASS Class = pItem->GetClass();
 
	BitFlag16 flag = pPacket->GetBitFlag();

	//»ù±¾ÊôÐÔ
	for (X_INT i=ItemData::ITEM_DATA_BIND; i < ItemData::ITEM_DATA_COMMON_ATTR_COUNT; ++i)
	{
		if (flag.isSetBit(i) == XFALSE) continue;
		switch (i)
		{
			case  ItemData::ITEM_DATA_BIND:
				pItem->SetBind(pPacket->GetBind());
				break;
		}
	}

		switch (Class)
		{
		case EM_ITEM_CLASS_EQUIP:
			{
				 if (flag.isSetBit(ItemData::EquipData::EQUIP_DATA_ENHANCE) == XTRUE)
				 {
					 static_cast <ItemEquip*>(pItem)->SetStar(pPacket->GetEquipEnhanceLevel());
				 }
				 if (flag.isSetBit(ItemData::EquipData::EQUIP_DATA_BIND_OWNER) == XTRUE)
				 {
					 pItem->SetItemOwnerGUID(pPacket->GetBindOwnerGUID().GetValue());
				 }
				 if (flag.isSetBit(ItemData::EquipData::EQUIP_DATA_EQUIPUSE) == XTRUE)
				 {
					 static_cast <ItemEquip*>(pItem)->SetEquiped(pPacket->GetEquipUse());
				 } 
			}
			break;
		case EM_ITEM_CLASS_GEM:
			{
				if (flag.isSetBit(ItemData::GemData::GEMITEM_DATA_COUNT) == XTRUE)
				{
					pItem->SetCount(pPacket->GetGemItemCount());
				}
			}
			break;
		case EM_ITEM_CLASS_COMMON:
			{
				if (flag.isSetBit(ItemData::CommonItemData::COMMONITEM_DATA_COUNT) == XTRUE)
				{
					pItem->SetCount(pPacket->GetCommonItemCount());
				}
			}
			break;
		case EM_ITEM_CLASS_QUESTITEM:
			{
				if (flag.isSetBit(ItemData::QuestItemData::QUESTITEM_DATA_COUNT) == XTRUE)
				{
					pItem->SetCount(pPacket->GetQuestItemCount());
				}
			}
			break;
		} 
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_BAGOWN_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLINSPECT_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_HEROUPGRADE_UPDATA);
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_EQUIPMENTALL_UPDATA);
		
	return 1;
}