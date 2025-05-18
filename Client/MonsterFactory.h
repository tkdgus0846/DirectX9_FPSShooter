#pragma once
#include "Factory.h"

class CMonsterFactory :
	public CFactory
{
	DECLARE_SINGLETON(CMonsterFactory)
public:
	CMonsterFactory();
	virtual ~CMonsterFactory();

	HRESULT Ready_Factory(LPDIRECT3DDEVICE9 pGraphicDev);
};

#define MONSTER_FACTORY CMonsterFactory::GetInstance()