#include "./ui/EquipmentAllUI.h"
#include "./ui/EquipmentAllUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./base/UtilTools.h"

USING_NS_CC_EXT;

EquipmentAllUI::EquipmentAllUI()
{
	this->m_MutexGroup =0;
	nTablePage = 0;
	nPage = 0;
}
EquipmentAllUI::~EquipmentAllUI()
{

}

X_VOID   EquipmentAllUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_EQUIPMENTALL_SHOW);
	m_Event.push_back(GAME_EVENT_EQUIPMENTALL_UPDATA);
	

}
X_VOID	 EquipmentAllUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_EQUIPMENTALL_SHOW:
		{
			if (pEvent->m_vArg.size() > 0) 
			{
				nTablePage = UtilTools::StringToInt( pEvent->m_vArg[0].c_str());
			}

			this->Show(XTRUE);
		}

		break;
	case GAME_EVENT_EQUIPMENTALL_UPDATA:
		this->UpData();
		break;
	default:
		break;
	}  
}

X_VOID	EquipmentAllUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< EquipmentAllUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	EquipmentAllUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("EquipmentAllUIView", EquipmentAllUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
	m_pUi = ccbReader->readNodeGraphFromFile("EquipmentAll.ccbi");
    
    ccbReader->release();
}
