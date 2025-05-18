#pragma once
#include "Cactus.h"
class Cactus3 :
	public Cactus
{
protected:
	explicit Cactus3(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~Cactus3();
public:

	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Cactus3"; }
	virtual HRESULT Add_Component() override;
};

