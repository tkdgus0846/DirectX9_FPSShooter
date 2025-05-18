#include "stdafx.h"
#include "BackGround.h"

#include "Export_Function.h"
#include "..\Engine\SoundMgr.h"

#define STAR_NUM 30

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
	Set_LayerID(LAYER_BACKGROUND);
	Set_ObjTag(L"Background");

	m_curSelectArrow = 0;

	m_eGameMode = GAMEMODE_NOCHOICE;
	m_ePrevGameMode = GAMEMODE_NOCHOICE;
}

CBackGround::~CBackGround()
{
}

HRESULT CBackGround::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_eGameMode = GAMEMODE_NOCHOICE;

	return result;
}

_int CBackGround::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	for (int i = 0; i < STAR_NUM; i++)
	{
		m_StartAniVec[i]->Update_Component(fTimeDelta);
	}

	Engine::Add_RenderGroup(RENDER_ALPHA_UI, this);

	if (Selected_GameMode() == false)
	{
		if (Engine::Key_Down(DIK_DOWNARROW))
		{
			STOP_PLAY_SOUND(L"sfxSelect.wav", SOUND_EFFECT, 1.f);
			m_curSelectArrow += 1;
			if (m_curSelectArrow > 2) m_curSelectArrow = 0;
		}

		if (Engine::Key_Down(DIK_UPARROW))
		{
			STOP_PLAY_SOUND(L"sfxSelect.wav", SOUND_EFFECT, 1.f);
			m_curSelectArrow -= 1;
			if (m_curSelectArrow < 0) m_curSelectArrow = 2;
		}

		if (Engine::Key_Down(DIK_RETURN))
		{
			if (m_eGameMode == m_ePrevGameMode)
			{
				m_eGameMode = (SELECTGAMEMODE)m_curSelectArrow;
				STOP_PLAY_SOUND(L"sfxStart.wav", SOUND_EFFECT, 1.f);
			}
				
		}
	}
	

	return 0;
}

void CBackGround::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBackGround::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	_matrix scaleMatrix, transMatrix, viewMat;

	scaleMatrix.Scaling((_float)WINCX, (_float)WINCY, 0.f);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &scaleMatrix);

	m_BackgroundTexture->Render_Texture();
	m_BackgroundBuffer->Render_Component();

	for (int i = 0; i < STAR_NUM; i++)
	{
		scaleMatrix.Scaling(m_StarSizeVec[i], m_StarSizeVec[i], 0.f);
		transMatrix.Translation(m_StarPosVec[i].x, m_StarPosVec[i].y, 0.f);

		viewMat = scaleMatrix * transMatrix;

		m_pGraphicDev->SetTransform(D3DTS_VIEW, &viewMat);
		m_StartAniVec[i]->Render_Component();
		m_StarBufferVec[i]->Render_Component();
	}
	
	
	scaleMatrix.Scaling(200.f, 112.f, 0.f);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &scaleMatrix);
	__super::Render_GameObject();

	for (int i = 0; i < m_LogoTextBufferVec.size(); i++)
	{
		scaleMatrix.Scaling(20.f, 20.f, 0.f);
		transMatrix.Translation(m_LogoTextPosVec[i].x, m_LogoTextPosVec[i].y, 0.f);

		viewMat = scaleMatrix * transMatrix;

		m_pGraphicDev->SetTransform(D3DTS_VIEW, &viewMat);

		if (m_LogoTextNumVec[i] == 999)
			m_BackgroundTexture->Render_Texture();
		else
			m_LogoTextTexture->Render_Texture(m_LogoTextNumVec[i]);
		m_LogoTextBufferVec[i]->Render_Component();
	}

	scaleMatrix.Scaling(10.f, 10.f, 0.f);
	transMatrix.Translation(m_SelectArrowPos[m_curSelectArrow].x, m_SelectArrowPos[m_curSelectArrow].y, 0.f);
	viewMat = scaleMatrix * transMatrix;
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &viewMat);

	m_SelectArrowTexture->Render_Texture();
	m_SelectArrowBuffer->Render_Component();
}

HRESULT CBackGround::Add_Component(void)
{
	m_LogoBuffer = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex",this));
	NULL_CHECK_RETURN(m_LogoBuffer, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Logo_RcTex", m_LogoBuffer });

	m_LogoTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Logo_Texture",this));
	NULL_CHECK_RETURN(m_LogoTexture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Logo_Texture", m_LogoTexture });

	m_BackgroundBuffer = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_BackgroundBuffer, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Background_RcTex", m_BackgroundBuffer });
	//m_BackgroundBuffer->Set_RenderFlag();

	m_BackgroundTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Background_Texture", this));
	NULL_CHECK_RETURN(m_BackgroundTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Background_Texture", m_BackgroundTexture });

	CTexture* starTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"StarBullet_Texture", this));
	m_uMapComponent[ID_STATIC].insert({ L"StarBullet_Texture", m_BackgroundTexture });
	
	for (int i = 0; i < STAR_NUM; i++)
	{
		CRcTex* starBuffer = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		m_StarBufferVec.push_back(starBuffer);
		//starBuffer->Set_RenderFlag();
		NULL_CHECK_RETURN(m_LogoBuffer, E_FAIL);

		CAnimation* ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
		
		m_StartAniVec.push_back(ani);

		ani->BindAnimation(ANIM_IDLE, starTexture, GetRandomFloat(0.1f,0.3f));
		ani->SelectState(ANIM_IDLE);

		_float fSize = GetRandomFloat(2.8f, 6.7f);
		m_StarSizeVec.push_back(fSize);

		_vec3 RandomPos;
		_vec3 minPos = { -375.f, -275.f, 0.f };
		_vec3 maxPos = { 375.f, 275.f, 0.f };

		GetRandomVector(&RandomPos, &minPos, &maxPos);
		m_StarPosVec.push_back(RandomPos);
	}

	m_LogoTextTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Num_Texture", this));
	m_uMapComponent[ID_STATIC].insert({ L"Num_Texture", m_LogoTextTexture });

	m_SelectArrowTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"SelectArrow_Texture", this));
	m_uMapComponent[ID_STATIC].insert({ L"SelectArrow_Texture", m_SelectArrowTexture });

	m_SelectArrowBuffer = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_SelectArrowBuffer, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"Arrow_RcTex", m_SelectArrowBuffer });


	Make_Logo_Text("START GAME", { -120.f,-160.f,0.f }, 27.f);
	Make_Logo_Text("EDITOR", { -68.f,-200.f,0.f }, 27.f);
	Make_Logo_Text("EXIT", { -38.f,-240.f,0.f }, 27.f);
	
	m_SelectArrowPos[0] = { -150.f,-160.f,0.f };
	m_SelectArrowPos[1] = { -98.f,-200.f,0.f };
	m_SelectArrowPos[2] = { -68.f,-240.f,0.f };
	return S_OK;
}

CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBackGround*		pInstance = new CBackGround(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBackGround::Make_Logo_Text(string msg, const _vec3& startPoint, const _float& seq)
{
	_vec3 myPoint = startPoint;

	for (int i = 0; i < msg.length(); i++)
	{
		_uint num = msg[i] - 'A';
		if (msg[i] < 'A') num = 999;

		CRcTex* textBuffer = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		m_LogoTextBufferVec.push_back(textBuffer);
		m_LogoTextNumVec.push_back(num);
		m_LogoTextPosVec.push_back(myPoint);

		myPoint.x += seq;	
	}
}

void CBackGround::Free(void)
{
	Safe_Release(m_LogoBuffer);
	Safe_Release(m_LogoTexture);
	Safe_Release(m_BackgroundBuffer);
	Safe_Release(m_BackgroundTexture);
	Safe_Release(m_LogoTextTexture);
	Safe_Release(m_SelectArrowTexture);
	Safe_Release(m_SelectArrowBuffer);

	for_each(m_StarBufferVec.begin(), m_StarBufferVec.end(), CDeleteObj());
	for_each(m_StartAniVec.begin(), m_StartAniVec.end(), CDeleteObj());
	for_each(m_LogoTextBufferVec.begin(), m_LogoTextBufferVec.end(), CDeleteObj());
	__super::Free();
}
