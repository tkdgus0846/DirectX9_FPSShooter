#include "RangeCheck.h"

#include "Export_Function.h"

CRangeCheck::CRangeCheck(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CRangeCheck::CRangeCheck(const CRangeCheck & rhs)
	: CBehavior(rhs)
{
}

CRangeCheck::~CRangeCheck()
{
}

HRESULT CRangeCheck::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CRangeCheck::Update_Component(const _float & fTimeDelta)
{
	CComponent* pComponent = m_pGameObject->Get_Component(L"Range", ID_ALL);

	if (dynamic_cast<CCollider*>(pComponent)->Get_CollisionList().empty())
		return BEHAVIOR_FAIL;
	else
	{
		for (auto iter : dynamic_cast<CCollider*>(pComponent)->Get_CollisionList())
		{
			if (nullptr != dynamic_cast<CGameObject*>(iter.second.OtherGameObject))
				return BEHAVIOR_SUCCES;
		}
	}

	return BEHAVIOR_FAIL;
}

void CRangeCheck::LateUpdate_Component(void)
{
}

void CRangeCheck::Render_Component(void)
{
}

CRangeCheck * CRangeCheck::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRangeCheck* pInstance = new CRangeCheck(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CRangeCheck::Clone(void)
{
	return new CRangeCheck(*this);
}

void CRangeCheck::Free()
{
	__super::Free();
}
