#ifndef __UISYSTEM_H__
#define __UISYSTEM_H__
#include "./base/Global.h"
#include "./base/Singleton.h"

#include "./ui/ui.h"
#include <list>


class UISystem :public Singleton<UISystem>
{

	DECLARE_SINGLETON(UISystem)

public:
	UISystem();
	virtual ~UISystem();
public:
	X_VOID			Initial();
	X_VOID			Tick(X_UINT nTime);
	X_VOID			Release();

public:

	X_VOID          onUIShowHide( UI *  pLayout,X_BOOL show);
 
	X_BOOL			IsLayoutShow(const string& strLayout,const string&  strWnd = "");
 
	UI*		    	getWndControl(const string& strLayout);

	static	X_VOID   OnGameEvent(const tGameEventData* pEvent, X_UINT dwOwnerData);

	// 检查互斥 返回UBI_TRUE 窗口可显示
	X_BOOL	CheckMutex( const UI *  pLayout);
   
	X_VOID  CleanShowList(const UI* pLayout);
	
	X_BOOL	isMain();

	UI*     getCurrentHanlerUi();
	bool    isCanUpdate(const UI*  pui);
	void    onFrontUI(UI *  pLayout);
	 
	X_VOID  setLock(bool b )
	{
		b_lock = b;
	}
protected:
	typedef std::list< UI *> LAYOUTWNDLIST;
	typedef LAYOUTWNDLIST::iterator WND_ITER;

	LAYOUTWNDLIST m_AllLayoutWnd;
	LAYOUTWNDLIST m_ShowLayoutWnd;
	bool     b_lock;
	UI *     m_preUi;
};

#endif