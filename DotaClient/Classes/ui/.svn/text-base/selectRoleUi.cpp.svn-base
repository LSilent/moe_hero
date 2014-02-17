#include "./ui/selectRoleUi.h"
#include "./ui/selectRoleView.h"
#include "./Packets/Login/CGCreateRolePacket.h"
#include "./datapool/DataPool.h"
#include "./net/NetworkSystem.h"
#include "./game/SendPacket.h"

selectRoleUi::selectRoleUi()
{
	 
}
selectRoleUi::~selectRoleUi()
{
 
}

X_VOID   selectRoleUi::CareEvent()
{
	m_Event.push_back(GAME_EVENT_SELECTROLE_SHOW);
	m_Event.push_back(GAME_EVENT_MAINPAGE_SHOW);
 
}

X_VOID		 selectRoleUi::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_SELECTROLE_SHOW:
		this->Show(XTRUE);
		cocos2d::CCLog("---------------------------selectRoleUi::OnGameEvent   Show");
		break;
	case GAME_EVENT_MAINPAGE_SHOW:
		this->Show(XFALSE);
		break;
	default:
		break;
	}  
	 
}
X_VOID	selectRoleUi::OnCreate()
{
	if (m_pUi) return;
	selectRoleView *layer=  selectRoleView::create();
	m_pUi  = (cocos2d::CCNode*)layer;
	m_pUi->setUserData(this);
}
X_VOID   selectRoleUi::onEnterClick()
{
	if( SendLogicPacket::CreateRole(7))
    {
          DataPool::GetSingleton()->setRoleCreate(true);
    }
}