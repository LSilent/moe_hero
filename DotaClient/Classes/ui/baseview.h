#ifndef __BASEVIEW_H__
#define __BASEVIEW_H__

#include "cocos2d.h"
#include "./ui/ui.h"
#include "./ui/UISystem.h"
 
class BaseView :public cocos2d::CCLayer
{
public:
	 
   virtual void onExit()
   {
	  
	
	   UI *pUi = ( UI *)(this->getUserData());

	   if (pUi)
	   {
		   pUi->ReleaseUI();
		   UISystem::GetSingleton()->CleanShowList(pUi);
	   }

	   CCLayer::onExit();
	  
   }
    


};




#endif
