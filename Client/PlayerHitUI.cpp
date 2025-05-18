#include "PlayerHitUI.h"
#include "Player.h"
#include "Export_Function.h"


CPlayerHitUI::CPlayerHitUI(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
	Set_ObjTag(L"PlayerHitUI");
}

CPlayerHitUI::~CPlayerHitUI()
{
}

HRESULT CPlayerHitUI::Add_Component()
{
	CRcTex*	m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", m_pRcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BloodScreen", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"BloodScreen", Texture });

	return S_OK;
}

HRESULT CPlayerHitUI::Ready_GameObject(void)
{
	m_vScale = { 400.f, 300.f, 0.f };
	__super::Ready_GameObject();

	return S_OK;
}

_int CPlayerHitUI::Update_GameObject(const _float & fTimeDelta)
{
	if (Engine::Get_Player() == nullptr) { return 0; }
	if (dynamic_cast<CPlayer*>(Engine::Get_Player())->Get_bDamaged() == false) { return 0; }

	m_fTime += fTimeDelta;
	if (m_fTime > 0.3f)
	{
		dynamic_cast<CPlayer*>(Engine::Get_Player())->Set_bDamaged(false); 
		m_fTime = 0.f;
	}

	Add_RenderGroup(RENDER_FINAL_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CPlayerHitUI::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CPlayerHitUI::Render_GameObject(void)
{
	Set_ViewMatrix_UI(0.f, 0.f);

	__super::Render_GameObject();
}


CPlayerHitUI * CPlayerHitUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerHitUI* pInstance = new CPlayerHitUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayerHitUI::Free(void)
{
	__super::Free();
}