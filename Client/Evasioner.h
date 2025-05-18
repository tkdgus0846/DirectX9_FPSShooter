#pragma once
#include "Enemy.h"

BEGIN(Engine)
class CAnimation;
END

class CEvasioner : public CEnemy
{
private:
	explicit CEvasioner(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEvasioner();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionStay(const class Collision* collision);
	virtual void OnCollisionExit(const class Collision* collision);

	void		 SetInHole() { m_bInHole = true; }

private:
	CAnimation* m_pAnimation;
	_bool		m_bInHole;

private:
	virtual HRESULT Add_Component() override;

public:
	static CEvasioner*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Evasioner"; }

private:
	virtual void Free(void) override;
};

