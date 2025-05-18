#pragma once
#include "Base.h"
#include "Particle.h"
#include "Export_Function.h"

class CParticlePool : public CBase
{
	friend class CParticleMgr;

private:
	CParticlePool();
	~CParticlePool();

	CParticle* CParticlePool::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar* ParticleName, _int ParticleNum, const _vec3& vPos, const _vec3& Origin, const _vec3& boundingSize = { 0.f,0.f,0.f }, _bool bIsInRoom = false);

	void		Push(CParticle* pObj);

	list<CParticle*>		m_ParticlePool;
	int				m_iCreateCnt = 0;

	virtual void Free(void) override;
	static CParticlePool* Create();

};

class CParticleMgr : public CBase
{
	DECLARE_SINGLETON(CParticleMgr)
private:
	explicit CParticleMgr();
	virtual ~CParticleMgr();

public:
	void Reserve(LPDIRECT3DDEVICE9 pDevice, _uint cnt, const _tchar* name);

	CParticle* CParticleMgr::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar* ParticleName, _int ParticleNum, const _vec3& vPos, const _vec3& Origin = { 0.f,0.f,0.f }, const _vec3& boundingSize = { 0.f,0.f,0.f }, _bool bIsInRoom = false);

	void		Push(const _tchar* name, CParticle* pParticle);

	virtual void Free(void) override;

private:
	unordered_map<const _tchar*, CParticlePool*> m_ParticlePool;
};

