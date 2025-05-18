#include "Cactus3.h"
#include "Export_Function.h"



Cactus3::Cactus3(LPDIRECT3DDEVICE9 pGraphicDev)
	: Cactus(pGraphicDev)
{
	Set_ObjTag(Tag());
}

Cactus3::~Cactus3()
{
}

CGameObject * Cactus3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Cactus3* pInstance = new Cactus3(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT Cactus3::Add_Component()
{
	HRESULT hResult = __super::Add_Component();

	CComponent *pComponent;
	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Cactus3", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Cactus3", pComponent });

	return hResult;
}
