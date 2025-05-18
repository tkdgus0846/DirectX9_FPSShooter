#include "stdafx.h"
#include "BulletMgr.h"
#include "NormalBullet.h"
#include "FireBullet.h"
#include "IceBullet.h"
#include "VortexBullet.h"
#include "SwordBullet.h"
#include "LaserBullet.h"
#include "RedLaserBullet.h"
#include "EnemyBullet.h"
#include "SonicBird.h"
#include "ShockWave.h"
#include "RootAttack.h"

IMPLEMENT_SINGLETON(CBulletMgr)



CBulletPool::CBulletPool()
{
}

CBulletPool::~CBulletPool()
{
	//Free();
}

void CBulletPool::Push(CBullet * pObj)
{
	if (nullptr == pObj)
		return;

	auto colNameVec = pObj->Get_ColNameVec();

	for (int i = 0; i < colNameVec.size(); i++)
	{
		CCollider* collider = dynamic_cast<CCollider*>(pObj->Get_Component(colNameVec[i], ID_ALL));

		if (collider == nullptr) continue;

		collider->Get_CollisionList().clear();
		collider->Set_Enable(FALSE);
	}

	m_BulletPool.push_back(pObj);
}

void CBulletPool::Free(void)
{
	for_each(m_BulletPool.begin(), m_BulletPool.end(), CDeleteObj());
	m_BulletPool.clear();
}

//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

CBulletPool* CBulletPool::Create()
{
	CBulletPool*		pInstance = new CBulletPool();
	return pInstance;
}

CBullet* CBulletPool::Pop(const _tchar* name, LPDIRECT3DDEVICE9 pDevice, const _vec3 & vPos, const _vec3 & vDir, const _vec3& vScale, bool bIsEnemyBullet, const _float& fSpeed)
{
	CBullet*		pBullet = nullptr;

	if (m_BulletPool.empty())
	{
		if (name == L"FireBullet")
		{
			pBullet = CFireBullet::Create(pDevice);
		}
		else if (name == L"NormalBullet")
		{
			pBullet = CNormalBullet::Create(pDevice);
		}
		else if (name == L"IceBullet")
		{
			pBullet = CIceBullet::Create(pDevice);
		}
		else if (name == L"VortexBullet")
		{
			pBullet = CVortexBullet::Create(pDevice);
		}
		else if (name == L"SwordBullet")
		{
			pBullet = CSwordBullet::Create(pDevice);
		}
		else if (name == L"LaserBullet")
		{
			pBullet = CLaserBullet::Create(pDevice);
		}
		else if (name == L"RedLaserBullet")
		{
			pBullet = CRedLaserBullet::Create(pDevice);
		}
		else if (name == L"EnemyBullet")
		{
			pBullet = CEnemyBullet::Create(pDevice);
		}
		else if (name == L"SonicBird")
		{
			pBullet = CSonicBird::Create(pDevice);
		}
		else if (name == L"ShockWave")
		{
			pBullet = CShockWave::Create(pDevice);
		}
		else if (name == L"RootAttack")
		{
			pBullet = CRootAttack::Create(pDevice);
		}
		++m_iCreateCnt;
		
	}

	else
	{
		pBullet = m_BulletPool.front();
		m_BulletPool.pop_front();
	}

	if (nullptr == pBullet)
		return nullptr;

	(pBullet)->Set_Pos(vPos);
	(pBullet)->Set_Dir(vDir);
	(pBullet)->SetIsEnemy(bIsEnemyBullet);
	(pBullet)->SetAge();
	(pBullet)->SetDead(false);
	(pBullet)->m_pTransform->Set_Scale(vScale);
	(pBullet)->Pop_Initialize();

	if (fSpeed != -1.f)
		(pBullet)->SetSpeed(fSpeed);

	Engine::Add_Collider(pBullet);


	auto colNameVec = pBullet->Get_ColNameVec();
	_bool bIsRender = Engine::Collider_GetIsRender();

	for (int i = 0; i < colNameVec.size(); i++)
	{
		CCollider* collider = dynamic_cast<CCollider*>(pBullet->Get_Component(colNameVec[i], ID_ALL));

		if (collider == nullptr) continue;

		collider->Set_Enable(TRUE);
		collider->Set_IsRender(bIsRender);

		collider->Get_CollisionList().clear();

		if (bIsEnemyBullet == true)
		{
			Engine::Change_ColGroup(collider, COL_ENEMYBULLET);
		}
		else
		{
			Engine::Change_ColGroup(collider, COL_PLAYERBULLET);
		}
	}	

	

	return pBullet;
}

CBulletMgr::CBulletMgr()
{
}


CBulletMgr::~CBulletMgr()
{
	Free();
}

void CBulletMgr::Reserve(LPDIRECT3DDEVICE9 pDevice, _uint cnt, const _tchar* name)
{
	for (int i = 0; i < cnt; i++)
	{
		CBullet* pBullet = nullptr;
		if (name == L"FireBullet")
		{
			pBullet = CFireBullet::Create(pDevice);
		}
		else if (name == L"NormalBullet")
		{
			pBullet = CNormalBullet::Create(pDevice);
		}
		else if (name == L"IceBullet")
		{
			pBullet = CIceBullet::Create(pDevice);
		}
		else if (name == L"VortexBullet")
		{
			pBullet = CVortexBullet::Create(pDevice);
		}
		else if (name == L"SwordBullet")
		{
			pBullet = CSwordBullet::Create(pDevice);
		}
		else if (name == L"LaserBullet")
		{
			pBullet = CLaserBullet::Create(pDevice);
		}
		else if (name == L"RedLaserBullet")
		{
			pBullet = CRedLaserBullet::Create(pDevice);
		}
		else if (name == L"EnemyBullet")
		{
			pBullet = CEnemyBullet::Create(pDevice);
		}
		else if (name == L"ShockWave")
		{
			pBullet = CShockWave::Create(pDevice);
		}
		else if (name == L"RootAttack")
		{
			pBullet = CRootAttack::Create(pDevice);
		}
		
		if (m_BulletPool[name] == nullptr)
		{
			m_BulletPool[name] = CBulletPool::Create();
		}
		Push(name, pBullet);
	}
}

void CBulletMgr::Push(const _tchar* name, CBullet* pBullet)
{
	if (m_BulletPool[name] == nullptr) return;

	m_BulletPool[name]->Push(pBullet);
}


void CBulletMgr::Free(void)
{
	for_each(m_BulletPool.begin(), m_BulletPool.end(), CDeleteMap());
	m_BulletPool.clear();
}

CBullet* CBulletMgr::Pop(const _tchar* name, LPDIRECT3DDEVICE9 pDevice, const _vec3& vPos, const _vec3& vDir, const _vec3& vScale, bool bIsEnemyBullet, const _float& fSpeed)
{
	if (m_BulletPool[name] == nullptr)
	{
		m_BulletPool[name] = CBulletPool::Create();
	}
	CBullet*		pBullet = m_BulletPool[name]->Pop(name, pDevice, vPos, vDir, vScale, bIsEnemyBullet, fSpeed);
	if (pBullet == nullptr)
		return nullptr;

	return pBullet;
}