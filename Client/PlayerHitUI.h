#pragma once
#include "UI.h"

BEGIN(Engine)

class CAnimation;
class CRcTex;

END

class CPlayerHitUI :
	public CUI
{
public:
	explicit CPlayerHitUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPlayerHitUI();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	D3DXMATRIX  matWorld, matView;
	_float		m_fTime = 0.f;

public:
	static CPlayerHitUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};
