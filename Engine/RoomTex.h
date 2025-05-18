#pragma once
#include "VIBuffer.h"

BEGIN(Engine)

class CRoomTex : public CVIBuffer
{
private:
	explicit CRoomTex(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CRoomTex(const CRoomTex& rhs);
	virtual ~CRoomTex();

public:
	HRESULT		Ready_Buffer(void);

public:
	static CRoomTex*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*	Clone(void);
private:
	virtual void Free(void);
};

END