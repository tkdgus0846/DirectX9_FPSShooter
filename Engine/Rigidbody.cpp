#include "stdafx.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "Transform.h"
#include "Export_Function.h"

CRigidbody::CRigidbody(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
{
}

CRigidbody::CRigidbody(const CRigidbody & rhs)
	:CComponent(rhs)
{
}


CRigidbody::~CRigidbody()
{
}

HRESULT CRigidbody::Ready_Rigidbody(void)
{
	return S_OK;
}

_int CRigidbody::Update_Component(const _float & fTimeDelta)
{
	m_vCurPos = m_pGameObject->m_pTransform->m_vInfo[INFO_POS];

	m_vVelocity = m_vCurPos - m_vPrevPos;
	D3DXVec3Normalize(&m_vMoveDir, &m_vVelocity);
	m_fSpeed = m_vVelocity.Length();
	
	m_vPrevPos = m_vCurPos;
	return 0;
}

void CRigidbody::LateUpdate_Component(void)
{
}



CRigidbody * CRigidbody::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRigidbody* pInstance = new CRigidbody(pGraphicDev);

	if (FAILED(pInstance->Ready_Rigidbody()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

CComponent * CRigidbody::Clone(void)
{
	return new CRigidbody(*this);
}

void CRigidbody::Collision_OtherBody(CRigidbody * otherBody, const Collision* collision)
{
	_float fDeltaTime = Engine::Get_Timer(L"Timer_FPS60");

	_float otherSpeed = otherBody->m_fSpeed;
	_vec3 otherVelocity = otherBody->m_vVelocity;

	_vec3 resultVelocity;

	_float dotProduct = m_vMoveDir.Dot(otherBody->m_vMoveDir);

	if (dotProduct > 0)
	{
		if (m_fSpeed > otherSpeed)
		{
			resultVelocity = m_vVelocity;
		}
		else
		{
			resultVelocity = otherVelocity;
		}
	}
	else if (dotProduct < 0)
	{
		resultVelocity = m_vVelocity + otherVelocity;
	}
	else if (dotProduct == 0 && (m_fSpeed == 0.f || otherSpeed == 0.f))
	{
		resultVelocity = (m_fSpeed > otherSpeed) ? m_vVelocity: otherVelocity;
	}
	else if (dotProduct == 0)
	{
		resultVelocity = m_vVelocity;
	}

	m_pGameObject->m_pTransform->Move_Velocity(resultVelocity);
	//otherBody->Get_GameObject()->m_pTransform->Move_Velocity(resultVelocity);
}

void CRigidbody::Free(void)
{
	__super::Free();
}
