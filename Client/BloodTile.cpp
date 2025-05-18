#include "BloodTile.h"
#include "Export_Function.h"

CBloodTile::CBloodTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(L"BloodTile");
}

CBloodTile::~CBloodTile()
{
}

CGameObject * CBloodTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBloodTile* pInstance = new CBloodTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT CBloodTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorBlood", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorBlood", texture });

	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CBloodTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}