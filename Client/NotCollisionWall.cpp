#include "NotCollisionWall.h"

#include "Wall.h"
#include "Export_Function.h"

CNotCollisionWall::CNotCollisionWall(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CNotCollisionWall::CNotCollisionWall(const CNotCollisionWall & rhs)
	: CBehavior(rhs)
{
}

CNotCollisionWall::~CNotCollisionWall()
{
}

HRESULT CNotCollisionWall::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CNotCollisionWall::Update_Component(const _float & fTimeDelta)
{
	CCollider* pCollider = dynamic_cast<CCollider*>(m_pGameObject->Get_Component(L"BodyCollider", ID_ALL));
	NULL_CHECK_RETURN(pCollider, BEHAVIOR_FAIL);

	auto uMap = pCollider->Get_CollisionList();

	if (uMap.empty())
		return BEHAVIOR_SUCCES;
	else
	{
		for (auto iter : uMap)
		{
			if (dynamic_cast<CWall*>(iter.second.OtherGameObject))
				return BEHAVIOR_FAIL;
		}
	}

	return BEHAVIOR_SUCCES;
}

void CNotCollisionWall::LateUpdate_Component(void)
{
}

void CNotCollisionWall::Render_Component(void)
{
}

CNotCollisionWall * CNotCollisionWall::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CNotCollisionWall* pInstance = new CNotCollisionWall(pGraphicDev);

	if (pInstance->Ready_Behavior())
	{
		Safe_Release(pInstance);
		return nullptr;
	}
	return pInstance;
}

CComponent * CNotCollisionWall::Clone(void)
{
	return new CNotCollisionWall(*this);
}

void CNotCollisionWall::Free()
{
	__super::Free();
}
