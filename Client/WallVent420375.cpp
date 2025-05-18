#include "WallVent420375.h"
#include "Export_Function.h"


WallVent420375::WallVent420375(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallVent420375::~WallVent420375()
{
}

CGameObject * WallVent420375::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallVent420375* pInstance = new WallVent420375(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallVent420375::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallVent #420375", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallVent #420375", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}