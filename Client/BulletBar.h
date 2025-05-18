#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;

END

class CBulletBar :
	public CUI
{
private:
	CBulletBar(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBulletBar();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	Engine::CRcTex*			m_pBufferCom;
	Engine::CTexture*		m_pTextureCom;
	D3DXMATRIX  matWorld, matView;

public:
	static CBulletBar*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};


