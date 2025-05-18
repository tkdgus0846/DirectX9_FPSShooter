#pragma once
#include "Monster.h"

class CNubBoss : public CMonster
{
private:
	explicit CNubBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNubBoss();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void SetDead(_bool bDead = true) final { CGameObject::SetDead(bDead); }

private:
	_bool Dead_Production();	// 보스 죽는 효과 끝나면 true 반환핢...
	virtual void	Get_Damaged(_int Damage) final;
	virtual HRESULT Add_Component() override;
	
private:
	_float m_fCurTime1;
	_float m_fPreTime1;
	_bool  m_bCutScene;

public:
	static CNubBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

private:
	virtual void Free(void) override;
};

