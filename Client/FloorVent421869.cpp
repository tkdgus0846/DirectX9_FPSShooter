#include "FloorVent421869.h"
#include "Export_Function.h"

FloorVent421869::FloorVent421869(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorVent421869::~FloorVent421869()
{
}

CGameObject * FloorVent421869::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorVent421869* pInstance = new FloorVent421869(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorVent421869::Add_Component()
{
	HRESULT result = __super::Add_Component();
	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorVent #421869", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorVent #421869", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });

	return S_OK;
}