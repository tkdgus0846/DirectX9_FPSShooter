#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimation;

END

class CCoin :
	public CUI
{
private:
	CCoin(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCoin();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	_int		Compute_Num(string PlayerCoin);

private:
	Engine::CTexture*		m_pTextureCom = nullptr;

	D3DXMATRIX				matWorld, matView;
	vector<CRcTex*>			m_vecRc;
	
	_int m_MaxNumber = 3;
	_int m_iStartNum = 26;

public:
	static CCoin*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

