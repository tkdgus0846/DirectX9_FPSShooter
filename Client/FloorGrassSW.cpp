#include "FloorGrassSW.h"
#include "Export_Function.h"


FloorGrassSW::FloorGrassSW(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorGrassSW::~FloorGrassSW()
{
}

CGameObject * FloorGrassSW::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorGrassSW* pInstance = new FloorGrassSW(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorGrassSW::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorGrassSW", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorGrassSW", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}

void FloorGrassSW::OnCollisionStay(const Collision * collision)
{
	if (IsBodyCollider(collision))
	{
		//TODO
	}
}