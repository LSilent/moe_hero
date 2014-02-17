
#ifndef __SoundSystem_h__
#define __SoundSystem_h__
 
#include "./base/Global.h"
#include "./base/Singleton.h"

enum GAME_CLICK_EFFECT
{
	GAME_CLICK_COMMON,
	GAME_CLICK_SOUND1, //链条
	GAME_CLICK_SOUND2, //合成物品
	GAME_CLICK_SOUND3, //献祭
	GAME_CLICK_SOUND4, //购买体力
	GAME_CLICK_SOUND5, //进化
	GAME_CLICK_SOUND6, //英雄升级
	GAME_CLICK_SOUND7, //技能升级
	GAME_CLICK_SOUND8, //吃奶酪
	GAME_CLICK_SOUND9, //选择
	GAME_CLICK_SOUND10,
	GAME_CLICK_SOUND11,
}; 

 class SoundSystem :  public Singleton<SoundSystem>
{
public:
	SoundSystem();
	virtual ~SoundSystem();

public:
	
	X_VOID  Initial();
	X_VOID  Release();

	//暂停、继续播放
 
	X_VOID	pauseBackgroundMusic(bool bpause);
	X_VOID	pauseAllEffects(bool bpause);





	X_VOID	setBackgroundMusicVolume(float volume);
	
	X_VOID	playBackgroundMusic(const X_CHAR* music,bool bLoop = true);
	X_VOID	playEffect(const X_CHAR* music,bool bLoop = false);


	X_VOID playClickEffect(GAME_CLICK_EFFECT gcEffect,bool bLoop = false);
	
private: 
 
	DECLARE_SINGLETON(SoundSystem);
};

#endif