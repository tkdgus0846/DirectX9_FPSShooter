#include "ShWallPipes420367ortWall.h"
#include "Export_Function.h"


ShWallPipes420367ortWall::ShWallPipes420367ortWall(LPDIRECT3DDEVICE9 pGraphicDev)
	: CWallTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

ShWallPipes420367ortWall::~ShWallPipes420367ortWall()
{
}

CGameObject * ShWallPipes420367ortWall::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	ShWallPipes420367ortWall* pInstance = new ShWallPipes420367ortWall(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT ShWallPipes420367ortWall::Add_Component()
{
	HRESULT result = __super::Add_Component();

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"ShWallPipes #420367ortWall", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"ShWallPipes #420367ortWall", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	return result;
}