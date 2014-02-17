#include "./sound/SoundSystem.h"

#include "SimpleAudioEngine.h"

#include "./datapool/SettingData.h"

using namespace CocosDenshion;

IMPLEMENT_SINGLETON(SoundSystem);

SoundSystem::SoundSystem()
{
}
SoundSystem::~SoundSystem()
{
}
X_VOID SoundSystem::Initial()
{
	  //setBackgroundMusicVolume(0.2);
}
X_VOID SoundSystem::Release()
{
	SimpleAudioEngine::end();
}
X_VOID SoundSystem::pauseBackgroundMusic(bool bpause)
{
	 if (bpause)
	 {
		 SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	 }
	 else
	 {
		 if (SettingData::Get(SettingData::SOUND))
			 SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	 }
	   
}

X_VOID SoundSystem::pauseAllEffects(bool bpause)
{
	if (bpause)
	{
		 SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	}
	else
	{
		if (SettingData::Get(SettingData::AUDIO))
		 SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	}
	  
}
 
X_VOID	SoundSystem::playBackgroundMusic(const X_CHAR* music,bool bLoop)
{
	if (music == string("-1"))
	{
		return;
	}
	if (SettingData::Get(SettingData::SOUND))
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(music,bLoop);
	}

}
X_VOID	SoundSystem::playEffect(const X_CHAR* music,bool bLoop)
{
	if (music == string("-1"))
	{
		return;
	}
	if (SettingData::Get(SettingData::AUDIO))
	{
		SimpleAudioEngine::sharedEngine()->playEffect(music,bLoop);
	}
	
}
X_VOID	SoundSystem::setBackgroundMusicVolume(float volume)
{
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(volume);
}

X_VOID SoundSystem::playClickEffect(GAME_CLICK_EFFECT gcEffect,bool bLoop)
{
	string strFileName;
	switch (gcEffect)
	{
	case GAME_CLICK_COMMON:
		strFileName = "ge_btn_common" +SOUND_EXT;
		break;
	case GAME_CLICK_SOUND1:
		strFileName = "ge_line"+SOUND_EXT;
		break;
	case GAME_CLICK_SOUND2:
		strFileName = "ge_equip_com"+SOUND_EXT;
		break;
	case GAME_CLICK_SOUND3:
		strFileName = "ge_altar"+SOUND_EXT;
		break;
	case GAME_CLICK_SOUND4:
		strFileName = "ge_btn_buyBear"+SOUND_EXT;
		break;
	case GAME_CLICK_SOUND5:
		strFileName = "ge_btn_heroEvolve"+SOUND_EXT;
		break;
	case GAME_CLICK_SOUND6:
		strFileName = "ge_btn_heroUp"+SOUND_EXT;
		break;
	case GAME_CLICK_SOUND7:
		strFileName = "ge_btn_skillUp"+SOUND_EXT;
		break;
	case GAME_CLICK_SOUND8:
		strFileName = "ge_btn_cheese"+SOUND_EXT;
		break;
	case GAME_CLICK_SOUND9:
		strFileName = "ge_btn_sel"+SOUND_EXT;
		break;
	case GAME_CLICK_SOUND10:
		strFileName = "";
		break;
	case GAME_CLICK_SOUND11:
		strFileName = "";
		break;
	default:
		break;
	}
	if (strFileName.empty())
	{
		return;
	}

	playEffect(strFileName.c_str(),bLoop);

}