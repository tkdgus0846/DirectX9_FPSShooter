#include "OilTile.h"
#include "Export_Function.h"


COilTile::COilTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

COilTile::~COilTile()
{
}

CGameObject * COilTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	COilTile* pInstance = new COilTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CGameObject * COilTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

HRESULT COilTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorBlood", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorBlood", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void COilTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}