#pragma once
#include "Monster.h"

BEGIN(Engine)
class CAnimation;
END

class CTreeBoss : public CMonster
{
private:
	explicit CTreeBoss(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTreeBoss();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	void Change_State() { m_bIsSummon == true ? false : true; }
	virtual void SetDead(_bool bDead = true) final { CGameObject::SetDead(bDead); }

private:
	_bool Dead_Production();	// 보스 죽는 효과 끝나면 true 반환핢...
	_vec3 m_vDefaultPos;
	_bool m_bIsSummon;
	_float m_fCurTime1;
	_float m_fPreTime1;
	CAnimation* m_pAnimation;
	_bool		m_bCutScene;

private:
	virtual HRESULT Add_Component() override;

public:
	static CTreeBoss*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

private:
	virtual void Free(void) override;
};

