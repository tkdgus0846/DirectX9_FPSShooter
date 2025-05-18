#pragma once
#include "Cactus.h"
class Cactus1 :
	public Cactus
{
protected:
	explicit Cactus1(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~Cactus1();

public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Cactus1"; }
	virtual HRESULT Add_Component() override;
};

