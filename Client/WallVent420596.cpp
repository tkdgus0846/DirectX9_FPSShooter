#include "WallVent420596.h"
#include "Export_Function.h"


WallVent420596::WallVent420596(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallVent420596::~WallVent420596()
{
}

CGameObject * WallVent420596::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallVent420596* pInstance = new WallVent420596(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallVent420596::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallVent #420596", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallVent #420596", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}