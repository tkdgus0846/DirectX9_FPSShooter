#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;

END

class CCutSceneUI :
	public CUI
{
public:
	explicit CCutSceneUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCutSceneUI();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	CRcTex* m_pRcTex;
	CTexture* m_pTexture;

	_float		m_fUp = 250.f;
	_float		m_fDown = -250.f;

public:
	static CCutSceneUI*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};