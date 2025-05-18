#include "WallSpecial420366.h"
#include "Export_Function.h"


WallSpecial420366::WallSpecial420366(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallSpecial420366::~WallSpecial420366()
{
}

CGameObject * WallSpecial420366::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallSpecial420366* pInstance = new WallSpecial420366(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallSpecial420366::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallSpecial #420366", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallSpecial #420366", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}