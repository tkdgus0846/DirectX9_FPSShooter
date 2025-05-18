#include "WallPanels421731.h"
#include "Export_Function.h"


WallPanels421731::WallPanels421731(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallPanels421731::~WallPanels421731()
{
}

CGameObject * WallPanels421731::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallPanels421731* pInstance = new WallPanels421731(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallPanels421731::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallPanels #421731", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallPanels #421731", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}