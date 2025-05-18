#include "EffectManager.h"

IMPLEMENT_SINGLETON(CEffectManager)

CEffectPool::CEffectPool()
{
}

CEffectPool::~CEffectPool()
{
}

void CEffectPool::Push(CEffect* pObj)
{
	if (nullptr == pObj)
		return;

	m_EffectPool.push_back(pObj);
}

CEffect * CEffectPool::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar * name, const _vec3 & vPos, const _vec3& vScale, _float fAnimationTime, _bool bEndByTime, _float fLifeSpan)
{
	CEffect*		pEffect = nullptr;

	if (m_EffectPool.empty())
	{
		pEffect = CEffect::Create(pDevice, name, fAnimationTime, bEndByTime, fLifeSpan);
		++m_iCreateCnt;
	}
	else
	{
		pEffect = m_EffectPool.front();
		m_EffectPool.pop_front();
	}

	if (nullptr == pEffect)
		return nullptr;

	(pEffect)->Set_Pos(vPos);
	(pEffect)->SetDead(false);
	(pEffect)->m_pTransform->Set_Scale(vScale);
	return pEffect;
}

CEffectPool* CEffectPool::Create()
{
	CEffectPool*		pInstance = new CEffectPool();
	return pInstance;
}

void CEffectPool::Free(void)
{
	for_each(m_EffectPool.begin(), m_EffectPool.end(), CDeleteObj());
	m_EffectPool.clear();
}

//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

CEffectManager::CEffectManager()
{

}

CEffectManager::~CEffectManager()
{
	Free();
}

CEffect * CEffectManager::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar * name, const _vec3 & vPos, const _vec3& vScale, _float fAnimationTime, _bool bEndByTime, _float fLifeSpan)
{
	if (m_EffectPool[name] == nullptr)
	{
		m_EffectPool[name] = CEffectPool::Create();
	}
	CEffect*		pEffect = m_EffectPool[name]->Pop(pDevice, name, vPos, vScale, fAnimationTime, bEndByTime, fLifeSpan);
	if (pEffect == nullptr)
		return nullptr;

	return pEffect;
}


void CEffectManager::Reserve(LPDIRECT3DDEVICE9 pDevice, _uint cnt, const _tchar* name)
{
	for (int i = 0; i < cnt; i++)
	{
		/*CEffect* pEffect = CEffect::Create(pDevice, name, fAnimationTime, bEndByTime, fLifeSpan);*/
		
		if (m_EffectPool[name] == nullptr)
		{
			m_EffectPool[name] = CEffectPool::Create();

			
		}
		Pop(pDevice, name, { 0.f,-50.f,0.f }, { 0.f,0.f,0.f }, 0.001f, true, 0.001f);
	}
}

void CEffectManager::Push(const _tchar* name, CEffect* pEffect)
{
	if (m_EffectPool[name] == nullptr) return;

	m_EffectPool[name]->Push(pEffect);
}

void CEffectManager::Free(void)
{
	for_each(m_EffectPool.begin(), m_EffectPool.end(), CDeleteMap());
	m_EffectPool.clear();
}
