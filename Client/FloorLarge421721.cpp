#include "FloorLarge421721.h"
#include "Export_Function.h"



FloorLarge421721::FloorLarge421721(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorLarge421721::~FloorLarge421721()
{
}

CGameObject * FloorLarge421721::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorLarge421721* pInstance = new FloorLarge421721(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorLarge421721::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLarge #421721", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLarge #421721", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}