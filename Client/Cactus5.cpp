#include "Cactus5.h"
#include "Export_Function.h"


Cactus5::Cactus5(LPDIRECT3DDEVICE9 pGraphicDev)
	: Cactus(pGraphicDev)
{
	Set_ObjTag(Tag());
}

Cactus5::~Cactus5()
{
}

CGameObject * Cactus5::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Cactus5* pInstance = new Cactus5(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT Cactus5::Add_Component()
{
	HRESULT hResult = __super::Add_Component();

	CComponent *pComponent;
	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(Tag(), this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ Tag(), pComponent });

	return hResult;
}
