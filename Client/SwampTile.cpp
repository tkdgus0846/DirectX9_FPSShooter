#include "SwampTile.h"
#include "Export_Function.h"

CSwampTile::CSwampTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CSwampTile::~CSwampTile()
{
}

CGameObject * CSwampTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSwampTile* pInstance = new CSwampTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CGameObject * CSwampTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

HRESULT CSwampTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorSwamp", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorSwamp", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CSwampTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}