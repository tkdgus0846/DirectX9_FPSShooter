#include "NullFloorTile.h"
#include "Export_Function.h"


CNullFloorTile::CNullFloorTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CFloorTile(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CNullFloorTile::~CNullFloorTile()
{
}

HRESULT CNullFloorTile::Ready_GameObject()
{
	return S_OK;
}

_int CNullFloorTile::Update_GameObject(const _float & fTimeDelta)
{
	return _int();
}

void CNullFloorTile::LateUpdate_GameObject(void)
{
}

void CNullFloorTile::Render_GameObject(void)
{
}

CGameObject * CNullFloorTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNullFloorTile* pInstance = new CNullFloorTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CNullFloorTile * CNullFloorTile::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos)
{
	CNullFloorTile* pInstance = new CNullFloorTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

HRESULT CNullFloorTile::Add_Component()
{
	return S_OK;
}