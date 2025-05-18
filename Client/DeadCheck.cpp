#include "DeadCheck.h"

#include "Export_Function.h"

CDeadCheck::CDeadCheck(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CDeadCheck::CDeadCheck(const CDeadCheck & rhs)
	: CBehavior(rhs)
{
}

CDeadCheck::~CDeadCheck()
{
}

HRESULT CDeadCheck::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CDeadCheck::Update_Component(const _float & fTimeDelta)
{
	if (m_pGameObject->GetDead())
		return BEHAVIOR_SUCCES;

	return BEHAVIOR_FAIL;
}

CDeadCheck * CDeadCheck::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CDeadCheck* pInstance = new CDeadCheck(pGraphicDev);

	if (pInstance->Ready_Behavior())
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

CComponent * CDeadCheck::Clone(void)
{
	return new CDeadCheck(*this);
}

void CDeadCheck::Free()
{
	__super::Free();
}
