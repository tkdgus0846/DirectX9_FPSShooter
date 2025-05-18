#pragma once
#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

enum EdgeIndex
{
	LEFT_TOP, LEFT_BOTTOM, RIGHT_TOP, RIGHT_BOTTOM, EDGEEND
};

class CWallTex : public CVIBuffer
{
private:
	explicit CWallTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CWallTex(const CWallTex& rhs);
	virtual ~CWallTex();

public:
	HRESULT		Ready_Buffer();

public:
	static CWallTex*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void);
private:
	virtual void Free(void);
};

END