#pragma once
#include "Monster.h"

BEGIN(Engine)
class CTexture;
class CRcTex;
END

class CWalkerBoss : public CMonster
{
private:
	explicit CWalkerBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWalkerBoss();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void SetDead(_bool bDead = true) final { CGameObject::SetDead(bDead); }

private:
	_bool Dead_Production();	// 보스 죽는 효과 끝나면 true 반환핢...
	virtual HRESULT Add_Component() override;
	CTexture* m_pTextureCom;
	CRcTex* m_pShadow;

	_float		m_fCurTime1;
	_float		m_fPreTime1;
	_bool		m_bCutScene;

public:
	static CWalkerBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

private:
	virtual void Free(void) override;
};

