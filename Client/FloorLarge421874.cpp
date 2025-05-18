#include "FloorLarge421874.h"
#include "Export_Function.h"



FloorLarge421874::FloorLarge421874(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorLarge421874::~FloorLarge421874()
{
}

CGameObject * FloorLarge421874::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorLarge421874* pInstance = new FloorLarge421874(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorLarge421874::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLarge #421874", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLarge #421874", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}