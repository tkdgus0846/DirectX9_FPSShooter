#pragma once
#include "Base.h"
#include "Effect.h"
#include "Export_Function.h"

class CEffectPool : public CBase
{
	friend class CEffectManager;

private:
	CEffectPool();
	~CEffectPool();

	CEffect* CEffectPool::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar* name, const _vec3 & vPos, const _vec3& vScale = { 1.f,1.f,1.f }, _float fAnimationTime = 0.1f, _bool bEndByTime = FALSE, _float fLifeSpan = 1.f);

	void		Push(CEffect* pObj);

	list<CEffect*>		m_EffectPool;
	int				m_iCreateCnt = 0;

	virtual void Free(void) override;
	static CEffectPool* Create();

};

class CEffectManager : public CBase
{
	DECLARE_SINGLETON(CEffectManager)
private:
	explicit CEffectManager();
	virtual ~CEffectManager();

public:
	void Reserve(LPDIRECT3DDEVICE9 pDevice, _uint cnt, const _tchar* name);

	CEffect* CEffectManager::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar* name, const _vec3 & vPos, const _vec3& vScale = { 1.f,1.f,1.f }, _float fAnimationTime = 0.1f, _bool bEndByTime = FALSE, _float fLifeSpan = 1.f);

	void		Push(const _tchar* name, CEffect* pEffect);

	virtual void Free(void) override;

private:
	unordered_map<const _tchar*, CEffectPool*> m_EffectPool;
};

