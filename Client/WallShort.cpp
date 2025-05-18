#include "WallShort.h"
#include "Export_Function.h"


WallShort::WallShort(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallShort::~WallShort()
{
}

CGameObject * WallShort::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallShort* pInstance = new WallShort(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallShort::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallShort", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallShort", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}