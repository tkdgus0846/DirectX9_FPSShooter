#include "ShortWall420954.h"
#include "Export_Function.h"


ShortWall420954::ShortWall420954(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

ShortWall420954::~ShortWall420954()
{
}

CGameObject * ShortWall420954::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	ShortWall420954* pInstance = new ShortWall420954(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT ShortWall420954::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"ShortWall #420954", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"ShortWall #420954", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}