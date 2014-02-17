#include "./game/SendPacket.h"
#include "./Packets/Human/CGAskHumanDetailAttrPacket.h"
#include "./Packets/Hero/CGAskHeroListPacket.h"
#include "./Packets/Item/CGAskItemListPacket.h"
#include "./Packets/Hero/CGImproveHeroPacket.h"
#include "./Packets/Login/CGCreateRolePacket.h"

#include "./Packets/Item/CGDropItemPacket.h"
#include "./Packets/Item/CGMoveItemPacket.h"
#include "./Packets/Item/CGUseItemPacket.h"
#include "./Packets/Item/CGDropItemPacket.h"

#include "./Packets/CGHeartBeatPacket.h"
 
#include "./timer/SystemTimer.h"
#include "./event/EventSystem.h"
#include "./net/NetworkSystem.h"
#include "./game/MainGame.h"
#include "./ui/UISystem.h"
#include "./load/ResourceSystem.h"
#include "./database/DataBaseSystem.h"
#include "./ui/SceneManger.h"
#include "./sound/SoundSystem.h"
#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/Item.h"
#include "./object/ObjectHero.h"
#include "./Packets/Hero/CGDistribHeroBearpointPacket.h"
#include "./Packets/Other/CGBuyShopItemPacket.h"
#include "./Packets/Human//CGSetMatrixObjectPacket.h"
#include "./Packets/Fight/CGAskFightPacket.h"
#include "./Packets/Human/CGChatPacket.h"
#include "./Packets/Human/CGEquipManufacturePacket.h"
#include "./datapool/EquipOperator.h"
#include "./Packets/Other/CGAskSkillLevelUpPacket.h"
#include "./Packets/Fight/CGAskCopySceneListPacket.h"
#include "./Packets/Mail/CGMailAskOpenPacket.h"
#include "./Packets/Mail/CGMailDelPacket.h"
#include "./Packets/Mail/CGMailReadPacket.h"
#include "./Packets/Mail/CGMailWritePacket.h"
#include "./Packets/Arena/CGArenaAskEnterPacket.h"
#include "./Packets/Arena/CGArenaChallengePacket.h"
#include "./packets/Other/CGBuyActionPointPacket.h"
#include "./packets/Other/CGSellItemPacket.h"
#include "./Packets/HuoDong/CGAskHuoDongListPacket.h"
#include "./Packets/Other/CGEatCheesePacket.h"
#include "./Packets/Other/CGRefreshCopyScenePacket.h"
#include "./datapool/HuoDong.h"
#include "./Packets/Other/CGBuyBearPointPacket.h"
#include "./Packets/Charge/CGAskChargePacket.h"
#include "./Packets//Other/CGAskAchievementPacket.h"
#include "./packets/Other/CGGetAchievementAwardPacket.h"
#include "./Packets/Other/CGFreshGuidePacket.h"
#include "./Packets/Mission/CGAskMissionListPacket.h"
#include "./Packets/Mission/CGSubmitMissionPacket.h"
#include "./Packets/Arena/CGArenaAskDetailPacket.h"
#include "./Packets/Wood/CGWoodAskPacket.h"
#include "./Packets/Wood/CGWoodSetMatrixPacket.h"
#include "./Packets/Other/CGExchangeStonePacket.h"
#include "./Packets/QuJing/CGAskQuJingDataPacket.h"
#include "./Packets/QuJing/CGOpenQuJingUIPacket.h"
#include "./Packets/QuJing/CGQuJingHuSongPacket.h"
#include "./Packets/QuJing/CGQuJingRobPacket.h"
#include "./Packets/QuJing/CGQuJingSetMatrixPacket.h"
#include "./Packets/QuJing/CGQuJingSpeedUpPacket.h"
#include "./Packets/QuJing/CGRefreshQuJingShiZhePacket.h"
#include "./Packets/QuJing/CGRefreshQuJingTangSengPacket.h"
#include "./Packets/Stair/CGStairAskPacket.h"
#include "./Packets/Other/CGRockHeroPacket.h"
#include "./Packets/Other/CGGetGiftpackCardPacket.h"
#include "./Packets/Mail/CGMailDelAllPacket.h"
#include "./Packets/Mail/CGMailReadAllPacket.h"
// «Î«ÛÕÊº“
X_VOID SendLogicPacket::askHumanDetail()
{
	CGAskHumanDetailAttrPacket packet;
	ObjectSelf* pSelf =  DataPool::GetSingleton()->getObjectManager()->getSelf();
	packet.SetGuid(pSelf->GetGuid());
	NetworkSystem::GetSingleton()->SendPacket(&packet);

}
//«Î«Û”¢–€
X_VOID   SendLogicPacket::askHeros(EM_HERO_CONTAINER_TYPE _vector)
{
	if(_vector <= EM_HERO_CONTAINER_INVALID || _vector >= EM_HERO_CONTAINER_NUMBER) return;

	CGAskHeroListPacket packet;
	//EM_HERO_CONTAINER_BAG,			//Œ‰Ω´¿∏
	//EM_HERO_CONTAINER_RECRUIT,		//Œ‰Ω´’–ƒº¿∏

	packet.SetContainerType(_vector);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
//«Î«Û±≥∞¸
X_VOID   SendLogicPacket::askPacket(EM_ITEM_CONTAINER_TYPE _vector)
{

	if(_vector <= EM_ITEM_CONTAINER_INVALID || _vector >= EM_ITEM_CONTAINER_NUMBER) return;
	CGAskItemListPacket packet;
	packet.SetContainer(_vector);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
 
}
X_VOID  SendLogicPacket::ImproveHero(const ObjectHero *pHero){

	if (pHero == X_NULL)
	{
		return;
	}
	CGImproveHeroPacket packet;
	packet.SetHeroPos(pHero->GetPos());
	packet.SetHeroGUID(pHero->GetGuid());
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID  SendLogicPacket::RecruitHero(EM_RECRUIT_HERO_TYPE type,const ObjectHero *pHero)
{
	CGRecruitHeroPacket  packet;
	if (EM_RECRUIT_HERO_SINGLE == type && pHero != X_NULL )
	{
		packet.SetHeroPos(pHero->GetPos());
		packet.SetHeroGUID(pHero->GetGuid());
	}
	packet.SetRecruitType(type);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID   SendLogicPacket::DropItem(const  Item *pItem)
{
	if (pItem == X_NULL)
	{
		return;
	}
	CGDropItemPacket packet;
	packet.SetSourceContainerType(pItem->GetItemVectorType());
	packet.SetSourcePos(pItem->GetItemVectorPos());
	packet.SetSourceGuid(pItem->GetGuid());
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID    SendLogicPacket::UseItem(const Item * pItem, const ObjectHero* pHero )
 {
	 CGUseItemPacket packet;
	 if (pHero)
	 {
		 packet.SetTargetGUID(pHero->GetGuid());
	 }
	 packet.AddItem(pItem->GetItemVectorPos(),pItem->GetGuid(),1);
	 packet.SetContainerType(pItem->GetItemVectorType());
	 NetworkSystem::GetSingleton()->SendPacket(&packet);

 }
X_VOID   SendLogicPacket::UseItem(const  vector<const Item *>& pVecItem,const  vector<int>& nums ,const ObjectHero* pHero)
{
	X_UINT size = pVecItem.size();
	if ( size == 0&&pHero == X_NULL )
	{
		return;
	}
	CGUseItemPacket packet;
	const Item* pItem = X_NULL;
	EM_ITEM_CONTAINER_TYPE type = EM_ITEM_CONTAINER_EQUIP;
	for (X_UINT i = 0 ;i< size ;i++)
	{
		pItem = pVecItem[i];
		if (!pItem)continue;
		type = pItem->GetItemVectorType();
		packet.AddItem(pItem->GetItemVectorPos(),pItem->GetGuid(),nums[i]);
	}
	packet.SetContainerType(type);
	if (pHero)
	{
		packet.SetTargetGUID(pHero->GetGuid());
	}
	NetworkSystem::GetSingleton()->SendPacket(&packet);
	/*packet.SetSourceContainerType(pItem->GetItemVectorType());
	packet.SetSourcePos(pItem->GetItemVectorPos());
	packet.SetSourceGuid(pItem->GetGuid());*/
}
X_VOID   SendLogicPacket::MoveItem(const  Item *pItem1,const  Item *pItem2)
{
	CGMoveItemPacket  packet;

	packet.SetSourceContainerType(pItem1->GetItemVectorType());
	packet.SetSourcePos(pItem1->GetItemVectorPos());
	packet.SetSourceGuid(pItem1->GetGuid());
	if (pItem2)
	{
		packet.SetDestContainerType(pItem2->GetItemVectorType());
		packet.SetDestPos(pItem2->GetItemVectorPos());
		packet.SetDestGuid(pItem2->GetGuid());
	}
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
bool     SendLogicPacket::CreateRole(X_INT heroId)
{
	const LoginData* pData = DataPool::GetSingleton()->getLoginData();
	if (!pData)
	{
		return false;
	}
	CGCreateRolePacket packet;
	packet.SetPlayerID(0);
	packet.SetUserID(pData->getUserId().c_str());
	packet.SetRoleName(pData->getLoginName().c_str());

	packet.SetPlayerID(0);
	packet.SetGiftHeroID(heroId);
	return NetworkSystem::GetSingleton()->SendPacket(&packet) == XTRUE;
}

X_VOID     SendLogicPacket::HeartBeat()
{
	 CGHeartBeatPacket packet;
	 NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	  SendLogicPacket::DistribHeroBearpoint(const vector<ObjectHero*> & heroes,const vector< int >& points )
{
	X_INT size  =  heroes.size();
	if (size == 0)
	{
		return;
	}
	CGDistribHeroBearpointPacket packet;
	
	ObjectHero *pHero = X_NULL;
	for (X_INT i = 0 ; i< size ;i++)
	{
		pHero = heroes[i];
		if (!pHero || points[i] == 0 )continue;
		 
		packet.AddHero(pHero->GetPos(),pHero->GetGuid(), points[i]);
	}

	 NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	   SendLogicPacket::BuyItem(EM_SHOP_IDTYPE SHOP_ID,const Item* pItem,X_INT num )
 {
	 if (!pItem || num <= 0)
	 {
		 return;
	 }
	 CGBuyShopItemPacket packet;
	 packet.SetItemCount(num);
	 packet.SetItemID(pItem->GetTableID());
	 packet.SetShopID(SHOP_ID);
	 NetworkSystem::GetSingleton()->SendPacket(&packet);
 }
X_VOID	   SendLogicPacket::SetMatrixHeros(const vector<ObjectHero*> & Heroes )
{
	ObjectManager *pm =DataPool::GetSingleton()->getObjectManager();
	const ObjectHero* pGoddess  =  static_cast<ObjectHero*>(pm->FindInstance(OBJECT_TYPE_HERO,pm->getSelf()->playerData()->GetGoddessHeroGuid()));
	 
	X_INT nullPos = -1; 
	 X_INT size = Heroes.size();
	CGSetMatrixObjectPacket packet;
	ObjectHero* pHero = X_NULL;
	for (X_INT i = 0; i< MAX_MATRIX_CELL_COUNT;i++ )
	{
		if ( i < size )
		{
			pHero = Heroes[i];
		} else
		{
			pHero = X_NULL;
		}
		if (!pHero)	
		{
			if (nullPos == -1)
			{
				nullPos = i;
			}
			continue;
		}
		packet.AddHero(i,pHero->GetGuid());
	}
	if (pGoddess&&nullPos !=-1)
	{
		packet.AddHero(nullPos,pGoddess->GetGuid());
	}
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	  SendLogicPacket::SetGoddessMatrix()
{
	ObjectManager *pm =DataPool::GetSingleton()->getObjectManager();
	const ObjectHero* Heroes  =  static_cast<ObjectHero*>(pm->FindInstance(OBJECT_TYPE_HERO,pm->getSelf()->playerData()->GetGoddessHeroGuid()));
	if (!Heroes)
	{
		return;
	}

	CGSetMatrixObjectPacket packet;
	ObjectSelf *pSelf = DataPool::GetSingleton()->getObjectManager()->getSelf();
	const vector<ObjectHero*> heros =  pSelf->playerData()->GetFightHero();
	ObjectHero* pHero = X_NULL;

	X_INT nullPos = -1; 
	for (X_INT i = 0; i< MAX_MATRIX_CELL_COUNT;i++)
	{
		pHero = heros[i];
		if (!pHero)
		{
			if (nullPos == -1)
			{
				nullPos = i;
			}
			continue;
		}
		packet.AddHero(i,pHero->GetGuid());
	}
	if ( nullPos !=-1)
		packet.AddHero(nullPos,Heroes->GetGuid());

	NetworkSystem::GetSingleton()->SendPacket(&packet);

}
X_VOID	   SendLogicPacket::Battle(X_CLIENT_GUID id, bool Monster,X_INT copySceneId)
{
	CGAskFightPacket packet;
	packet.SetObjType(!Monster);
	packet.SetTargetGuid(id);
	packet.SetCopySceneID(copySceneId);
	if(NetworkSystem::GetSingleton()->SendPacket(&packet))
	{
		DataPool::GetSingleton()->getCopySceneManager()->setFightSceneId(copySceneId);
	}
}
X_VOID	  SendLogicPacket::PickDropBox()
{
	CGDropItemPacket packet;
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
 X_BOOL	  SendLogicPacket::Chat(ENUM_CHAT_TYPE type,string str,X_CLIENT_GUID player)
 {
	 unsigned int size =  str.size();
	 if (size == 0)
	 {
         string tip = UtilTools::GET_TEXT_FROM_LANG(577);
         if (tip != "")
         {
             vector<string> strV;strV.clear();
             strV.push_back(tip);
             EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
             
         }
         return X_FALSE;
	 }
	
	 char _str[MAX_CHAT_SIZE] = {0} ;
     if (size >= MAX_CHAT_SIZE) {
         str =str.substr(0,MAX_CHAT_SIZE-1);
     }
	 strcpy(_str,str.c_str());
	 UtilTools::FilterText(_str);
	 CGChatPacket packet;
	 packet.SetChatType(type);
	 packet.SetContent(_str);
	 packet.SetTargetGuid(player);
	 packet.SetFaceCount(0);
	return  NetworkSystem::GetSingleton()->SendPacket(&packet);
 }
X_VOID	  SendLogicPacket::EquipMaker(const Item* pItem )
{
	if (!pItem)
	{
		return;
	}	
	CGEquipManufacturePacket packet;
	packet.SetPrescriptionID (EquipMaker::__FindEquipWithId(pItem->GetTableID()));
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}

X_BOOL	  SendLogicPacket::EquipMakerFrom(const Item* pItem )
{
	if (!pItem)
	{
		return X_FALSE;
	}	
	X_INT  productId  = EquipMaker::__FindEquipWithMaterialId(pItem->GetTableID());
	const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_EQUIP_MANUFACTURE);
	const stDBC_FILE_EQUIP_MANUFACTURE	* m_pTableData  = (const stDBC_FILE_EQUIP_MANUFACTURE*)pDataFile->GetFieldsByIndexKey(productId);
	if (!m_pTableData)return X_FALSE;
	 
	if( (m_pTableData->wood > 0) && (DataPool::GetSingleton()->getObjectManager()->getSelf()->playerData()->GetWood()) < m_pTableData->wood )
	{
		string tip = UtilTools::GET_TEXT_FROM_LANG(671);
		if (tip != "")
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);

		}

		return X_FALSE;
	}
	for (X_INT i =0;i<MAX_MATERIAL_NUM;i++)
	{
		if(m_pTableData->items[i].id == -1)continue;

			X_INT num = 	DataPool::GetSingleton()->getBagData()->getItemNumByTableId(m_pTableData->items[i].id);

			if (num <= 0)
			{
				string tip = UtilTools::GET_TEXT_FROM_LANG(672);
				if (tip != "") 
				{
					vector<string> strV;strV.clear();
					strV.push_back(tip);
					EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);

				}
				return X_FALSE;
			}
	}

	CGEquipManufacturePacket packet;
	packet.SetPrescriptionID (productId);
	return NetworkSystem::GetSingleton()->SendPacket(&packet);
	 
}
X_VOID	  SendLogicPacket::SkillUpgrade(const ObjectHero* pHero,X_INT skillId,const vector<Item*> & items,const  vector<int>& nums)
{
	X_UINT size = items.size();
	if (!pHero) return;
	CGAskSkillLevelUpPacket packet;
	packet.SetDestGuid(pHero->GetGuid());
	packet.SetSkillID(skillId);
	
	const Item* pItem = X_NULL;
	X_INT num = 0;
	for (X_UINT i = 0;i<size;i++)
	{
		pItem = items[i];
		if (pItem)
		{
			for (X_INT j = 0; j < nums[i];j++ )
			{
				packet.AddItem(pItem->GetGuid());
				num ++;
			}
			
		}
	}
	packet.SetItemCount(num);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID    SendLogicPacket::askSceneList(X_INT groupId,bool bSureChangeGroup )
{
	CopySceneGroup* pGroup = DataPool::GetSingleton()->getCopySceneManager()->getCopySceneGroupById(groupId);
	DataPool::GetSingleton()->getCopySceneManager()->setChangeGroup(bSureChangeGroup);
	if (pGroup && pGroup->isAsked())
	{
		if (bSureChangeGroup)
		{
			DataPool::GetSingleton()->getCopySceneManager()->setCurSceneGroup(pGroup);
		}
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_LEVELLIST_UPDATA);
		return;
	}
	CGAskCopySceneListPacket packet;
	packet.SetCopySceneGroupID(groupId);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}

X_VOID    SendLogicPacket::OpenMailBox() 
{
	CGMailAskOpenPacket packet;
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
 X_VOID    SendLogicPacket::DeleteMailByIndex(X_INT index)
 {
	 CGMailDelPacket packet;
	 packet.SetIndex(index);
	 NetworkSystem::GetSingleton()->SendPacket(&packet);
 }
 X_BOOL    SendLogicPacket::ReadMailByIndex(X_INT index)
 {
	 CGMailReadPacket packet;
	 packet.SetIndex(index);
	 return NetworkSystem::GetSingleton()->SendPacket(&packet);
 }
 
 X_VOID    SendLogicPacket::WriteMail(X_CLIENT_GUID guid,const string &title,const string & text)
 {
	 CGMailWritePacket packet;
	 packet.SetDestGuid(guid);
	 packet.SetTitle(title.c_str());
	 packet.SetContex(text.c_str());
	 NetworkSystem::GetSingleton()->SendPacket(&packet);
 }
X_VOID   SendLogicPacket::OpenMailAll(EM_TYPE_MAIL_CONTENT type)
{
	//0: ∆’Õ®, 1:’Ω∂∑, 2:∑•ƒæ≥°
	CGMailReadAllPacket packet;
	packet.SetType(type);
   NetworkSystem::GetSingleton()->SendPacket(&packet);

}
X_VOID   SendLogicPacket::DelMailAll(EM_TYPE_MAIL_CONTENT type)
 {
	 CGMailDelAllPacket packet;
	 packet.SetType(type);
	 NetworkSystem::GetSingleton()->SendPacket(&packet);
 }
X_VOID    SendLogicPacket::SarificeOper(EM_SACRIFICE_OPER_TYPE operType, X_INT id)
{
	CGSacrificePacket packet;
	packet.SetOperType(operType);
	packet.SetSacrificeID(id);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID    SendLogicPacket::EnterArena()
{
	CGArenaAskEnterPacket packet;
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID    SendLogicPacket::ChallengeArena(X_CLIENT_GUID guid)
{
	CGArenaChallengePacket packet;
	packet.SetGUID(guid);
	if(NetworkSystem::GetSingleton()->SendPacket(&packet))
	{
		DataPool::GetSingleton()->getCopySceneManager()->setFightSceneId(-1);
	}
}
X_VOID    SendLogicPacket::BuyActionPoint()
{
	CGBuyActionPointPacket packet;
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID    SendLogicPacket::SaleEquip(const  vector<const Item *>& pVecItem)
{
	X_UINT size = pVecItem.size();
	if ( size == 0  )
	{
		return;
	}
	CGSellItemPacket packet;
	const Item* pItem = X_NULL;
	EM_ITEM_CONTAINER_TYPE type = EM_ITEM_CONTAINER_EQUIP;
	for (X_UINT i = 0 ;i< size ;i++)
	{
		pItem = pVecItem[i];
		if (!pItem||!pItem->Rule(EM_Sale))continue;
		type = pItem->GetItemVectorType();
		packet.AddItem(pItem->GetItemVectorPos(),pItem->GetGuid(),1);
	}
	packet.SetContainer(type);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID    SendLogicPacket::AskHuoDong()
{
	
	if (!DataPool::GetSingleton()->baskHuoDong)
	{
		DataPool::GetSingleton()->baskHuoDong = true;
		CGAskHuoDongListPacket packet;
		NetworkSystem::GetSingleton()->SendPacket(&packet);
	}
}

X_VOID    SendLogicPacket::EnjoyHuoDong(HuoDong *hd)
{
	X_INT id = hd->getId();
	 if (id >= EM_ID_HUODONG_EATCHEESE1 && id<= EM_ID_HUODONG_EATCHEESE3)
	 {
		 CGEatCheesePacket packet;
		 packet.SetHuoDongID(id);
		 NetworkSystem::GetSingleton()->SendPacket(&packet);
	 }else if (id >= EM_ID_HUODONG_GANK1 && id<= EM_ID_HUODONG_DUIXIAN3)
	 {
		 CGRefreshCopyScenePacket packet;
		 packet.SetHuoDongID(id);
		if(NetworkSystem::GetSingleton()->SendPacket(&packet))
		{
			CopySceneGroup*  pGroup = DataPool::GetSingleton()->getCopySceneManager()->getCopySceneGroupById(HUODONG_COPYSCENE_GROUP);
			if (pGroup)
			{
				DataPool::GetSingleton()->getCopySceneManager()->setCurScene(pGroup->getCopySceneById(hd->getCopySceneId()));
			}
			DataPool::GetSingleton()->getCopySceneManager()->setFightSceneId(hd->getCopySceneId());
		}
	 }
}
X_VOID   SendLogicPacket::BuyBearPoint(X_INT id)
{
	CGBuyBearPointPacket packet;
	packet.SetID(id);
	NetworkSystem::GetSingleton()->SendPacket(&packet);

}
X_VOID  SendLogicPacket::Charge(X_INT id)
{

	CGAskChargePacket packet;
	packet.SetChargeID(id);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID  SendLogicPacket::ExChange(X_INT id)
{
	CGExchangeStonePacket packet;
	packet.SetExchangeID(id);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
		  
}
X_VOID  SendLogicPacket::AskAchievement()
{
	CGAskAchievementPacket packet;
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID  SendLogicPacket::RequestAchievement(X_INT id)
{
	CGGetAchievementAwardPacket packet;
	packet.SetAchieveID(id);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
	

}
X_VOID  SendLogicPacket::ClickGuideTip(X_INT id)
{
	 CGFreshGuidePacket packet;
	 packet.SetFreshGuideGroupID(id);
	 NetworkSystem::GetSingleton()->SendPacket(&packet);
}

X_VOID  SendLogicPacket::AskQuest()
{
	if(DataPool::GetSingleton()->getQuestData()->isAsked())return;
	CGAskMissionListPacket packet;
	NetworkSystem::GetSingleton()->SendPacket(&packet);
	
	
}
X_VOID  SendLogicPacket::SubmitQuest(X_INT id)
{
	CGSubmitMissionPacket packet;
	packet.SetMissionID(id);
	NetworkSystem::GetSingleton()->SendPacket(&packet);

}
X_VOID  SendLogicPacket::AskArenaDetail(X_CLIENT_GUID id)
{
	CGArenaAskDetailPacket packet;
	packet.SetGuid(id);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}

X_VOID SendLogicPacket::AskRobWood( X_INT id )
{
	CGWoodAskPacket  packet;
	packet.SetOptType(CGWoodAskPacket::WOODOPT(id));
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}

X_VOID SendLogicPacket::SetWoodMatrixHeros( X_GUID* pGuid )
{
	CGWoodSetMatrixPacket packet;
	packet.SetHeroGuid(pGuid);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}

X_VOID SendLogicPacket::AskMessageRevengeWood( X_INT messageIndex )
{
	CGWoodAskPacket  packet;
	packet.SetOptType(CGWoodAskPacket::WOODOPT_OPENREROB);
	packet.SetMailIndex( messageIndex);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::AskQuJingData()
{
	CGAskQuJingDataPacket packet;
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::OpenQuJingUi()
{
	CGOpenQuJingUIPacket packet;
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::QuJingHuSong()
{
	CGQuJingHuSongPacket packet;
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::QuJingRob(X_CLIENT_GUID guid)
{
	DataPool::GetSingleton()->BattlyType = EM_BATTLETYPE_QUJING;
	CGQuJingRobPacket packet;
	packet.SetRobGuid(guid);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::QuJingSetMatrixt(X_GUID* guid )
{
	CGQuJingSetMatrixPacket packet;
	packet.SetHeroGuid(guid);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::QuJingSpeedUp(X_CLIENT_GUID guid,X_INT type)
{
	CGQuJingSpeedUpPacket packet;
	packet.SetType(type);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::QuJingRefreshShiZhe(bool bTop)
{
	if (bTop)
	{
		CGRefreshQuJingTangSengPacket packet;
		NetworkSystem::GetSingleton()->SendPacket(&packet);
	 
	}else
	{  
		CGRefreshQuJingShiZhePacket packet;
		NetworkSystem::GetSingleton()->SendPacket(&packet);
		
	}
 
}
X_VOID	 SendLogicPacket::StairEnterPacket()
{
	CGStairAskPacket packet;
	packet.SetOptType(CGStairAskPacket::STAIROPT_ENTER);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::StairStartPacket()
{
	CGStairAskPacket packet;
	packet.SetOptType(CGStairAskPacket::STAIROPT_START);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::StairAddBufferPacket( X_INT buffer)
{
	CGStairAskPacket packet;
	packet.SetOptType(CGStairAskPacket::STAIROPT_PLUS);
	packet.SetPlusIndex(buffer);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_BOOL	 SendLogicPacket::StairMonsterPacket( X_INT monster)
{
	CGStairAskPacket packet;
	packet.SetOptType(CGStairAskPacket::STAIROPT_FIGHT);
	packet.SetMonsterGroup(monster);
	return NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::StairShowMonsterPacket( X_INT monster)
{
	CGStairAskPacket packet;
	packet.SetOptType(CGStairAskPacket::STAIROPT_SHOW);
	packet.SetMonsterGroup(monster);
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_BOOL	 SendLogicPacket::RockHer( X_INT num)
{
	CGRockHeroPacket packet;
	packet.SetRockTimes(num);
	return NetworkSystem::GetSingleton()->SendPacket(&packet);
}
X_VOID	 SendLogicPacket::GetGiftPackCard(X_INT type,const string &str  )
{
	if (str.size() <=0 )
	{
		return;
	}
	CGGetGiftpackCardPacket packet;
	packet.SetType(type);
	packet.SetCardSerial(str.c_str());
	NetworkSystem::GetSingleton()->SendPacket(&packet);
}
 