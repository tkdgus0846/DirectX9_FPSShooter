#include "WallPanels420595.h"
#include "Export_Function.h"


WallPanels420595::WallPanels420595(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallPanels420595::~WallPanels420595()
{
}

CGameObject * WallPanels420595::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallPanels420595* pInstance = new WallPanels420595(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallPanels420595::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallPanels #420595", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallPanels #420595", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}