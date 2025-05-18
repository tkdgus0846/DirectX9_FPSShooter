#include "WallPipes420745.h"
#include "Export_Function.h"


WallPipes420745::WallPipes420745(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

WallPipes420745::~WallPipes420745()
{
}

CGameObject * WallPipes420745::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	WallPipes420745* pInstance = new WallPipes420745(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT WallPipes420745::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"WallPipes #420745", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"WallPipes #420745", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}