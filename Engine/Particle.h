#pragma once
#include "GameObject.h"

class CParticleSystem;

class CParticle : public CGameObject
{
	friend class CParticlePool;

protected:
	explicit CParticle(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CParticle();

public:
	virtual HRESULT Add_Component() override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void Render_GameObject(void) override;
	void			SetBoundingSize(const _vec3& size);
	
	void	Reset();

protected:
	const _tchar* m_ParticleName;
	CParticleSystem* m_Particle;

	_int			m_ParticleNum;
	_vec3			m_Origin;
	_vec3			m_BoundingSize;

private:
	virtual void	SetDead(_bool bDead = true) override;

private:
	static CParticle* Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar* ParticleName, _int ParticleNum, const _vec3& Pos , const _vec3& Origin);

	virtual void Free(void) override;

};

