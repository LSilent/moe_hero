#include "./ui/messageUI.h"
#include "./ui/messageUIView.h"
#include "./ui/element/mainSatusView.h"
#include "./ui/element/mainNavgView.h"

USING_NS_CC_EXT;

MessageUI::MessageUI()
{
	this->m_MutexGroup = 6;
}
MessageUI::~MessageUI()
{

}

X_VOID   MessageUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_MESSAGE_SHOW);
	m_Event.push_back(GAME_EVENT_MESSAGE_UPDATA);
	

}
X_VOID	 MessageUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_MESSAGE_SHOW:
		{
			if (pEvent->m_vArg.size()>0)
			{
				if(pEvent->m_vArg.at(0) == "close")
				{
					this->Show(XFALSE);
					return;
				}
			}
		}
		this->Show(XTRUE);
		break;
	case GAME_EVENT_MESSAGE_UPDATA:
		this->UpData();
			break;
	default:
		break;
	}  
}

X_VOID	MessageUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< MessageUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	MessageUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("MessageUIView", MessageUIViewLoader::loader());
 

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("Message.ccbi");
    
    ccbReader->release();
}
