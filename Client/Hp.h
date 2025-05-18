#pragma once
#include "UI.h"
#include "Player.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimation;

END

class CHp :
	public CUI
{
public:
	CHp(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CHp();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	void		Set_ViewMatrix_UI(_float fX, _float fY);
	_int		Compute_Hp(_int& pPlayerHp);

private:
	Engine::CTexture*		m_pTextureCom;
	D3DXMATRIX				matWorld, matView;

private:
	_int m_iMaxHp = 5;
	_int m_iTotalHp = 20;
	_int m_iCurrentHp = 0;
	_int pPlayerHp = 20;

	vector<CRcTex*> m_vecRc;

public:
	static CHp*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};
