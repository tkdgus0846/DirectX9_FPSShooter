#include "WallVent.h"
#include "Export_Function.h"


WallVent::WallVent(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallVent::~WallVent()
{
}

CGameObject * WallVent::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallVent* pInstance = new WallVent(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallVent::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallVent", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallVent", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}