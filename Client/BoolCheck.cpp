#include "BoolCheck.h"

#include "Export_Function.h"

CBoolCheck::CBoolCheck(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_pTypename(nullptr)
{
}

CBoolCheck::CBoolCheck(const CBoolCheck & rhs)
	: CBehavior(rhs), m_pTypename(rhs.m_pTypename)
{
}

CBoolCheck::~CBoolCheck()
{
}

HRESULT CBoolCheck::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CBoolCheck::Update_Component(const _float & fTimeDelta)
{
	_bool bSwitch = false;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(m_pTypename, bSwitch), BEHAVIOR_ERROR);

	if (bSwitch == true)
		return BEHAVIOR_SUCCES;
	else
		return BEHAVIOR_FAIL;
}

CBoolCheck * CBoolCheck::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBoolCheck* pInstance = new CBoolCheck(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CBoolCheck::Clone(void)
{
	return new CBoolCheck(*this);
}

void CBoolCheck::Free()
{
	__super::Free();
}
