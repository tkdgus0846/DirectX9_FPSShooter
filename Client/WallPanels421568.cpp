#include "WallPanels421568.h"
#include "Export_Function.h"


WallPanels421568::WallPanels421568(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallPanels421568::~WallPanels421568()
{
}

CGameObject * WallPanels421568::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallPanels421568* pInstance = new WallPanels421568(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallPanels421568::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallPanels #421568", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallPanels #421568", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}