#pragma once
#include "Cactus.h"
class Cactus5 :
	public Cactus
{
protected:
	explicit Cactus5(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~Cactus5();

public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Cactus5"; }
	virtual HRESULT Add_Component() override;
};

