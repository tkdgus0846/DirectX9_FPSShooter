#pragma once
#include "Enemy.h"

class CLizard : public CEnemy
{
private:
	explicit CLizard(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLizard();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	_bool m_bIsDamaged;
	_bool m_bIsJump;

private:
	virtual HRESULT Add_Component() override;

public:
	static CLizard*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Lizard"; }

private:
	virtual void Free(void) override;
};

