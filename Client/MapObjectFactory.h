#pragma once
#include "Factory.h"

class CMapObjectFactory :
	public CFactory
{
	DECLARE_SINGLETON(CMapObjectFactory)

private:
	CMapObjectFactory();
	virtual ~CMapObjectFactory();

public:
	HRESULT Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev);
};

#define MAPOBJ_FACTORY CMapObjectFactory::GetInstance()