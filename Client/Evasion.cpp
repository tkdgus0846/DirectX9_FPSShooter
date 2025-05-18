#include "Evasion.h"

#include "Bullet.h"
#include "Export_Function.h"

CEvasion::CEvasion(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CEvasion::CEvasion(const CEvasion & rhs)
	: CBehavior(rhs)
{
}

CEvasion::~CEvasion()
{
}

HRESULT CEvasion::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CEvasion::Update_Component(const _float & fTimeDelta)
{
	CCollider* pComponent = dynamic_cast<CCollider*>(m_pGameObject->Get_Component(L"EvasBullet", ID_ALL));

	for (auto iter : pComponent->Get_CollisionList())
	{
		if (nullptr != dynamic_cast<CBullet*>(iter.second.OtherGameObject))
		{
			_vec3 vDir = m_pGameObject->m_pTransform->m_vInfo[INFO_POS]
				- iter.second.OtherGameObject->m_pTransform->m_vInfo[INFO_POS];

			_float fSpeed = 0.f;
			FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);

			if (0 > vDir.Dot(m_pGameObject->m_pTransform->m_vInfo[INFO_RIGHT]))
				m_pGameObject->m_pTransform->Move_Strafe(-fSpeed * 2.f, fTimeDelta);
			else
				m_pGameObject->m_pTransform->Move_Strafe(fSpeed * 2.f, fTimeDelta);

			return BEHAVIOR_RUNNING;
		}
	}

	return BEHAVIOR_SUCCES;
}

void CEvasion::LateUpdate_Component(void)
{
}

void CEvasion::Render_Component(void)
{
}

CEvasion * CEvasion::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEvasion* pInstance = new CEvasion(pGraphicDev);

	if (!pInstance)
		return nullptr;

	return pInstance;
}

CComponent * CEvasion::Clone(void)
{
	return new CEvasion(*this);
}

void CEvasion::Free()
{
	__super::Free();
}
