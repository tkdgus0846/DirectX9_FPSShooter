#include "stdafx.h"
#include "Behavior.h"

#include "Export_Utility.h"

CBehavior::CBehavior(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComposite(pGraphicDev), m_fCurTime(0.f)
	, m_fPreTime(0.f), m_fTimer(0.f)
{
}

CBehavior::CBehavior(const CBehavior & rhs)
	: CComposite(rhs), m_fCurTime(rhs.m_fCurTime)
	, m_fPreTime(rhs.m_fPreTime), m_fTimer(rhs.m_fTimer)
{
}

CBehavior::~CBehavior()
{
}

HRESULT CBehavior::Ready_Behavior()
{
	return __super::Ready_Composite();
}

_int CBehavior::Update_Component(const _float & fTimeDelta)
{
	__super::Update_Component(fTimeDelta);
	return 0;
}

void CBehavior::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CBehavior::Render_Component(void)
{
	__super::Render_Component();
}

HRESULT CBehavior::Add_Decorator(CComponent * pComponent)
{
	NULL_CHECK_RETURN(pComponent, E_FAIL);

	m_DecoratorList.push_back({ nullptr, pComponent });

	return S_OK;
}

_int CBehavior::update_Decorator(const _float & fTimeDelta)
{
	for (auto Deco : m_DecoratorList)
	{
		_int iResult = Deco.pComponent->Update_Component(fTimeDelta);

		if (BEHAVIOR_FAIL == iResult)
			return BEHAVIOR_FAIL;
	}

	return BEHAVIOR_SUCCES;
}

void CBehavior::Free()
{
	for (int i = 0; i < ID_END; i++)
	{
		for (auto& comp : m_DecoratorList)
		{
			Safe_Release(comp.pComponent);
		}
	}
	__super::Free();
}
