#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimation;

END

enum SELECTGAMEMODE
{
	GAMEMODE_STARTGAME,
	GAMEMODE_EDITOR,
	GAMEMODE_EXITGAME,
	GAMEMODE_NOCHOICE
};

class CBackGround : public Engine::CGameObject
{
private:
	explicit CBackGround(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBackGround();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	SELECTGAMEMODE			Get_GameMode() 
	{ 
		return m_eGameMode; 
	}
	
	_bool					Selected_GameMode()
	{
		if (m_eGameMode != m_ePrevGameMode) return true;
		return false;
	}

private:
	virtual HRESULT Add_Component() override;

public:
	static CBackGround*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	void Make_Logo_Text(string msg, const _vec3& startPoint, const _float& seq);
	virtual void Free(void) override;

private:
	SELECTGAMEMODE			m_eGameMode;
	SELECTGAMEMODE			m_ePrevGameMode;

	class CLoading*			m_pLoading;

	CRcTex*		m_LogoBuffer;
	CTexture*	m_LogoTexture;
	CRcTex*		m_BackgroundBuffer;
	CTexture*	m_BackgroundTexture;

	vector<CRcTex*>		m_StarBufferVec;
	vector<CAnimation*> m_StartAniVec;

	vector<_float>		m_StarSizeVec;
	vector<_vec3>		m_StarPosVec;

	CTexture*			m_LogoTextTexture;
	vector<CRcTex*>		m_LogoTextBufferVec;
	vector<_vec3>		m_LogoTextPosVec;
	vector<_uint>		m_LogoTextNumVec;

	CTexture*			m_SelectArrowTexture;
	CRcTex*				m_SelectArrowBuffer;
	_vec3				m_SelectArrowPos[3];

	_int				m_curSelectArrow;




};

