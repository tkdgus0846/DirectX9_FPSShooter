#pragma once
#include "UI.h"
BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimation;

END

class CUltimateUI :
	public CUI
{
	enum ULTIMATEUI
	{
		ULTIMATE_GUAGE,
		ULTIMATE_VORTEX,
		ULTIMATE_END
	};

public:
	CUltimateUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CUltimateUI();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	D3DXMATRIX				matWorld, matView;

	CRcTex* m_sRcTex;
	CRcTex* m_dRcTex;
	array<CComponent*, ULTIMATE_END> m_arrMap;

public:
	static CUltimateUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};