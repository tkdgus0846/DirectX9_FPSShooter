#pragma once

#include "Component.h"

BEGIN(Engine)

class CPickingSphere : public CComponent
{
protected:
	explicit CPickingSphere(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPickingSphere(const CPickingSphere& rhs);
	virtual ~CPickingSphere();

public:
	HRESULT Ready_PickingSphere();
	virtual	_int Update_Component(const _float& fTimeDelta) override;
	virtual void Render_Component() override;

public:
	void SetCenter(_vec3 vCenter) { m_pBoundingSphere->vCenter = vCenter; }
	void SetCenter(float fX, float fY, float fZ)
	{
		m_pBoundingSphere->vCenter.x = fX;
		m_pBoundingSphere->vCenter.y = fY;
		m_pBoundingSphere->vCenter.z = fZ;
	}
	void SetRadius(float fRadius) { m_pBoundingSphere->fRadius = fRadius; }
	float GetRadius() { m_pBoundingSphere->fRadius; }
	const BoundingSphere* GetBoundingSphere() { return m_pBoundingSphere; }

	void Set_PickingSphere(float fSize = 3.f);
	static CPickingSphere* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CPickingSphere * Clone(void) override;

private:
	_bool						m_bIsRender;
	LPD3DXMESH					m_pMesh;
	_vec3						m_vOffsetPoint;
	BoundingSphere*				m_pBoundingSphere;
	IDirect3DBaseTexture9*		m_BlueTexture;

private:
	virtual void Free(void) override;
};

END