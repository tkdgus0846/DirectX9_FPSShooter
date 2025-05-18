#pragma once
#include "UI.h"

BEGIN(Engine)

class CTexture;
class CRcTex;
class CAnimation;

END

class CDisc :
	public CUI
{
private:
	CDisc(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CDisc();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	void		Set_ViewMatrix_UI();
	void		Set_ViewMatrix_UI(_float fX, _float fY);
	_int		Compute_Num(_int& pPlayerDisc);
	void		Redner_Disc();


private:
	Engine::CTexture*		m_pTextureCom = nullptr;

	D3DXMATRIX				matWorld, matView;
	vector<CRcTex*>			m_vecRc;

	_int m_MaxNumber = 3;
	_int m_iStartNum = 26;

public:
	static CDisc*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

