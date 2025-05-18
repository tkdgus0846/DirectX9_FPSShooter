#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimation;

END

class CCrossHair :
	public CUI
{
private:
	CCrossHair(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCrossHair();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	D3DXMATRIX  matWorld, matView;

public:
	static CCrossHair*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

