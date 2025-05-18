#pragma once
#include "FloorTile.h"
class FloorLarge421409 :
	public CFloorTile
{
public:
	FloorLarge421409(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~FloorLarge421409();
public:
	static CGameObject* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"FloorLarge421409"; }

private:
	virtual HRESULT Add_Component() override;
};

