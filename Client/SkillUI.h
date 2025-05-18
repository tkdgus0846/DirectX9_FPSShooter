#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimation;

END

enum SKILLUI
{
	TIMESTOP,
	GRAVITION,
	TACTICAL,
	COOLTIME,
	SKILLEND
};


class CSkillUI : public CUI
{

protected:
	explicit CSkillUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSkillUI();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	D3DXMATRIX  matWorld, matView;

	CRcTex* m_pRcTex = nullptr;
	CTexture* m_pTexture = nullptr;
	CAnimation* Ani1 = nullptr;
	CAnimation* Ani2 = nullptr;
	CAnimation* Ani3 = nullptr;

	_bool	m_bAimHack = false;
	_bool	m_bGravition = false;
	_bool	m_bJump = false;

	_bool	m_bRenderEnable;

public:
	static CSkillUI*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};
