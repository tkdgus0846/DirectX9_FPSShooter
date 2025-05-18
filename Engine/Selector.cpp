#include "stdafx.h"
#include "Selector.h"

#include "Export_Utility.h"

CSelector::CSelector(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CSelector::CSelector(const CSelector & rhs)
	:CBehavior(rhs)
{
}

CSelector::~CSelector()
{
}

HRESULT CSelector::Ready_Behavior()
{
	for (_uint i = 0; i < ID_END; ++i)
	{
		for (auto iter : m_VecComponents[i])
		{
			dynamic_cast<CBehavior*>(iter.pComponent)->m_pBlackBoard = m_pBlackBoard;
			dynamic_cast<CBehavior*>(iter.pComponent)->Ready_Behavior();
		}
	}

	__super::Ready_Composite();

	return S_OK;
}

_int CSelector::Update_Component(const _float & fTimeDelta)
{
	if (0 == m_VecComponents[ID_UPDATE].size())
		return BEHAVIOR_FAIL;

	if (BEHAVIOR_FAIL == update_Decorator(fTimeDelta))
		return BEHAVIOR_FAIL;

	_int iResult = m_iterCurComponent->pComponent->Update_Component(fTimeDelta);

	switch (iResult)
	{
	case BEHAVIOR_RUNNING:
		return BEHAVIOR_RUNNING;

	case BEHAVIOR_SUCCES:
		m_iterPreComponent = m_VecComponents[ID_UPDATE].begin();
		return BEHAVIOR_SUCCES;

	case BEHAVIOR_FAIL:
		++m_iterPreComponent;

		if (m_iterPreComponent == m_VecComponents[ID_UPDATE].end())
		{
			m_iterPreComponent = m_VecComponents[ID_UPDATE].begin();
			return BEHAVIOR_FAIL;
		}
		else
			return BEHAVIOR_RUNNING;

	case BEHAVIOR_ERROR:
		return BEHAVIOR_ERROR;
	}

	return BEHAVIOR_FAIL;
}

void CSelector::LateUpdate_Component(void)
{
	if (0 == m_VecComponents[ID_UPDATE].size())
		return;

	m_iterCurComponent->pComponent->LateUpdate_Component();

	if (m_iterCurComponent != m_iterPreComponent)
		m_iterCurComponent = m_iterPreComponent;
}

void CSelector::Render_Component(void)
{
	__super::Render_Component();
}

CSelector * CSelector::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSelector* pInstance = new CSelector(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CSelector::Clone(void)
{
	return new CSelector(*this);
}

void CSelector::Free()
{
	__super::Free();
}
