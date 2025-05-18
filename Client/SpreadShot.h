#pragma once
#include "Behavior.h"
class CSpreadShot : public CBehavior
{
private:
	explicit CSpreadShot(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSpreadShot(const CSpreadShot& rhs);
	virtual ~CSpreadShot();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {};
	virtual void Render_Component(void) override {};

	void Setting_Option(const _tchar* pBulletTag, const _float& fSpeed,
		const _vec3& vScale = _vec3(1.f, 1.f, 1.f));
	void Setting_Spread_Option(SPREAD_OPTION eOption) { m_eOption = eOption; }

private:
	const _tchar*	m_pBulletTag;
	_float			m_fSpeed;
	_vec3			m_vScale;
	SPREAD_OPTION	m_eOption;

	_int			m_iDegree;

private:
	_int Spread_X(const _float& fTimeDelta);
	_int Spread_Plus(const _float& fTimeDelta);
	_int Spread_Circle(const _float& fTimeDelta);
	_int Spread_Tornado(const _float& fTimeDelta);
	_int Spread_Look(const _float& fTimeDelta);

public:
	static CSpreadShot* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

