#include "HardPyramid.h"
#include "Export_Function.h"

CHardPyramid::CHardPyramid(LPDIRECT3DDEVICE9 pGraphicDev)
	: CPyramid(pGraphicDev)
{
	Set_ObjTag(Tag());
}

CHardPyramid::~CHardPyramid()
{
}


HRESULT CHardPyramid::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CComponent *pComponent;

	pComponent = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"HardPyramid_Texture", this));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"HardPyramid_Texture", pComponent });

	return result;
}

CGameObject * CHardPyramid::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CHardPyramid* pInstance = new CHardPyramid(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}