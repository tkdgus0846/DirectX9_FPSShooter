#pragma once
#include "Cactus.h"
class Cactus2 :
	public Cactus
{
protected:
	explicit Cactus2(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~Cactus2();

public:
	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Cactus2"; }

	virtual HRESULT Add_Component() override;
};

