#include "./ui/UISystem.h"
#include "./ui/loginUi.h"
#include "./ui/MainPageUI.h"
#include "./ui/activitiesUI.h"
#include "./ui/battleFieldUI.h"
#include "./ui/SceneManger.h"
#include "./ui/logoUi.h"
#include "./ui/selectRoleUi.h"
#include "./ui/heroRecruitUI.h"
#include "./ui/heroBookUI.h"
#include "./ui/secretStoreUI.h"
#include "./ui/loadDistributeUI.h"
#include "./ui/heroInfoUI.h"
#include "./ui/heroFightChooseUI.h"
#include "./ui/bagOwnUI.h"
#include "./ui/teamListUI.h"
#include "./ui/equipmentInspectUI.h"
#include "./ui/equipmentAllUI.h"
#include "./ui/heroEvolveUI.h"
#include "./ui/heroUpgradeUI.h"
#include "./ui/skillInspectUI.h"
#include "./ui/settingUI.h"
#include "./ui/levelListUI.h"
#include "./ui/messageUI.h"
#include "./ui/rankListUI.h"
#include "./ui/altarUI.h"
#include "./ui/fightResultUI.h"
#include "./ui/TipUi.h"
#include "./ui/SkillUpgradeEquiUI.h"
#include "./ui/HeroEquipUI.h"
#include "./ui/equipmentSellUI.h"
#include "./ui/userInfoUI.h"
#include "./ui/cheeseActivityUI.h"
#include "./ui/NoticeUi.h"
#include "./ui/UserUpgradeUI.h"
#include "./ui/rechargeUI.h"
#include "./ui/ChatMessageUI.h"
#include "./ui/achievementUI.h"
#include "./ui/UpdataUi.h"
#include "./ui/taskInfoUI.h"
#include "./ui/userLoginUI.h"
#include "./ui/heroBaseActivityUI.h"
#include "./ui/OtherheroInfoUI.h"
#include "./ui/heroWoodFightChooseUI.h"
#include "./ui/EscortWoodUI.h"
#include "./ui/WoodShiZheUI.h"
#include "./ui/placardUI.h"
#include "./ui/giftDetailUI.h"

#include <algorithm>
#include "./DataBase/DataBaseSystem.h"
#include "cocos2d.h"

IMPLEMENT_SINGLETON(UISystem)
 
UISystem::UISystem()
{
	 
}
UISystem::~UISystem()
{

}
X_VOID		UISystem::Initial()
{
	m_AllLayoutWnd.clear();
	UI* pLayout = X_NULL;


	/*const  DataBase* pDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_UI);
	X_INT nLineNum = pDataFile->GetRecordsNum();
	for(X_INT i=0; i<nLineNum; i++)
	{
		const stDBC_FILE_UI* pDefine = (const stDBC_FILE_UI*)pDataFile->GetFieldsByLineNum(i);
		if(!pDefine) continue;
			 
	}	*/
	pLayout = new logoUi();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new selectRoleUi();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new loginUi();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new MainPageUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	/*pLayout = new ActivitiesUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);*/

	pLayout = new BattleFieldUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new HeroRecruitUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new HeroBookUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new SecretStoreUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new LoadDistributeUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new HeroInfoUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);



    pLayout = new HeroFightChooseUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new HeroWoodFightChooseUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new BagOwnUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new TeamListUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new EquipmentInspectUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new EquipmentAllUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new HeroEvolveUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new HeroUpgradeUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new SkillInspectUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new SettingUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new LevelListUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new MessageUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new RankListUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new AltarUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new FightResultUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout= new TipUi();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	
	pLayout= new SkillUpgradeEquiUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	
	pLayout= new HeroEquipUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout= new equipmentSellUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout= new userInfoUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	
	pLayout= new cheeseActivityUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout= new NoticeUi();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	
	pLayout= new UserUpgradeUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout= new rechargeUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);
	
	
	pLayout= new ChatMessageUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	b_lock = false;

	pLayout= new achievementUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new UpdataUi();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);
	
	pLayout = new taskInfoUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new userLoginUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new heroBaseActivityUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new OtherHeroInfoUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);

	pLayout = new EscortWoodUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);
	pLayout = new WoodShiZheUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);
	pLayout = new placardUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);
	pLayout = new giftDetailUI();
	pLayout->Init();
	m_AllLayoutWnd.push_back(pLayout);
	

	m_preUi = X_NULL;

}
X_VOID		UISystem::Tick(X_UINT nTime)
{

}
X_VOID		UISystem::Release()
{
	WND_ITER iend =  m_AllLayoutWnd.end();
	for (WND_ITER it = m_AllLayoutWnd.begin(); it != iend ;it++)
	{
	 
		const_cast<UI*>(*it)->Release();
		SAFE_DELETE (*it);
	}
 
	m_AllLayoutWnd.clear();
	m_ShowLayoutWnd.clear();
}
void    UISystem::onFrontUI(UI *  pLayout)
{
	if(!pLayout) return ;
	WND_ITER ifind = std::find(m_ShowLayoutWnd.begin(),m_ShowLayoutWnd.end(),pLayout);
	if (ifind != m_ShowLayoutWnd.end())
	{
		m_ShowLayoutWnd.erase(ifind);
	}
	m_ShowLayoutWnd.push_back(pLayout);
	m_preUi = getCurrentHanlerUi();
	SceneManger::GetSingleton()->FrontChild(pLayout->m_pUi,pLayout->bHandleTouchEvent);

}
X_VOID	UISystem::onUIShowHide( UI *  pLayout,X_BOOL show)
{
	if(!pLayout) return ;
	WND_ITER ifind = std::find(m_ShowLayoutWnd.begin(),m_ShowLayoutWnd.end(),pLayout);
	if (ifind != m_ShowLayoutWnd.end())
	{
		m_ShowLayoutWnd.erase(ifind);
	}
	if(show)
	{
		m_ShowLayoutWnd.push_back(pLayout);
		m_preUi = getCurrentHanlerUi();
	}
	cocos2d::CCNode * pNode = pLayout->GetWindow();
	if (!pNode)
	{
		return;
	}
	if(show)
	{
		pLayout->OnShow();
		SceneManger::GetSingleton()->AddChildToScene(pNode,pLayout->bHandleTouchEvent);
		
	}
	else
	{
		SceneManger::GetSingleton()->RemoveChildFormScene(pNode,XTRUE);
		//pLayout->ReleaseUI();
	}
	 
	
}
 
X_BOOL    UISystem::IsLayoutShow(const string& strLayout,const string&  strWnd)
{
	WND_ITER it = m_ShowLayoutWnd.begin();
	string  strWndName; 
	for ( ;it!= m_ShowLayoutWnd.end();++it)
	{
		strWndName = (*it)->GetName();
		if ( strWndName == strLayout )
		{
			if ((strWnd != ""))
			{
				 return XFALSE;
			}
			else
			{
				  return XTRUE;
			}
		}
	}
	return XFALSE;
}
UI*		UISystem::getWndControl(const string& strLayout)
{
	WND_ITER it = m_ShowLayoutWnd.begin();
	string  strWndName; 
	for ( ;it!= m_ShowLayoutWnd.end();++it)
	{
		strWndName = (*it)->GetName();
		if ( strWndName == strLayout )
		{
			return *it;
		}
	}
	return X_NULL;
}
X_VOID   UISystem::OnGameEvent(const tGameEventData* pEvent, X_UINT dwOwnerData)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return ;
	UI *pLayout =  (UI *)(dwOwnerData); 
	if(!pLayout) return;
	 pLayout->OnGameEvent(pEvent);
  
}
X_BOOL	UISystem::CheckMutex( const UI *  pLayout)
{
	if (!pLayout)
	{
		return XFALSE;
	}

	X_INT mutexGroup = pLayout->GetMutexGroup();
	if (mutexGroup < 0 || 	mutexGroup >= MAX_MUTEX_GROUP )
	{
		return XTRUE;
	}

	//所有显示的ui分到相应的互斥组
	WND_ITER it; 
	LAYOUTWNDLIST  mutexGroupvector[MAX_MUTEX_GROUP];
	for( X_INT i = 0; i< MAX_MUTEX_GROUP; i++)
		{
			mutexGroupvector[i].clear();
		}

	for ( it = m_ShowLayoutWnd.begin(); it != m_ShowLayoutWnd.end(); ++it)
		{
			if ((*it)==X_NULL ||(*it) == pLayout)
			{
				continue;
			}
			if (! (*it)->IsShow())
				{
					continue;
				}
			X_INT TempMutexGroup = (*it)->GetMutexGroup();
			if(TempMutexGroup < 0 || TempMutexGroup >= MAX_MUTEX_GROUP )
				{
					continue;
				}
			mutexGroupvector[TempMutexGroup].push_back(*it);			
		}		
		const  DataBase* pUiMutexDataFile  = DataBaseSystem::GetSingleton()->GetDataBase(DBC_FILE_UIMUTEX);
		const stDBC_FILE_UIMUTEX* pDefine = (const stDBC_FILE_UIMUTEX*)pUiMutexDataFile->GetFieldsByIndexKey(mutexGroup);
		if (!pDefine)
			{
				return XFALSE;
			}
	//处理其他界面关系 EM_Mutex_Forbid相关的 
	for(X_INT i = 0; i< MAX_MUTEX_GROUP; i++)
		{
			if (i == mutexGroup)
			{
				continue;
			}
			// 监测到有不允许当前界面打开的ui组存在显示，返回 XFALSE 标识不允许打开当前界面
			if ( UI::EM_Mutex_Forbid == static_cast<UI::EM_RULE_UIMUTEX>(pDefine->m_MutexGroup[i]))
			{
				if (!mutexGroupvector[i].empty())
				{
					return XFALSE;
				}
			}
		}
	//处理其他界面关系
    // 同组界面 -1表示多开，可并存，0表示不允许多开。  
	 if ( -1 == pDefine->m_MutexGroup[mutexGroup])
	 {
		// 不做任何处理
	 }
	 else
	 {
		// 关闭同组其他的界面
		WND_ITER iFinder; 
		iFinder = find(mutexGroupvector[mutexGroup].begin(),mutexGroupvector[mutexGroup].end(),pLayout);
		if (iFinder != mutexGroupvector[mutexGroup].end())
		{
			mutexGroupvector[mutexGroup].erase(iFinder);
		}
		WND_ITER  iter = mutexGroupvector[mutexGroup].begin();
		for (; iter!= mutexGroupvector[mutexGroup].end();++iter)
			{
				 (*iter)->Show(XFALSE); 
			}
	 }
	 // 处理其他组关系
	 for(X_INT i = 0; i< MAX_MUTEX_GROUP; i++)
		 {
		 if (i == mutexGroup)
			 {
				 continue;
			 }
		 //开始本界面，需要关闭其他组
		 if ( UI::EM_Mutex_Close == static_cast<UI::EM_RULE_UIMUTEX>(pDefine->m_MutexGroup[i]))
			 {
				 WND_ITER iter; 
				 for (iter = mutexGroupvector[i].begin(); iter!= mutexGroupvector[i].end();++iter)
					 {
						 (*iter)->Show(XFALSE); 
					 }
			 }
		 }
	return XTRUE;
}
X_VOID  UISystem::CleanShowList(const UI* pLayout)
{
	WND_ITER ifind = std::find(m_ShowLayoutWnd.begin(),m_ShowLayoutWnd.end(),pLayout);
	if (ifind != m_ShowLayoutWnd.end())
	{
		m_ShowLayoutWnd.erase(ifind);
	}
	if (b_lock)
	{
		return;
	}
	UI* pui = getCurrentHanlerUi();
	if (pui)
	{
		if (pui == m_preUi)
		{ 
			#ifdef UI_SHOW_RECREAT
			#else
			 //UISystem::GetSingleton()->onFrontUI(pui);
			#endif
			return;
		}
		m_preUi = pui;
		pui->Show(XTRUE);
	}
}
X_BOOL	UISystem::isMain()
{
	 
	UI *pUi = m_ShowLayoutWnd.back();
	if (pUi &&pUi->bHandleTouchEvent&&pUi->m_Name ==  "main")
	{
		return XTRUE;
	}
	return XFALSE;
}
UI*    UISystem::getCurrentHanlerUi()
{
	UI *pUi = X_NULL;
	LAYOUTWNDLIST::reverse_iterator ib = m_ShowLayoutWnd.rbegin();
	for ( ; ib != m_ShowLayoutWnd.rend();++ib )
	{
		pUi =  *ib;
		if (!pUi || !pUi->bHandleTouchEvent)continue;
		 return pUi;
	}
	return pUi;
}
//如果显示 不是最前窗体就bu更新了 解决穿透问题。因为更新会导致ui里面的控件重新创建 注册事件 导致level重新提级。
bool    UISystem::isCanUpdate(const UI*  pui)
{

#ifdef UI_SHOW_RECREAT
	const UI*  pTopUi =  getCurrentHanlerUi();
	if (!pTopUi || pTopUi == pui)
	{
		return true;
	}
	return false;
#else


	return true;
#endif

	
}