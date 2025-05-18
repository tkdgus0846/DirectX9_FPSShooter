#include "WallVent420952.h"
#include "Export_Function.h"


WallVent420952::WallVent420952(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallVent420952::~WallVent420952()
{
}

CGameObject * WallVent420952::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallVent420952* pInstance = new WallVent420952(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallVent420952::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallVent #420952", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallVent #420952", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}