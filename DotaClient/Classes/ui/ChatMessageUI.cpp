#include "./ui/ChatMessageUI.h"
#include "./ui/ChatMessageUIView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

ChatMessageUI::ChatMessageUI()
{
	this->m_MutexGroup = 6;
}
ChatMessageUI::~ChatMessageUI()
{

}

X_VOID   ChatMessageUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_CHATMESSAGE_SHOW);
	m_Event.push_back(GAME_EVENT_CHATMESSAGE_UPDATA);
}
X_VOID	 ChatMessageUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_CHATMESSAGE_SHOW:
		{
			if (pEvent->m_vArg.size() >=1 )
			{
				if(pEvent->m_vArg[0] == string("close"))
				{
						this->Show(XFALSE);
						return;
				}
			}
			 
		}
		this->Show(XTRUE);
		break;
	case GAME_EVENT_CHATMESSAGE_UPDATA:
		this->UpData();
			break;
	default:
		break;
	}  
}

X_VOID	ChatMessageUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< ChatMessageUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	ChatMessageUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("ChatMessageUIView", ChatMessageUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("ChatMessage.ccbi");
    
    ccbReader->release();
}
