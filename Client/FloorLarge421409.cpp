#include "FloorLarge421409.h"
#include "Export_Function.h"



FloorLarge421409::FloorLarge421409(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorLarge421409::~FloorLarge421409()
{
}

CGameObject * FloorLarge421409::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorLarge421409* pInstance = new FloorLarge421409(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorLarge421409::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLarge #421409", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLarge #421409", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}