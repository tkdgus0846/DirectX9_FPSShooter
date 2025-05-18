#include "FloorLarge421559.h"
#include "Export_Function.h"



FloorLarge421559::FloorLarge421559(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorLarge421559::~FloorLarge421559()
{
}

CGameObject * FloorLarge421559::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorLarge421559* pInstance = new FloorLarge421559(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorLarge421559::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLarge #421559", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLarge #421559", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}