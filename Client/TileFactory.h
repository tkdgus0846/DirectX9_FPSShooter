#pragma once
#include "Factory.h"

class CTileFactory :
	public CFactory
{
	DECLARE_SINGLETON(CTileFactory)
private:
	CTileFactory();
	virtual ~CTileFactory();
	
public:
	HRESULT Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev);
};

#define TILE_FACTORY CTileFactory::GetInstance()