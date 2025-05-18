#include "Disc.h"
#include "Export_Function.h"
#include "Player.h"
CDisc::CDisc(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
	Set_ObjTag(L"Disc");

}

CDisc::~CDisc()
{
}

HRESULT CDisc::Add_Component()
{
	// 디스크
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Disc_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Disc_Texture", Texture });

	CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.2f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	// 숫자
	for (size_t i = 0; i < m_MaxNumber; i++)
	{
		CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
		NULL_CHECK_RETURN(RcTex, E_FAIL);
		m_vecRc.push_back(RcTex);
	}

	m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Num_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);

	return S_OK;
}

HRESULT CDisc::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CDisc::Update_GameObject(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_ALPHA_UI, this);
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CDisc::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CDisc::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	Redner_Disc();

	Set_ViewMatrix_UI();

	__super::Render_GameObject();
}

void CDisc::Set_ViewMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	matTrans.Translation(300.f, 220.f, 0.f);
	D3DXMatrixScaling(&matView, 12.f, 12.f, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CDisc::Set_ViewMatrix_UI(_float fX, _float fY)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, 22.f, 20.f, 0.f);
	matTrans.Translation(fX, fY, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

_int CDisc::Compute_Num(_int & pPlayerDisc)
{
	return _int();
}

void CDisc::Redner_Disc()
{
	CPlayer* pPlayer = dynamic_cast<CPlayer*>(Engine::Get_Player());
	if (pPlayer == nullptr) return;

	_int curDisc = pPlayer->Get_Disc();

	for (size_t i = 0; i < m_MaxNumber; i++)
	{
		switch (i)
		{
		case 0:
			Set_ViewMatrix_UI(330 + (25.f * i), 220.f);
			m_pTextureCom->Render_Texture(curDisc + m_iStartNum);
			m_vecRc[i]->Render_Component();
			break;
		case 1:
			Set_ViewMatrix_UI(330 + (25.f * i), 220.f);
			m_pTextureCom->Render_Texture(41);
			m_vecRc[i]->Render_Component();
			break;
		case 2:
			Set_ViewMatrix_UI(330 + (25.f * i), 220.f);
			m_pTextureCom->Render_Texture(30);
			m_vecRc[i]->Render_Component();
			break;
		}
	}
}

CDisc * CDisc::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDisc* pInstance = new CDisc(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CDisc::Free(void)
{
	Safe_Release(m_pTextureCom);
	for_each(m_vecRc.begin(), m_vecRc.end(), CDeleteObj());
	__super::Free();
}
