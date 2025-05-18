#include "FloorHole421724.h"
#include "Export_Function.h"


FloorHole421724::FloorHole421724(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorHole421724::~FloorHole421724()
{
}

CGameObject * FloorHole421724::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorHole421724* pInstance = new FloorHole421724(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorHole421724::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorHole #421724", this));
	NULL_CHECK_RETURN(texture, E_FAIL);

	m_uMapComponent[ID_STATIC].insert({ L"FloorHole #421724", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void FloorHole421724::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}

