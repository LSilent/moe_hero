 
#ifndef __MAINGAME_H__
#define __MAINGAME_H__
#include "./base/Global.h"
#include "./base/Singleton.h"

#include "./ui/element/ModalDialogView.h"
 
class NetErrorModalDialogDelegate :public ModalDialogDelegate
{
public:
	  void dialogDidClick(int itemIndex, ModalDialogView *pSender);
 
};
class NewVersionModalDialogDelegate :public ModalDialogDelegate
{
public:
    void dialogDidClick(int itemIndex, ModalDialogView *pSender);
    
};

class MainGame : public Singleton<MainGame>
{

	DECLARE_SINGLETON(MainGame);
public:
	  MainGame();
	  virtual ~MainGame();
	  X_VOID Initial();
	  X_VOID Release();
	  X_VOID Tick(X_UINT nTime);
public:
	 
	  enum GAME_RUN_STATE
	  {
		  NONE_STATE = 0,		
		  CONNECT_TO_SERVER,  //建立连接
		  RUNING_IN_LOGIN,	  //登陆
		  RUING_IN_SELECTPLAYER,//选人
		  RUNING_IN_GAME,
		  RUNING_IN_BATTLE,
	  };
	  X_VOID			SetGameMainProState(GAME_RUN_STATE nRunState);
public:
	 
	X_VOID			ConnectServer(const X_CHAR* szServerIP, X_INT nServerPort);
	X_VOID			ConnectServerDone(X_BOOL nRet);

	X_VOID			AskRolelist();
	X_VOID			EndBattle(bool win);

	NetErrorModalDialogDelegate* getDelegate();
    NewVersionModalDialogDelegate* getNewVersionDelegate();
	 
private:
	GAME_RUN_STATE		m_nGameRunState;	 
	NetErrorModalDialogDelegate *m_pdelegate;
    NewVersionModalDialogDelegate *m_newVersionDelegate;

};
#endif