#include "FloorLarge421865.h"
#include "Export_Function.h"



FloorLarge421865::FloorLarge421865(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorLarge421865::~FloorLarge421865()
{
}

CGameObject * FloorLarge421865::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorLarge421865* pInstance = new FloorLarge421865(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorLarge421865::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLarge #421865", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLarge #421865", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}