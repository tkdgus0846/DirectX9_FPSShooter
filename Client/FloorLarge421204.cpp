#include "FloorLarge421204.h"
#include "Export_Function.h"



FloorLarge421204::FloorLarge421204(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorLarge421204::~FloorLarge421204()
{
}

CGameObject * FloorLarge421204::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorLarge421204* pInstance = new FloorLarge421204(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorLarge421204::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLarge #421204", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLarge #421204", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}