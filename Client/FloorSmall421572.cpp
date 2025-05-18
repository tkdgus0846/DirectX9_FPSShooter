#include "FloorSmall421572.h"
#include "Export_Function.h"


FloorSmall421572::FloorSmall421572(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorSmall421572::~FloorSmall421572()
{
}

CGameObject * FloorSmall421572::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorSmall421572* pInstance = new FloorSmall421572(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorSmall421572::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorSmall #421572", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorSmall #421572", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void FloorSmall421572::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}
