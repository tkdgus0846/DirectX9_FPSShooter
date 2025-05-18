#include "WallPipes420956.h"
#include "Export_Function.h"


WallPipes420956::WallPipes420956(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallPipes420956::~WallPipes420956()
{
}

CGameObject * WallPipes420956::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallPipes420956* pInstance = new WallPipes420956(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallPipes420956::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallPipes #420956", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallPipes #420956", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}