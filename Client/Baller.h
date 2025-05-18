#pragma once
#include "Enemy.h"

class CBaller : public CEnemy
{
private:
	explicit CBaller(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CBaller();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void SetDead(_bool bDead = true) final;

private:
	_float m_fTime;

private:
	virtual HRESULT Add_Component() override;

public:
	static CBaller*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Baller"; }
private:
	virtual void Free(void) override;
};