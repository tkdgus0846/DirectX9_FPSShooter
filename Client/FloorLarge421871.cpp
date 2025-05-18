#include "FloorLarge421871.h"
#include "Export_Function.h"



FloorLarge421871::FloorLarge421871(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorLarge421871::~FloorLarge421871()
{
}

CGameObject * FloorLarge421871::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorLarge421871* pInstance = new FloorLarge421871(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorLarge421871::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLarge #421871", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLarge #421871", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}