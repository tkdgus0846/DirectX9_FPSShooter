#include "SnowTile.h"
#include "Export_Function.h"

CSnowTile::CSnowTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CSnowTile::~CSnowTile()
{
}

CGameObject * CSnowTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSnowTile* pInstance = new CSnowTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CGameObject * CSnowTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

HRESULT CSnowTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorSnow", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorSnow", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CSnowTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}