#include "WallSpecial420958.h"
#include "Export_Function.h"


WallSpecial420958::WallSpecial420958(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallSpecial420958::~WallSpecial420958()
{
}

CGameObject * WallSpecial420958::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallSpecial420958* pInstance = new WallSpecial420958(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallSpecial420958::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallSpecial #420958", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallSpecial #420958", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}