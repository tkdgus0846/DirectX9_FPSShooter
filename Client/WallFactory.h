#pragma once
#include "Factory.h"

class CWallFactory :
	public CFactory
{
	DECLARE_SINGLETON(CWallFactory)
public:
	CWallFactory();
	virtual ~CWallFactory();

public:
	HRESULT Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev);
};

#define WALL_FACTORY CWallFactory::GetInstance()