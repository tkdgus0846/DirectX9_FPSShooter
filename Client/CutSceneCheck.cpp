#include "CutSceneCheck.h"

#include "Export_Function.h"

CCutSceneCheck::CCutSceneCheck(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev), m_pTypename(nullptr)
{
}

CCutSceneCheck::CCutSceneCheck(const CCutSceneCheck & rhs)
	: CBehavior(rhs), m_pTypename(rhs.m_pTypename)
{
}

CCutSceneCheck::~CCutSceneCheck()
{
}

HRESULT CCutSceneCheck::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CCutSceneCheck::Update_Component(const _float & fTimeDelta)
{
	_bool bIsCutScene = false;
	m_pBlackBoard->Get_Type(m_pTypename, bIsCutScene);

	if (bIsCutScene == true)
	{
		bIsCutScene = false;
		m_pBlackBoard->Set_Type(m_pTypename, bIsCutScene);
		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_FAIL;
}

CCutSceneCheck * CCutSceneCheck::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCutSceneCheck* pInstance = new CCutSceneCheck(pGraphicDev);

	if (pInstance->Ready_Behavior())
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

CComponent * CCutSceneCheck::Clone(void)
{
	return new CCutSceneCheck(*this);
}

void CCutSceneCheck::Free()
{
	__super::Free();
}
