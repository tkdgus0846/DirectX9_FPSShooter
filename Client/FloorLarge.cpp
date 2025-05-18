#include "FloorLarge.h"
#include "Export_Function.h"



FloorLarge::FloorLarge(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorLarge::~FloorLarge()
{
}

CGameObject * FloorLarge::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorLarge* pInstance = new FloorLarge(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorLarge::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLarge", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLarge", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}