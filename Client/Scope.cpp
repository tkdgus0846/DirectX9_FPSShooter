#include "Scope.h"
#include "Export_Function.h"
#include "Player.h"

CScope::CScope(LPDIRECT3DDEVICE9 pGraphicDev)
	:CUI(pGraphicDev)
{
	Set_ObjTag(L"Scope");
}


CScope::~CScope()
{
}

HRESULT CScope::Add_Component()
{
	CRcTex* pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pRcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pRcTex });

	CTexture* m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Scope_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Scope_Texture", m_pTextureCom });
	
	return S_OK;
}

HRESULT CScope::Ready_GameObject(void)
{
	m_vScale.x = 450.f;
	m_vScale.y = 350.f;

	__super::Ready_GameObject();
	return S_OK;
}

_int CScope::Update_GameObject(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_AFTER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);
	return 0;
}

void CScope::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CScope::Render_GameObject(void)
{
	if (Engine::Get_Player() == nullptr) { return; }

	if (dynamic_cast<CPlayer*>(Engine::Get_Player())->Get_bAimHack() == false) { return; }

	Set_ViewMatrix_UI(0.f, 0.f);	
	__super::Render_GameObject();
}

CScope * CScope::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CScope* pInstance = new CScope(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CScope::Free(void)
{
	__super::Free();
}
