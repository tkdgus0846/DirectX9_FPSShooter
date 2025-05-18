#pragma once
#include "Behavior.h"

class CBoolCheck : public CBehavior
{
private:
	explicit CBoolCheck(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CBoolCheck(const CBoolCheck& rhs);
	virtual ~CBoolCheck();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {}

	void Bind_Typename(const _tchar* pTypename) { m_pTypename = pTypename; }

private:
	const _tchar* m_pTypename;

public:
	static CBoolCheck* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

