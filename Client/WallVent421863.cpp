#include "WallVent421863.h"
#include "Export_Function.h"


WallVent421863::WallVent421863(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallVent421863::~WallVent421863()
{
}

CGameObject * WallVent421863::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallVent421863* pInstance = new WallVent421863(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallVent421863::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallVent #421863", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallVent #421863", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}