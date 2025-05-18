#pragma once
#include "Monster.h"

BEGIN(Engine)
class CAnimation;
END

class CWormBody;
class CWormTail;
class CWormHead : public CMonster
{
private:
	explicit CWormHead(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWormHead();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void SetDead(_bool bDead = true) final { CGameObject::SetDead(bDead); }
	void Set_Move(_bool bSwitch) { m_bMove = bSwitch; }
	_bool Get_Move() { return m_bMove; }

private:
	_bool Dead_Production();	// 보스 죽는 효과 끝나면 true 반환핢...
	virtual HRESULT Add_Component() override;

private:
	Engine::CAnimation*	m_pAnimation;

	vector<CWormBody*>	m_vecBody;
	CWormTail*			m_pTail;
	_bool				m_bMove;
	_bool				m_bCutScene;
	_float				m_fCurAngle;
	_float				m_fPreAngle;
	_float				m_fCurTime1;
	_float				m_fPreTime1;
	_float				m_fCurTime2;
	_float				m_fPreTime2;

public:
	static CWormHead*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);

private:
	virtual void Free(void) override;
};

