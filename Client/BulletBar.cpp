#include "BulletBar.h"
#include "Player.h"
#include "Export_Function.h"


CBulletBar::CBulletBar(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
	Set_ObjTag(L"BulletBar");
}

CBulletBar::~CBulletBar()
{
}

HRESULT CBulletBar::Ready_GameObject(void)
{
	m_vScale = { 151.f, 33.f, 1.f };
	__super::Ready_GameObject();

	return S_OK;
}

_int CBulletBar::Update_GameObject(const _float & fTimeDelta)
{

	Engine::Add_RenderGroup(RENDER_ALPHA_UI, this);

	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CBulletBar::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CBulletBar::Render_GameObject(void)
{
	if (Engine::Get_Player() == nullptr) { return; }
	if (dynamic_cast<CPlayer*>(Engine::Get_Player())->Get_bAimHack() == true) { return; }

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	Set_ViewMatrix_UI(-238.f, -230.f);

	__super::Render_GameObject();
}

HRESULT CBulletBar::Add_Component(void)
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"BulletBar_Texture", this));
	NULL_CHECK_RETURN(m_pTextureCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"BulletBar_Texture", pComponent });

	return S_OK;
}


CBulletBar * CBulletBar::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBulletBar* pInstance = new CBulletBar(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CBulletBar::Free(void)
{
	__super::Free();
}