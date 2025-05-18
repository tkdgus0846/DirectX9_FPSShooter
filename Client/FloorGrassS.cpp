#include "FloorGrassS.h"
#include "Export_Function.h"


FloorGrassS::FloorGrassS(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorGrassS::~FloorGrassS()
{
}

CGameObject * FloorGrassS::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorGrassS* pInstance = new FloorGrassS(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorGrassS::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorGrassS", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorGrassS", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void FloorGrassS::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}


