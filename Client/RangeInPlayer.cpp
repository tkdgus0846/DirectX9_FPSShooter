#include "RangeInPlayer.h"

#include "Player.h"
#include "Export_Function.h"

CRangeInPlayer::CRangeInPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: CBehavior(pGraphicDev), m_bReturn(false)
{
}

CRangeInPlayer::CRangeInPlayer(const CRangeInPlayer & rhs)
	: CBehavior(rhs), m_bReturn(rhs.m_bReturn)
{
}

CRangeInPlayer::~CRangeInPlayer()
{
}

HRESULT CRangeInPlayer::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CRangeInPlayer::Update_Component(const _float & fTimeDelta)
{
	CComponent* pComponent = m_pGameObject->Get_Component(L"Range", ID_ALL);

	for (auto iter : dynamic_cast<CCollider*>(pComponent)->Get_CollisionList())
	{
		if (nullptr != dynamic_cast<CPlayer*>(iter.second.OtherGameObject))
		{
			if (m_bReturn == true)
				return BEHAVIOR_SUCCES;
			else
				return BEHAVIOR_FAIL;
		}
	}

	if (m_bReturn == true)
		return BEHAVIOR_FAIL;
	else
		return BEHAVIOR_SUCCES;
}

CRangeInPlayer * CRangeInPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRangeInPlayer* pInstance = new CRangeInPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CRangeInPlayer::Clone(void)
{
	return new CRangeInPlayer(*this);
}

void CRangeInPlayer::Free()
{
	__super::Free();
}
