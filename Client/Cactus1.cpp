#include "Cactus1.h"
#include "Export_Function.h"


Cactus1::Cactus1(LPDIRECT3DDEVICE9 pGraphicDev)
	: Cactus(pGraphicDev)
{
	Set_ObjTag(Tag());
}

Cactus1::~Cactus1()
{
}

CGameObject * Cactus1::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Cactus1* pInstance = new Cactus1(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT Cactus1::Add_Component()
{
	HRESULT hResult = __super::Add_Component();

	CComponent *pComponent;
	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Cactus1", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"Cactus1", pComponent });

	return hResult;
}
