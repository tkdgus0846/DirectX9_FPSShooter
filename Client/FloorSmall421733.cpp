#include "FloorSmall421733.h"
#include "Export_Function.h"


FloorSmall421733::FloorSmall421733(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorSmall421733::~FloorSmall421733()
{
}

CGameObject * FloorSmall421733::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorSmall421733* pInstance = new FloorSmall421733(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorSmall421733::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorSmall #421733", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorSmall #421733", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void FloorSmall421733::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}
