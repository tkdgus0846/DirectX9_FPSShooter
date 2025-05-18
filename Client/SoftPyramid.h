#pragma once
#include "Pyramid.h"

class CSoftPyramid :
	public CPyramid
{
private:
	explicit CSoftPyramid(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSoftPyramid();

	virtual void OnCollisionEnter(const Collision* collsion) override;
	virtual void OnCollisionStay(const Collision* collision) override;

	virtual HRESULT Add_Component() override;

public:
	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"SoftPyramid"; }

	virtual void	SetDead(_bool bDead = true) override;
private:
	virtual void Free(void) override;
};

