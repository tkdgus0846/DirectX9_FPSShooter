#include "FloorVent.h"
#include "Export_Function.h"
#include "..\Engine\ParticleMgr.h"



FloorVent::FloorVent(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorVent::~FloorVent()
{
}

CGameObject * FloorVent::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorVent* pInstance = new FloorVent(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorVent::Add_Component()
{
	HRESULT result = __super::Add_Component();
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorVent", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorVent", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}

_int FloorVent::Update_GameObject(const _float& fTimeDelta)
{
	m_fTime += fTimeDelta;
	if (m_fTime >= 6.f)
	{
		CParticle* particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"Vent_Particle", 100, m_pTransform->m_vInfo[INFO_POS]);
		Add_GameObject(particle);
		m_fTime = 0.f;
	}
	return __super::Update_GameObject(fTimeDelta);
}
