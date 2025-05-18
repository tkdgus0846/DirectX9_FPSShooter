#include "Cactus4.h"
#include "Export_Function.h"



Cactus4::Cactus4(LPDIRECT3DDEVICE9 pGraphicDev)
	: Cactus(pGraphicDev)
{
	Set_ObjTag(Tag());
}

Cactus4::~Cactus4()
{
}

CGameObject * Cactus4::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Cactus4* pInstance = new Cactus4(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT Cactus4::Add_Component()
{
	HRESULT hResult = __super::Add_Component();

	CComponent *pComponent;
	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(Tag(), this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ Tag(), pComponent });

	return hResult;
}
