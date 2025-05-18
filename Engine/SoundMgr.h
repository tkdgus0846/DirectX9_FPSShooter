#pragma once

#include "Include.h"

BEGIN(Engine)

class CSoundMgr
{
	DECLARE_SINGLETON(CSoundMgr)

private:
	explicit CSoundMgr(void);
	virtual ~CSoundMgr(void);

public:
	void Init(); 
	void Release(); 

public:
	void PlayGameSound(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void PlayBGM(const TCHAR* pSoundKey, CHANNELID eID, float fVolume);
	void PlayPrevBGM(float fVolume);
	void SetVolumePrevBGM(float fVolume, bool bChange = false);
	void SetVolumeCurBGM(float fVolume);

	void StopSound(CHANNELID eID);
	void StopAll();
	void SetChannelVolume(CHANNELID eID, float fVolume);
	void StopAllBGM();
	void StopBGM(CHANNELID eID);
	void StopCurBGM();


	bool IsPlaying(CHANNELID eID);

private:
	void LoadSoundFile(); 

	const _tchar*		m_CurBGM;
	CHANNELID			m_CurBGMChannel;
	const _tchar*		m_PrevBGM;
	CHANNELID			m_PrevBGMChannel;

private:

	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL]; 

	

	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem; 
};

#define SOUND CSoundMgr::GetInstance()
#define PLAY_SOUND(soundkey, channelID, volume) SOUND->PlayGameSound(soundkey, channelID, volume)
#define PLAY_BGM(soundKey, channelID, volume) SOUND->PlayBGM(soundKey, channelID, volume)
#define STOP_SOUND(channelID) SOUND->StopSound(channelID)
#define STOP_ALL_SOUND SOUND->StopAll()
#define SET_CHANNEL_VOLUME(channelID, volume) SOUND->SetChannelVolume(channelID, volume)

#define STOP_ALL_BGM SOUND->StopAllBGM()

#define STOP_PLAY_SOUND(soundkey, channelID, volume)        \
STOP_SOUND(channelID);											\
PLAY_SOUND(soundkey, channelID, volume)							\

#define IS_PLAYING(channelID) SOUND->IsPlaying(channelID)


END