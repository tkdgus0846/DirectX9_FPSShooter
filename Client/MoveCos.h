#pragma once
#include "Behavior.h"

class CMoveCos : public CBehavior
{
private:
	explicit CMoveCos(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMoveCos(const CMoveCos& rhs);
	virtual ~CMoveCos();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {};

	void Set_Follow() { m_bIsFollow = true; }
	void Set_MoveTime(const _float& fTime = 4.f) { m_fTimer = fTime; }

private:
	_vec3 m_vDir;	// 한 축의 성분을 제외한 이동 방향.
	_bool m_bStart;
	_bool m_bIsFollow;
	_float m_fTime;
	_float m_fFstSpeed;

public:
	static CMoveCos* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

