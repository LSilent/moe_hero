#ifndef __SENDPACKET_H__
#define __SENDPACKET_H__

#include "./base/Global.h"
#include "./Packets/Hero/CGRecruitHeroPacket.h"
#include "./Packets/Other/CGSacrificePacket.h"
#include "./Packets/Stair/CGStairAskPacket.h"

 class ObjectHero;
 class Item;
 class HuoDong;
 
class SendLogicPacket
{
	 public :
	// �������
	 static	X_VOID  askHumanDetail();
	 //����Ӣ��
	 static	X_VOID  askHeros(EM_HERO_CONTAINER_TYPE _vector);
	 //���󱳰�
	 static	X_VOID  askPacket(EM_ITEM_CONTAINER_TYPE _vector);

	 //Ӣ�۽���
	 static	X_VOID   ImproveHero(const ObjectHero *pHero);
	 //��ļӢ��

		/* EM_RECRUIT_HERO_FRESH,	//ˢ��
		   EM_RECRUIT_HERO_ALL,		//ȫ����ļ
		   EM_RECRUIT_HERO_SINGLE,	//��ļָ��λ��
		 */
	 static	X_VOID    RecruitHero(EM_RECRUIT_HERO_TYPE type,const ObjectHero *pHero = X_NULL);
	//������Ʒ
	 static	X_VOID    DropItem(const  Item *pItem);
	 
	 //ʹ����Ʒ
	 static	X_VOID    UseItem(const  vector<const Item *>& pVecItem,const  vector<int>& nums,const ObjectHero* pHero);
	 static	X_VOID   MoveItem(const  Item *pItem1,const  Item *pItem2);

	 static	X_VOID    UseItem(const Item * pItem, const ObjectHero* pHero = X_NULL);

	 static bool    CreateRole(X_INT heroId);
	 static X_VOID	  HeartBeat();

 
	 static X_VOID	  DistribHeroBearpoint(const vector<ObjectHero*> & heroes,const vector< int >& points );

	 static X_VOID	  BuyItem(EM_SHOP_IDTYPE SHOP_ID,const Item* pItem,X_INT num = 1);
	 static	X_VOID	  SetMatrixHeros(const vector<ObjectHero*> &Heroes );
	 static	X_VOID	  SetGoddessMatrix();
	 static	X_VOID	  Battle(X_CLIENT_GUID id, bool Monster = true,X_INT copySceneId = -1);
	 static X_VOID	  PickDropBox();

	 static X_BOOL	  Chat(ENUM_CHAT_TYPE type,string str,X_CLIENT_GUID player = INVALID_INDEX);

	 static X_VOID	  EquipMaker(const Item* pItem );
	 static X_BOOL	  EquipMakerFrom(const Item* pItem );

	  static X_VOID	  SkillUpgrade(const ObjectHero* pHero,X_INT skillId,const vector<Item*> & items,const  vector<int>& nums);

	  static X_VOID    askSceneList(X_INT groupId,bool bSureChangeGroup = false);

	  //���ʼ�����
	  static X_VOID    OpenMailBox();
	  static X_VOID    DeleteMailByIndex(X_INT index);
	  static X_BOOL    ReadMailByIndex(X_INT index);
	  static X_VOID    WriteMail(X_CLIENT_GUID guid,const string &title,const string & text);
	  static X_VOID   OpenMailAll(EM_TYPE_MAIL_CONTENT type);
	  static X_VOID   DelMailAll(EM_TYPE_MAIL_CONTENT type);

	  static X_VOID    SarificeOper(EM_SACRIFICE_OPER_TYPE operType, X_INT id);
	  
	  static X_VOID    EnterArena();
	  static X_VOID    ChallengeArena(X_CLIENT_GUID guid);

	  //��������
	  static X_VOID    BuyActionPoint();
	  static X_VOID    SaleEquip(const  vector<const Item *>& pVecItem);

	  static X_VOID    AskHuoDong();
	  static X_VOID    EnjoyHuoDong(HuoDong *hd);

	  static X_VOID   BuyBearPoint(X_INT id);

	  static X_VOID  Charge(X_INT id);
	  static X_VOID  ExChange(X_INT id);

	  static X_VOID  AskAchievement();
	  static X_VOID  RequestAchievement(X_INT id);
	  static X_VOID  ClickGuideTip(X_INT id);
	  static X_VOID  AskQuest();
	  static X_VOID  SubmitQuest(X_INT id);

	  //����
	  static X_VOID  AskArenaDetail(X_CLIENT_GUID id);

	  static X_VOID  AskRobWood(X_INT id);
	  static X_VOID  AskMessageRevengeWood(X_INT messageIndex);
	  //����ľ��Ӣ��
	  static X_VOID	 SetWoodMatrixHeros(X_GUID* pGuid);

	  static X_VOID	 AskQuJingData();
	  static X_VOID	 OpenQuJingUi();
	  static X_VOID  QuJingHuSong();
	  static X_VOID  QuJingRob(X_CLIENT_GUID guid);

	  static X_VOID	 QuJingSetMatrixt(X_GUID* guid );
	  static X_VOID  QuJingSpeedUp(X_CLIENT_GUID guid,X_INT type);
	  static X_VOID	 QuJingRefreshShiZhe(bool bTop = false);
  
	  static X_VOID	 StairEnterPacket();
	  static X_VOID	 StairStartPacket();
	  static X_VOID	 StairAddBufferPacket( X_INT buffer);
 	  static X_BOOL	 StairMonsterPacket( X_INT monster);
	  static X_VOID	 StairShowMonsterPacket( X_INT monster);

	  static X_BOOL	 RockHer( X_INT num);
	  
	  static X_VOID  GetGiftPackCard(X_INT type,const string &str  );//0 ��ѯ 1�콱

};


#endif