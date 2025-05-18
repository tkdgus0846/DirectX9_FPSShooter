#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class CFrustrumNormalTex :
	public CVIBuffer
{
private:
	explicit CFrustrumNormalTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CFrustrumNormalTex(const CFrustrumNormalTex& rhs);
	virtual ~CFrustrumNormalTex();

public:
	HRESULT		Ready_Buffer(void);

public:
	static CFrustrumNormalTex*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

	virtual CComponent*	Clone(void);
private:
	virtual void Free(void);

	void ComputeNormal(_vec3* p0, _vec3* p1, _vec3* p2, _vec3* out);
};

END

