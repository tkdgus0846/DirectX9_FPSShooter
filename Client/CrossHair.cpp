#include "CrossHair.h"
#include "Export_Function.h"

CCrossHair::CCrossHair(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
	Set_ObjTag(L"CrossHair");
}

CCrossHair::~CCrossHair()
{
}

HRESULT CCrossHair::Ready_GameObject(void)
{
	m_vPos = { 0.f, 0.f, 0.f };
	m_vScale = { 25.f, 25.f, 0.f };

	__super::Ready_GameObject();

	return S_OK;
}

_int CCrossHair::Update_GameObject(const _float & fTimeDelta)
{
	Add_RenderGroup(RENDER_ALPHA_UI, this);
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CCrossHair::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCrossHair::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	Set_ViewMatrix_UI();

	__super::Render_GameObject();
}

HRESULT CCrossHair::Add_Component(void)
{
	CRcTex* RcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(RcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", RcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"CrossHair_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"CrossHair_Texture", Texture });

	CAnimation* Ani = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(Ani, E_FAIL);

	Ani->BindAnimation(ANIM_IDLE, Texture, 0.1f);
	Ani->SelectState(ANIM_IDLE);
	m_uMapComponent[ID_ALL].insert({ L"Animation", Ani });

	return S_OK;
}

CCrossHair * CCrossHair::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCrossHair* pInstance = new CCrossHair(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CCrossHair::Free(void)
{
	__super::Free();
}







