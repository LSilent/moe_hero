#include "./ui/equipmentInspectUI.h"
#include "./ui/equipmentInspectUIView.h"
#include "./ui/element/mainNavgView.h"
#include "./datapool/EquipOperator.h"

USING_NS_CC_EXT;

EquipmentInspectUI::EquipmentInspectUI()
{
	this->m_MutexGroup = 2;
}
EquipmentInspectUI::~EquipmentInspectUI()
{

}

X_VOID   EquipmentInspectUI::CareEvent()
{
	m_Event.push_back(GAME_EVENT_EQUIPMENTINSPECT_SHOW);
	m_Event.push_back(GAME_EVENT_EQUIPMENTINSPECT_UPDATA);
	m_Event.push_back(GAME_EVENT_EQUIPMENTINSPECT_CLOSE);
}
X_VOID	 EquipmentInspectUI::OnGameEvent(const tGameEventData* pEvent)
{
	if ( !pEvent || !(pEvent->m_pEventDef) ) return;
	switch (pEvent->m_pEventDef->m_nEventIntID)
	{
	case GAME_EVENT_EQUIPMENTINSPECT_SHOW:
		this->Show(XTRUE);
		break;
	case GAME_EVENT_EQUIPMENTINSPECT_UPDATA:
		this->UpData();
		break;
	case GAME_EVENT_EQUIPMENTINSPECT_CLOSE:
		{
			this->Show(XFALSE);
			EquipMaker::Release();
		}
		
	default:
		break;
	}  
}

X_VOID	EquipmentInspectUI::UpData()
{
	if (m_bShow == XFALSE) return;
	 if(! UISystem::GetSingleton()->isCanUpdate(this) )return;
	static_cast< EquipmentInspectUIView* >( m_pUi )->onDataUpdate( true );
}

X_VOID	EquipmentInspectUI::OnCreate()
{
	if (m_pUi) return;
	 
	/* Create an autorelease CCNodeLoaderLibrary. */
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    
    ccNodeLoaderLibrary->registerCCNodeLoader("EquipmentInspectUIView", EquipmentInspectUIViewLoader::loader());
	ccNodeLoaderLibrary->registerCCNodeLoader("MainNavgView", MainNavgViewLoader::loader());

    /* Create an autorelease CCBReader. */
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    
    /* Read a ccbi file. */
    m_pUi = ccbReader->readNodeGraphFromFile("EquipmentInspect.ccbi");
    
    ccbReader->release();
}
