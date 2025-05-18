#include "CutSceneUI.h"
#include "Export_Function.h"

CCutSceneUI::CCutSceneUI(LPDIRECT3DDEVICE9 pGraphicDev)\
	:CUI(pGraphicDev)
{
	Set_ObjTag(L"CutSceneUI");
}

CCutSceneUI::~CCutSceneUI()
{
}

HRESULT CCutSceneUI::Add_Component()
{
	m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", m_pRcTex });

	m_pTexture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"MiniMapBack_Texture", this));
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"MiniMapBack_Texture", m_pTexture });

	return S_OK;
}

HRESULT CCutSceneUI::Ready_GameObject(void)
{
	m_vScale = { 500.f, 100.f, 0.f };
	__super::Ready_GameObject();

	return S_OK;
}

_int CCutSceneUI::Update_GameObject(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_Scene_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CCutSceneUI::LateUpdate_GameObject(void)
{
	m_fUp += 1.f;
	m_fDown -= 1.f;

	__super::LateUpdate_GameObject();
}

void CCutSceneUI::Render_GameObject(void)
{
	Set_ViewMatrix_UI(0.f, m_fUp);
	m_pTexture->Set_Texture_Num(17);
	m_pRcTex->Render_Component();
	__super::Render_GameObject();


	Set_ViewMatrix_UI(0.f, m_fDown);
	m_pTexture->Set_Texture_Num(17);
	m_pRcTex->Render_Component();
	__super::Render_GameObject();
}


CCutSceneUI * CCutSceneUI::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCutSceneUI* pInstance = new CCutSceneUI(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

void CCutSceneUI::Free(void)
{
	__super::Free();
}
