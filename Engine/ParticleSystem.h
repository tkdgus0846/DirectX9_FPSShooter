#pragma once
#include "Component.h"

class CParticleSystem : public CComponent
{
protected:
	explicit CParticleSystem(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CParticleSystem(const CParticleSystem& rhs);
	virtual ~CParticleSystem();
public:
	virtual HRESULT		Ready_Particle(void) PURE;

	virtual void Reset();
	virtual void ResetParticle(Particle* particle) PURE;
	virtual void AddParticle();

	virtual _int Update_Component(const _float& fTimeDelta) override;
	virtual void LateUpdate_Component() override;
	virtual void Render_Component() override;

	void SetOffset(const _vec3& origin) { m_Offset = origin; }
	void SetBoundingBox(const BoundingBox& boundingBox) { m_BoundingBox = boundingBox; }
	void SetBoundingSize(const _vec3& vSize)
	{
		m_BoundingBox._offsetMax = vSize / 2;
		m_BoundingBox._offsetMin = -vSize / 2;
	}
	void SetEmitRate(const float& emitRate) { m_EmitRate = emitRate; }
	void SetNumParticle(const int& numParticle);
	_int GetParticlesSize() { return m_Particles.size(); }

	bool IsEmpty();
	bool IsDead();
	void SetDead();

protected:
	virtual void RemoveDeadParticles();
	virtual void Free(void) override;

	virtual void PreRender();
	virtual void PostRender();

	virtual void		Render_Particle(void) PURE;

protected:
	_vec3					m_Offset;
	_vec3					m_Pos;

	BoundingBox				m_BoundingBox;
	float					m_EmitRate;
	float					m_Size;
	LPDIRECT3DVERTEXBUFFER9 m_VB;
	list<Particle>			m_Particles;
	int						m_MaxParticles;

	DWORD					m_VBSize;
	DWORD					m_VBOffset;
	DWORD					m_VBBatchSize;
};

