#include "Rush.h"

#include "Bullet.h"
#include "Export_Function.h"
#include "..\Engine\SoundMgr.h"

CRush::CRush(LPDIRECT3DDEVICE9 pGraphicDev)
	:CBehavior(pGraphicDev)
{
}

CRush::CRush(const CRush & rhs)
	: CBehavior(rhs)
{
}

CRush::~CRush()
{
}

HRESULT CRush::Ready_Behavior()
{
	HRESULT result = __super::Ready_Behavior();

	return result;
}

_int CRush::Update_Component(const _float & fTimeDelta)
{
	CCollider* pBodyCollider = dynamic_cast<CCollider*>(m_pGameObject->Get_Component(L"BodyCollider", ID_ALL));
	NULL_CHECK_RETURN(pBodyCollider, BEHAVIOR_ERROR);
	CTransform* pTransform = m_pGameObject->m_pTransform;

	_float fSpeed = 0.f;
	FAILED_CHECK_RETURN(m_pBlackBoard->Get_Type(L"fSpeed", fSpeed), BEHAVIOR_ERROR);

	auto uMap = pBodyCollider->Get_CollisionList();

	if (uMap.empty())
	{
		pTransform->Move_Walk(fSpeed * 3.5f, fTimeDelta);
		return BEHAVIOR_RUNNING;
	}
	else
	{
		for (auto& iter : uMap)
		{
			if (dynamic_cast<CBullet*>(iter.second.OtherGameObject))
				return BEHAVIOR_RUNNING;
		}
		Engine::Shake_Camera(SHAKE_Y, 1.5f, 5.f);
		STOP_PLAY_SOUND(L"sfxvanquish.wav", SOUND_ENEMY, 1.f);
		return BEHAVIOR_SUCCES;
	}

	return BEHAVIOR_ERROR;
}

CRush * CRush::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRush* pInstance = new CRush(pGraphicDev);

	if (FAILED(pInstance->Ready_Behavior()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CRush::Clone(void)
{
	return new CRush(*this);
}

void CRush::Free()
{
	__super::Free();
}
