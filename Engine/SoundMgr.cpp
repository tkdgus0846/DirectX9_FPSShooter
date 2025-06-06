#include "stdafx.h"
#include "SoundMgr.h"


IMPLEMENT_SINGLETON(CSoundMgr)

CSoundMgr::CSoundMgr(void)
{

}

CSoundMgr::~CSoundMgr(void)
{
	Release();
}

void CSoundMgr::Init()
{
	// 사운드를 담당하는 대표객체를 생성하는 함수
	FMOD_System_Create(&m_pSystem);
	
	// 1. 시스템 포인터, 2. 사용할 가상채널 수 , 초기화 방식) 
	FMOD_System_Init(m_pSystem, 32, FMOD_INIT_NORMAL, NULL);

	LoadSoundFile(); 
}
void CSoundMgr::Release()
{
	for (auto& Mypair : m_mapSound)
	{
		delete[] Mypair.first;
		FMOD_Sound_Release(Mypair.second);
	}
	m_mapSound.clear(); 
	
	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}




void CSoundMgr::PlayGameSound(const TCHAR * pSoundKey, CHANNELID eID, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter; 

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), 
		[&](auto& iter)->bool 
	{
		return !lstrcmp(pSoundKey, iter.first);
	});
	
	if (iter == m_mapSound.end())
		return;

	FMOD_BOOL bPlay = FALSE; 

	if (FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay))
	{
		FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[eID]);
	}

	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::PlayBGM(const TCHAR * pSoundKey, CHANNELID eID, float fVolume)
{
	map<TCHAR*, FMOD_SOUND*>::iterator iter;

	// iter = find_if(m_mapSound.begin(), m_mapSound.end(), CTag_Finder(pSoundKey));
	iter = find_if(m_mapSound.begin(), m_mapSound.end(), [&](auto& iter)->bool
	{
		return !lstrcmp(pSoundKey, iter.first);
	});
	
	if (iter == m_mapSound.end())
		return;

	m_PrevBGM = m_CurBGM;
	m_PrevBGMChannel = m_CurBGMChannel;

	m_CurBGM = pSoundKey;
	m_CurBGMChannel = eID;	

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter->second, FALSE, &m_pChannelArr[eID]);
	FMOD_Channel_SetMode(m_pChannelArr[eID], FMOD_LOOP_NORMAL);
	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);
	FMOD_System_Update(m_pSystem);
}

void Engine::CSoundMgr::SetVolumePrevBGM(float fVolume, bool bChange)
{
	if (bChange == true)
	{
		m_CurBGM = m_PrevBGM;
		m_CurBGMChannel = m_PrevBGMChannel;
	}
	
	FMOD_Channel_SetVolume(m_pChannelArr[m_PrevBGMChannel], fVolume);
}

void Engine::CSoundMgr::PlayPrevBGM(float fVolume)
{
	StopAllBGM();
	PlayBGM(m_PrevBGM, m_PrevBGMChannel, fVolume);
}

void Engine::CSoundMgr::SetVolumeCurBGM(float fVolume)
{
	FMOD_Channel_SetVolume(m_pChannelArr[m_CurBGMChannel], fVolume);
}


void CSoundMgr::StopSound(CHANNELID eID)
{
	FMOD_Channel_Stop(m_pChannelArr[eID]);
}

void CSoundMgr::StopAll()
{
	for (int i = 0 ; i < MAXCHANNEL ; ++i)
		FMOD_Channel_Stop(m_pChannelArr[i]);
}

void CSoundMgr::SetChannelVolume(CHANNELID eID, float fVolume)
{
	FMOD_Channel_SetVolume(m_pChannelArr[eID], fVolume);

	FMOD_System_Update(m_pSystem);
}

void CSoundMgr::StopAllBGM()
{
	for (_int i = SOUND_BGM; i < SOUND_BGM_END; i++)
		StopSound((CHANNELID)i);
}

void CSoundMgr::StopBGM(CHANNELID eID)
{
	StopSound((CHANNELID)eID);
}

void CSoundMgr::StopCurBGM()
{
	StopSound(m_CurBGMChannel);
}

bool CSoundMgr::IsPlaying(CHANNELID eID)
{
	FMOD_BOOL bPlay;
	FMOD_Channel_IsPlaying(m_pChannelArr[eID], &bPlay);
	
	return bPlay;
}

void CSoundMgr::LoadSoundFile()
{
	// _finddata_t : <io.h>에서 제공하며 파일 정보를 저장하는 구조체
	_finddata_t fd; 

	// _findfirst : <io.h>에서 제공하며 사용자가 설정한 경로 내에서 가장 첫 번째 파일을 찾는 함수
	long handle = _findfirst("../Resource/AudioClip/*.*", &fd);

	if (handle == -1)
		return; 

	int iResult = 0; 

	char szCurPath[128] = "../Resource/AudioClip/";
	char szFullPath[128] = ""; 

	while (iResult != -1)
	{
		strcpy_s(szFullPath, szCurPath); 

		// "../ Sound/Success.wav"
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr; 

		FMOD_RESULT eRes = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, 0, &pSound);

		if (eRes == FMOD_OK)
		{
			int iLength = strlen(fd.name) + 1; 

			TCHAR* pSoundKey = new TCHAR[iLength];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * iLength);

			// 아스키 코드 문자열을 유니코드 문자열로 변환시켜주는 함수
			MultiByteToWideChar(CP_ACP, 0, fd.name, iLength, pSoundKey, iLength);

			m_mapSound.emplace(pSoundKey, pSound);
		}
		//_findnext : <io.h>에서 제공하며 다음 위치의 파일을 찾는 함수, 더이상 없다면 -1을 리턴
		iResult = _findnext(handle, &fd);
	}

	FMOD_System_Update(m_pSystem);

	_findclose(handle);
}
