#pragma once
#include "Cactus.h"
class Cactus4 :
	public Cactus
{
protected:
	explicit Cactus4(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~Cactus4();
public:

	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Cactus4"; }
	virtual HRESULT Add_Component() override;
};

