#include "WallVent420738.h"
#include "Export_Function.h"


WallVent420738::WallVent420738(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallVent420738::~WallVent420738()
{
}

CGameObject * WallVent420738::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallVent420738* pInstance = new WallVent420738(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallVent420738::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallVent #420738", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallVent #420738", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}