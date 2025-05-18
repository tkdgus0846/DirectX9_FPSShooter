#pragma once
#include "Behavior.h"

class CCutSceneCheck : public CBehavior
{
private:
	explicit CCutSceneCheck(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCutSceneCheck(const CCutSceneCheck& rhs);
	virtual ~CCutSceneCheck();

public:
	virtual HRESULT Ready_Behavior() override;
	virtual _int Update_Component(const _float & fTimeDelta) override;
	virtual void LateUpdate_Component(void) override {}
	virtual void Render_Component(void) override {}

	void Bind_Switch(const _tchar* pTypename) { m_pTypename = pTypename; }

private:
	const _tchar* m_pTypename;

public:
	static CCutSceneCheck* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free() override;
};

