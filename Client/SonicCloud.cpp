#include "SonicCloud.h"


CSonicCloud::CSonicCloud(LPDIRECT3DDEVICE9 pGraphicDev) :
	CGameObject(pGraphicDev)
{

}

CSonicCloud::~CSonicCloud()
{
}

_int CSonicCloud::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);
	return 0;
}

void CSonicCloud::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CSonicCloud::Render_GameObject(void)
{
	__super::Render_GameObject();
}

HRESULT CSonicCloud::Add_Component()
{
	
	return S_OK;
}

CSonicCloud * CSonicCloud::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSonicCloud*		pInstance = new CSonicCloud(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
