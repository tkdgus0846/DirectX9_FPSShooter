#include "SonicUI.h"
#include "Export_Function.h"

CSonicUI::CSonicUI(LPDIRECT3DDEVICE9 pGraphicDev) :
	CUI(pGraphicDev)
{
	Set_ObjTag(L"SonicUI");
	m_Score = 0;
	m_bRenderScore = false;
}

CSonicUI::~CSonicUI()
{
}

HRESULT CSonicUI::Add_Component()
{
	for (int i = 0; i < 3; i++)
	{
		m_ScoreBufferVec.push_back(dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this)));
	}

	m_GameOverBuffer = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_GameOverBuffer, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"m_GameOverBuffer", m_GameOverBuffer });

	m_ScoreTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Score_Texture", this));
	NULL_CHECK_RETURN(m_ScoreTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"ScoreTexture", m_ScoreTexture });

	m_GameOverTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Gameover_Texture", this));
	NULL_CHECK_RETURN(m_GameOverTexture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"ScoreTexture", m_GameOverTexture });
	


	return S_OK;
}

_int CSonicUI::Update_GameObject(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_ALPHA_UI, this);
	return __super::Update_GameObject(fTimeDelta);
}

void CSonicUI::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSonicUI::Render_GameObject(void)
{
	if (m_bRenderScore)
	{
		_int stdInt = 100;
		_int curNum;
		_int dividenNum = m_Score;

		_vec3 pos = { 200.f,200.f,0.f };

		for (auto iter : m_ScoreBufferVec)
		{
			curNum = dividenNum / stdInt; // 0 0
			dividenNum %= stdInt;
			stdInt /= 10; // 100 10 1

			Set_ViewMatrix_UI(pos.x, pos.y, 6.f, 8.f);
			m_ScoreTexture->Render_Texture(curNum);
			iter->Render_Component();

			pos.x += 15.f;
		}
	}
	
	__super::Render_GameObject();
}

void CSonicUI::Start_Game()
{
	m_bRenderScore = true;
}

void CSonicUI::End_Game()
{
	m_bRenderScore = false;
}

CSonicUI * CSonicUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSonicUI*		pInstance = new CSonicUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CSonicUI::Free(void)
{
	for_each(m_ScoreBufferVec.begin(), m_ScoreBufferVec.end(), CDeleteObj());
	__super::Free();
}
