#include "stdafx.h"

#include "Creature.h"
#include "Collider.h"
#include "Export_Function.h"

CCreature::CCreature(LPDIRECT3DDEVICE9 pGrapicDev)
	: CGameObject(pGrapicDev), m_fSpeed(0.f)
	, m_iHp(0), m_iAttack(0), m_iMaxHp(5)
{
}

CCreature::~CCreature()
{
}

HRESULT CCreature::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CCreature::Update_GameObject(const _float & fTimeDelta)
{
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CCreature::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CCreature::Render_GameObject(void)
{
	__super::Render_GameObject();
}

void CCreature::OnCollisionEnter(const Collision * collsion)
{
}

void CCreature::OnCollisionStay(const Collision * collision)
{
	// ����ü�鳢�� �о�� �ڵ�.
	if (Get_WorldTime() < 3.f) 
		return;

	if (collision->MyCollider == Get_Component(L"BodyCollider", ID_ALL) && collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		_vec3 amountVec = collision->amountVec;
		if (m_pTransform == nullptr) return;

		_float fps60 = Engine::Get_Timer(L"Timer_FPS60");

		switch (collision->CollisionDir)
		{
			/*case DIR_UP:
			m_pTransform->m_vInfo[INFO_POS].y -= amountVec.y;
			break;
			case DIR_DOWN:
			m_pTransform->m_vInfo[INFO_POS].y += amountVec.y;
			break;*/
		case DIR_LEFT:
			m_pTransform->m_vInfo[INFO_POS].x += fps60*amountVec.x * 6;
			break;
		case DIR_RIGHT:
			m_pTransform->m_vInfo[INFO_POS].x -= fps60*amountVec.x * 6;
			break;
		case DIR_FRONT:
			m_pTransform->m_vInfo[INFO_POS].z -= fps60*amountVec.z * 6;
			break;
		case DIR_BACK:
			m_pTransform->m_vInfo[INFO_POS].z += fps60*amountVec.z * 6;
			break;
		default:
			break;
		}

	}


}

void CCreature::OnCollisionExit(const Collision * collision)
{
}

void CCreature::Free()
{
	__super::Free();
}
