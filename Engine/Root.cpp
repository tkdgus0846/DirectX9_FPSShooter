#include "stdafx.h"
#include "Root.h"

#include "Export_Utility.h"

CRoot::CRoot(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CRoot::CRoot(const CRoot & rhs)
	:CBehavior(rhs)
{
}

CRoot::~CRoot()
{
}

HRESULT CRoot::Ready_Behavior(void)
{
	m_pBlackBoard = new CBlackBoard;

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

_int CRoot::Update_Component(const _float & fTimeDelta)
{
	_int iResult = 0;

	if (CManagement::GetInstance()->Get_TimeStopped()) return E_FAIL;

	for (_int i = 0; i < ID_END; ++i)
	{
		for (auto iter : m_VecComponents[i])
		{
			iResult = iter.pComponent->Update_Component(fTimeDelta);
			if (iResult == BEHAVIOR_ERROR)
				return E_FAIL;
		}
	}

	return S_OK;
}

void CRoot::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

void CRoot::Render_Component(void)
{
	__super::Render_Component();
}

CRoot * CRoot::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRoot* pInstance = new CRoot(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CRoot::Clone(void)
{
	return new CRoot(*this);
}

void CRoot::Free()
{
	Safe_Delete(m_pBlackBoard);
	__super::Free();
}
