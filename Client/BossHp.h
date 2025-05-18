#pragma once
#include "UI.h"

BEGIN(Engine)

class CRcTex;
class CTexture;

END

class CCreature;

class CBossHp :
	public CUI
{
	enum BOSSMAP
	{
		BOSS_MAP_GUAGE,
		BOSS_MAP_HP,
		BOSS_MAP_FONT,
		BOSS_MAP_END
	};
	enum BOSSUI
	{
		BOSS_UI_B,
		BOSS_UI_O,
		BOSS_UI_S,
		BOSS_UI_S2,
		BOSS_UI_HP,
		BOSS_UI_GUAGE,
		BOSS_UI_END
	};

private:
	CBossHp(LPDIRECT3DDEVICE9 pGraphicDev);
	~CBossHp();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	CRcTex* m_sRcTex;
	CRcTex* m_dRcTex;
	array<CComponent*, BOSS_MAP_END> m_arrMap;

	_float	m_CurHp = 0;
	_bool	m_bStartPlayBGM;

	vector<CGameObject*> vecBoss;

public:
	static CBossHp*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};
