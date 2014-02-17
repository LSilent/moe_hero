#include "./ui/UpdataView.h"
 
#include "./ui/UpdataUi.h"

#include "./ui/element/ProgressView.h"
#include "./load/ResourceCheck.h"
#include "./game/MainGame.h"

#define DIALOG_TAG_NET_ERROR 1
#define DIALOG_TAG_UNCOMPRESS 2

bool UpdataView::init()
{
	retryNum =0;
	retryNumcompress = 0;
	m_dialog = 0;
    bool bRet = false;
	b_updata=false;
	mExpProgress = X_NULL;
	pLabel = X_NULL;
    do 
    { 
		CCSize size = CCDirector::sharedDirector()->getVisibleSize();
        CCSprite* pSprite = CCSprite::create("logo.jpg");
        CC_BREAK_IF(! pSprite);
        pSprite->setPosition(ccp(size.width/2, size.height/2));
        this->addChild(pSprite, 0);

		pSprite->setScaleX(SCALE_X );
		pSprite->setScaleY(SCALE_Y );

			CCSprite *tip = CCSprite::create("n_login_upg_tip.png");
			tip->setPosition(ccp(size.width * 0.5f , size.height * 0.19f));
			this->addChild(tip);

			CCSprite *progressBg = CCSprite::create("n_login_upg_bg.png");
			progressBg->setPosition(ccp(size.width * 0.5f , size.height * 0.13f));
			this->addChild(progressBg);

			mExpProgress = ProgressView::createProgress("n_login_upg_prog.png");
			mExpProgress->setContentSize(CCSize(size.width-40,20));
			mExpProgress->setAnchorPoint(ccp(0,0.5));
			/*mExpProgress->setPosition(ccp( 40, 0.5 *size.height ));*/
			mExpProgress->setPosition(ccp(progressBg->getPositionX() - progressBg->getContentSize().width * 0.5, progressBg->getPositionY()));
			mExpProgress->setProgressValue(0,1,PROGRESS_ADD,false);
			this->addChild(mExpProgress,1);
			getScheduler()->scheduleSelector( cocos2d::SEL_SCHEDULE(&UpdataView::updateRES),this,1,kCCRepeatForever,0,XFALSE);

			pLabel = CCLabelTTF::create("", FONT_NAME_ARIAL_BOLD, 24);
			CC_BREAK_IF(! pLabel);
			/*pLabel->setPosition(ccp(size.width / 2, 0.5 *size.height+10));*/
			pLabel->setPosition(progressBg->getPosition());
			this->addChild(pLabel, 2);
        bRet = true;
    } while (0);


X_INT code =  ResourceCheck::GetSingleton()->getErrCode();//Game::CheckVersion() 的结果码
		//if (Game::CheckVersion())
		if(code == -1)//  进入到这个视图表示Game::CheckVersion()结果为true。     -2表示需要更新   kNetwork表示监测失败了
		{
			b_updata = true;
			Game::CheckUpData();
		}
		else
		{
			handleError(code);
			// MainGame::GetSingleton()->SetGameMainProState(MainGame::RUNING_IN_LOGIN);
		} 
		
    return bRet;
}
void UpdataView::handleError(X_INT code)
{
	switch (code)
	{
	case -1://成功
		break;
	case AssetsManager::kNetwork:
		{
			retryNum++;
			if (retryNum < 10 )
			{
				this->unscheduleAllSelectors();
				if(Game::CheckVersion())
					Game::CheckUpData();
				getScheduler()->scheduleSelector( cocos2d::SEL_SCHEDULE(&UpdataView::updateRES),this,1,kCCRepeatForever,0,XFALSE);
			}else
			{
					if (!m_dialog)
					{
						this->unscheduleAllSelectors();
						string str = UtilTools::GET_TEXT_FROM_LANG(590);
						str += " ";
						str +=  UtilTools::IntToString(retryNum);
						m_dialog = ModalDialogView::createDialog(str.c_str(),this,DIALOG_MODEL_SINGLE);
						m_dialog->setTag(DIALOG_TAG_NET_ERROR);
						addChild(m_dialog,1000);
					}
			}
			return;
		}
		break;
	case AssetsManager::kUncompress:
		{
			retryNumcompress++;
			if (retryNumcompress < 10 )
			{
				this->unscheduleAllSelectors();
				Game::CheckUpData();
				getScheduler()->scheduleSelector( cocos2d::SEL_SCHEDULE(&UpdataView::updateRES),this,1,kCCRepeatForever,0,XFALSE);
			}else
			{
				if (!m_dialog)
				{
					this->unscheduleAllSelectors();
					string str = UtilTools::GET_TEXT_FROM_LANG(706);
					str += " ";
					str +=  UtilTools::IntToString(retryNumcompress);
					m_dialog = ModalDialogView::createDialog(str.c_str(),this,DIALOG_MODEL_SINGLE);
					m_dialog->setTag(DIALOG_TAG_UNCOMPRESS);
					addChild(m_dialog,1000);
				}
			}
			return;
		}
		break;
	}

}
void UpdataView::updateRES(float dt )
{
	X_INT progress = ResourceCheck::GetSingleton()->getProgress();
	if (mExpProgress)
	{
		 mExpProgress->setProgressValue(progress,1,PROGRESS_ADD,false);
	}
	
	 char str[20]= {0};
	 sprintf(str,"%d%%",progress);
	 if(pLabel)	 pLabel->setString(str);
	 X_INT code =  ResourceCheck::GetSingleton()->getErrCode();
	 handleError(code);

	 if (progress >= 100)
	 {
		 CCLog("----------------------------------------UpdataView::progress >= 100 " ,progress );
		 if (ResourceCheck::GetSingleton()->isDoned())
		 {
			 CCLog("----------------------------------------UpdataView::RUNING_IN_LOGIN"  );
			MainGame::GetSingleton()->SetGameMainProState(MainGame::RUNING_IN_LOGIN);
			this->unscheduleAllSelectors();
		 }
	 }
}
void UpdataView::dialogDidClick(int itemIndex, ModalDialogView *pSender)
{
	switch (pSender->getTag())
	{
	case DIALOG_TAG_NET_ERROR:
		{
			retryNum = 0;
			if(Game::CheckVersion())
				Game::CheckUpData();
			getScheduler()->scheduleSelector( cocos2d::SEL_SCHEDULE(&UpdataView::updateRES),this,1,kCCRepeatForever,0,XFALSE);

		}
		break;
	case DIALOG_TAG_UNCOMPRESS:
		{
			retryNumcompress = 0;
			Game::CheckUpData();
			getScheduler()->scheduleSelector( cocos2d::SEL_SCHEDULE(&UpdataView::updateRES),this,1,kCCRepeatForever,0,XFALSE);

		}
		break;
	default:
		break;
	}
	pSender->closeDialogView();
	m_dialog = 0;
}