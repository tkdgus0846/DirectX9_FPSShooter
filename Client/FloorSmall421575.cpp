#include "FloorSmall421575.h"
#include "Export_Function.h"



FloorSmall421575::FloorSmall421575(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorSmall421575::~FloorSmall421575()
{
}

CGameObject * FloorSmall421575::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorSmall421575* pInstance = new FloorSmall421575(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorSmall421575::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorSmall #421575", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorSmall #421575", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void FloorSmall421575::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}
