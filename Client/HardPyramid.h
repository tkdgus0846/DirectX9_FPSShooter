#pragma once
#include "Pyramid.h"

class CHardPyramid :
	public CPyramid
{
private:
	explicit CHardPyramid(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CHardPyramid();

	virtual HRESULT Add_Component() override;

public:
	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"HardPyramid"; }
};

