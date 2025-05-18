#pragma once
#include "Enemy.h"

BEGIN(Engine)
class CAnimation;
class CCollider;
END

class CSpeyeder : public CEnemy
{
private:
	explicit CSpeyeder(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSpeyeder();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionStay(const class Collision* collision);

private:
	CAnimation* m_pAnimation;
	CCollider* m_pColExplosion;

private:
	virtual HRESULT Add_Component() override;

public:
	static CSpeyeder*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Speyeder"; }

private:
	virtual void Free(void) override;
};

