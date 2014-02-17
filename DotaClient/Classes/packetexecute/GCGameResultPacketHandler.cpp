 
#include "./Packets/GCGameResultPacket.h"
#include "./base/UtilTools.h"
#include "./cocos2d.h"
#include "./event/EventSystem.h"
#include "./DataBase/DataBaseSystem.h"
#include "./sound/SoundSystem.h"
#include "./ui/SceneManger.h"
#include "./game/MainGame.h"
#include "./datapool/DataPool.h"
#include "./base/Sdk_Handler.h"


X_INT GCGameResultPacketHandler::Execute( GCGameResultPacket* pPacket, Player* pPlayer ) 
{
	if(pPacket == X_NULL) return 0;

	GAME_OPERATOR_RET gr = (GAME_OPERATOR_RET)pPacket->GetResultID();


	if (gr == BUY_ACTIONPOINT_CHARGE_NOT_ENOUGH)
	{
		EventSystem::GetSingleton()->PushEvent(GAME_EVENT_USER_INFO_BUY_ACTION);
		return 1;
	}
	string tip = UtilTools::GET_TEXT_FROM_LANG(gr);
	if (tip != "")
	{
		if(gr == GAME_VERSION_ERROR  && pPacket->GetParam() == 1)
		{
			// do nothing 

		}else
		{
			vector<string> strV;strV.clear();
			strV.push_back(tip);
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_TIP_UPDATA,strV);
		}
	
	
 
		 
	}
	switch (gr)
	{
	case HUMAN_LEVEL_NOT_ENOUGH:
		break;
	case MONEY_NOT_ENOUGH:
		break;
	case GOLD_NOT_ENOUGH:
		break;
	case ITEM_NOT_ENOUGH:
		break;
	case BEARPOINT_NOT_ENOUGH:
		break;
	case ACTION_NOT_ENOUGH:
		break;
	case BAG_NOT_ENOUGH:
		break;
	case EQUIPCONTAINER_NOT_ENOUGH:
		break;
	case TARGET_HUMAN_OFFLINE:
		break;
	case ACTION_TOPLIMIT:
		break;
	case HUODONG_NOT_ACTIVE:
		break;
	case WOOD_NOT_ENOUGH:
		break;
	case STONE_NOT_ENOUGH:
		break;
	case HERO_BEARPOINT_NOT_ENOUGH:
		break;
	case GAME_VERSION_ERROR:
        {
			X_INT param = pPacket->GetParam();//0 客户端版本低 // 1 客户端版本高
			SdkHandler::onGameVersionError(param == 1);
        }
		break;
	case ITEM_SUCCESS:
		break;
	case ITEM_SUCCESS_NOCHANGE:
		break;
	case ITEM_FAIL_INVALID:
		break;
	case ITEM_FAIL_SOURCEITEM_NULL:
		break;
	case ITEM_FAIL_SOURCEITEM_LOCK:
		break;
	case ITEM_FAIL_SOURCEITEM_BIND:
		break;
	case ITEM_FAIL_SOURCEITEM_ALIVE:
		break;
	case ITEM_FAIL_SOURCEITEM_USE:
		break;
	case ITEM_FAIL_SOURCEITEM_NOUSE:
		break;
	case ITEM_FAIL_DESTCONTAINER_NOT_ENOUGH:
		break;
	case ITEM_FAIL_DESTITEM_ALIVE:
		break;
	case ITEM_FAIL_DESTITEM_NULL:
		break;
	case ITEM_FAIL_DESTITEM_LOCK:
		break;
	case ITEM_FAIL_DESTITEM_FULL:
		break;
	case ITEM_FAIL_SOURCEITEM_NOSPLIT:
		break;
	case ITEM_FAIL_SOURCEITEM_SPLITCOUNT:
		break;
	case ITEM_FAIL_ITEM_NOT_ENOUGH:
		break;
	case ITEM_FAIL_CANNOT_LAYED:
		break;
	case ITEM_FAIL_CANNOT_DROP:
		break;
	case ITEM_FAIL_EQUIPLEVEL:
		break;
	case ITEM_FAIL_EQUIPPROFESSION:
		break;
	case ITEM_FAIL_SOURCEITEM_NOEQUIP:
		break;
	case ITEM_FAIL_EQUIPPOINT:
		break;
	case ITEM_FAIL_UNIQUE:
		break;
	case ITEM_FAIL_NOT_ENOUGH_BEARPOINT:
		break;
	case CREATEROLE_SUCCESS:
		break;
	case CREATEROLE_FAIL_ILLEGAL_NAME:
	case CREATEROLE_FAIL_SAME_NAME:
	case CREATEROLE_FAIL_TOPLIMIT:
	case CREATEROLE_FAIL_HAVE:
	case CREATEROLE_FAIL_INVALID:
        {
            if(DataPool::GetSingleton())
            {
                DataPool::GetSingleton()->setRoleCreate(false);
            }
        }
		break;
	case HERO_SUCCESS:
		break;
	case HERO_FAIL_INVALID:
		break;
	case HERO_FAIL_SOURCEHERO_NULL:
		break;
	case HERO_FAIL_SOURCEHERO_ALIVE:
		break;
	case HERO_FAIL_DESTCONTAINER_FULL:
		break;
	case HERO_RECRUIT_SUCCESS:
		{
			const DataBase* pfile = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_HERO_ATTR);
			if (pfile)
			{
				const stDBC_FILE_HERO_ATTR *pData = (const stDBC_FILE_HERO_ATTR * )pfile->GetFieldsByIndexKey(pPacket->GetParam()); 
				if (pData)
				{
					SoundSystem::GetSingleton()->playEffect(pData->_sound);
				}
			}
		}
		break;
	case HERO_RECRUIT_FAIL_DESTCONTAINER_FULL:
		break;
	case HERO_RECRUIT_FAIL_SOURCEHERO_INVALID:
		break;
	case HERO_RECRUIT_FAIL_CANNOT_RECRUIT:
		break;
	case HERO_RECRUIT_FAIL_LEFTTIME:
		break;
	case HERO_RECRUIT_FAIL_INVALID:
		break;
	case HERO_IMPROVE_SUCCESS:
		break;
	case HERO_IMPROVE_FAIL_MAX_QUALITY:
		break;
	case HERO_DISTRIB_SUCCESS:
		break;
	case HERO_DISTRIB_FAIL_INVALID:
		break;
	case HERO_MAX_LEVEL:
		break;
	case MATRIX_SUCCESS:
		break;
	case MATRIX_FAIL_PROF_CLOSE:
		break;
	case MATRIX_FAIL_REPEAT:
		break;
	case MATRIX_FAIL_HERO_TOPLIMIT:
		break;
	case SHOP_BUYITEM_SUCCESS:
		break;
	case SHOP_BUYITEM_FAIL:
		break;
	case SHOP_BUY_GOLD_NOENOUGH:
		break;
	case SHOP_SELL_FAIL:
		break;
	case SKILLUP_SUCCESS:
		{
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_SKILLUPGRADE_STATUS_SUCCESS);
		}
		break;
	case SKILLUP_FAIL_NO_SKILL:
		break;
	case SKILLUP_FAIL_MAX_LEVEL:
		break;
	case SKILLUP_FAIL_LOWRATE:
		break;
	case SKILLUP_FAIL_HERO_LEVEL:
		break;
	case COPYSCENE_CLOSE:
		break;
	case SACRIFICE_ENTER_SUCCESS:
		break;
	case SACRIFICE_PRAY_SUCCESS:
		break;
	case ARENA_FAIL_LOWLEVEL:
		break;
	case ARENA_FAIL_GOLDNOTENOUGH:
		break;
	case CHESS_GAME_OVER:
		break;
	case CHESS_GAME_RESET:
		break;
	case BUY_BEARPOINT_MAXTIMES:
		break;
	case PAY_SUCCESS:
		break;

		//伐木场tip消息
	case WOOD_FAIL_LOWLEVEL:
		break;
	case WOOD_FAIL_ROBCOUNT:
		break;
	case WOOD_FAIL_SAFETIME:
		break;
	case WOOD_FAIL_MATCH:
		break;
	case WOOD_FAIL_MATCHGOLD:
		break;
	case WOOD_FAIL_MATCHTIMES:
		break;
	case WOOD_FAIL_MAXLEVEL:
		break;
	case WOOD_FAIL_LEVELUP:
		break;
	case WOOD_FAIL_LEVELUPING:
		break;
	case GIFTPACK_CARD_QUERY_OK:				//激活卡号查询成功
		{
			X_INT param = pPacket->GetParam(); 
			vector<string>str;str.clear();
			str.push_back(UtilTools::IntToString(param));
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_GIFTDETAIL_SHOW,str);

		}
		break;
	case GIFTPACK_CARD_QUERY_ERROR:				//激活卡号不存在
		break;
	case GIFTPACK_CARD_RECV_OK:				//领取成功
		{
			X_INT param = pPacket->GetParam(); 
			vector<string>str;str.clear();
			str.push_back(UtilTools::IntToString(param));
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_GIFTDETAIL_SHOW,str);
		}
		break;
	 
	case GIFTPACK_CARD_DONE:				//激活卡已被领取
		{
			vector<string>str;str.clear();
			str.push_back(UtilTools::IntToString(-1));
			EventSystem::GetSingleton()->PushEvent(GAME_EVENT_GIFTDETAIL_SHOW,str);
		}
		break;
	case QUJING_FAIL_REFRESH_MAX_LEVEL:	//使者已达最高等级，不需刷新
			break;
	case QUJING_FAIL_HUSONG_MAX_TIMES:		//护送已达最大次数
			break;
	case QUJING_FAIL_ROB_MAX_TIMES:			//拦劫已达最大次数
			break;
	case QUJING_FAIL_BE_ROBBED_MAX_TIMES:	//目标拦劫已达最大次数
			break;
	case QUJING_FAIL_ROB_CD:				//拦劫CD未完
			break;
	case QUJING_ROB_OK:					//拦劫成功
			break;
	case QUJING_FAIL_SETMATRIX:			//上阵失败
			break;
	case QUJING_FAIL_HEROCOUNT:			//英雄未全部收集
			break;
	case QUJING_FAIL_HUSONG_NOW:			//已经在护送中
		break;
			
		break;
	default:
		break;
	}  

	return 1;
}