#include "Cactus2.h"
#include "Export_Function.h"


Cactus2::Cactus2(LPDIRECT3DDEVICE9 pGraphicDev)
	: Cactus(pGraphicDev)
{
	Set_ObjTag(Tag());
}

Cactus2::~Cactus2()
{
}

CGameObject * Cactus2::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Cactus2* pInstance = new Cactus2(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT Cactus2::Add_Component()
{
	HRESULT hResult = __super::Add_Component();

	CComponent *pComponent;
	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Cactus2", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Cactus2", pComponent });

	return hResult;
}