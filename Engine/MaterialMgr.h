#pragma once

#include "Material.h"

BEGIN(Engine)

class CMaterialMgr : public CBase
{
	DECLARE_SINGLETON(CMaterialMgr)

private:
	explicit CMaterialMgr();
	virtual ~CMaterialMgr();

public:
	//HRESULT Ready_Material(LPDIRECT3DDEVICE9 pGraphicDev,
						
};

END