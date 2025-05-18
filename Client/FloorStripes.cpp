#include "FloorStripes.h"
#include "Export_Function.h"

FloorStripes::FloorStripes(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

FloorStripes::~FloorStripes()
{
}

CGameObject * FloorStripes::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	FloorStripes* pInstance = new FloorStripes(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT FloorStripes::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorStripes", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorStripes", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return S_OK;
}
