#include "SandTile.h"
#include "Export_Function.h"

CSandTile::CSandTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CSandTile::~CSandTile()
{
}

CGameObject * CSandTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSandTile* pInstance = new CSandTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT CSandTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorSand", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorSand", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void CSandTile::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}