#include "LoadingBackground.h"

#include "Export_Function.h"


CLoadingBackground::CLoadingBackground(LPDIRECT3DDEVICE9 pGraphicDev):
	CUI(pGraphicDev),
	m_iSeperator(0),
	m_CurSeperatorIndex(0)
{
	Set_ObjTag(L"Background");
}


CLoadingBackground::~CLoadingBackground()
{
}

CLoadingBackground* CLoadingBackground::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLoadingBackground*		pInstance = new CLoadingBackground(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT CLoadingBackground::Add_Component()
{
	m_LogoTextTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Num_Texture", this));

	Make_Logo_Text("LOADING", { -100.f,-100.f,0.f }, 27.f);
	Make_Logo_Text("LOADING.", { -100.f,-100.f,0.f }, 27.f);
	Make_Logo_Text("LOADING..", { -100.f,-100.f,0.f }, 27.f);
	Make_Logo_Text("LOADING...", { -100.f,-100.f,0.f }, 27.f);
	Make_Logo_Text("LOADING COMPLETE!!!", { -210.f,-100.f,0.f }, 27.f);

	m_TextSeperator.push_back(m_LogoTextBufferVec.size());

	m_CurSeperatorIndex = 0;
	return S_OK;
}

void CLoadingBackground::Render_GameObject(void)
{
	// m_TextSeperator[m_CurSeperatorIndex] 부터
	// m_TextSeperator[m_CurSeperatorIndex + 1] 까지 해야함.
	
	_int startIndex = m_TextSeperator[m_CurSeperatorIndex];
	_int endIndex = m_TextSeperator[m_CurSeperatorIndex+1];

	for (int i = startIndex; i < endIndex; i++)
	{
		const _vec3& pos = m_LogoTextPosVec[i];
		Set_ViewMatrix_UI(pos.x, pos.y, 30.f, 30.f);

		m_LogoTextTexture->Render_Texture(m_LogoTextNumVec[i]);
		m_LogoTextBufferVec[i]->Render_Component();
	}
		
	
	__super::Render_GameObject();
}

_int CLoadingBackground::Update_GameObject(const _float& fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	Add_RenderGroup(RENDER_ALPHA_UI, this);
	return 0;
}

void CLoadingBackground::Make_Logo_Text(string msg, const _vec3& startPoint, const _float& seq)
{
	_vec3 myPoint = startPoint;

	m_TextSeperator.push_back(m_iSeperator);
	m_iSeperator += msg.length();
	
	// . => 46   ! => 33  A => 65
	for (int i = 0; i < msg.length(); i++)
	{
		_uint num = msg[i] - 'A';
		if (msg[i] < 'A')
		{
			if (msg[i] == '.')
				num = 38;
			else if (msg[i] == '!')
				num = 39;
			else
				num = 999;
		}


		if (num != 999)
		{
			CRcTex* textBuffer = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
			m_LogoTextBufferVec.push_back(textBuffer);
			m_LogoTextNumVec.push_back(num);
			m_LogoTextPosVec.push_back(myPoint);
		}

		myPoint.x += seq;
	}
}

void CLoadingBackground::Free(void)
{
	Safe_Release(m_LogoTextTexture);
	for_each(m_LogoTextBufferVec.begin(), m_LogoTextBufferVec.end(), CDeleteObj());
	__super::Free();
}
