#include "ShortWall421217.h"
#include "Export_Function.h"


ShortWall421217::ShortWall421217(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

ShortWall421217::~ShortWall421217()
{
}

CGameObject * ShortWall421217::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	ShortWall421217* pInstance = new ShortWall421217(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT ShortWall421217::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"ShortWall #421217", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"ShortWall #421217", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}
