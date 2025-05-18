#pragma once
#include "Bullet.h"

class CRootAttack : public CBullet
{
	friend class CBulletMgr;
	friend class CBulletPool;
private:
	explicit CRootAttack(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRootAttack();

public:
	virtual void SetDead(_bool bDead = true) override;

	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const Collision* collsion) override;
	virtual void OnCollisionStay(const Collision* collision) override;
	virtual void OnCollisionExit(const Collision* collision) override;

	virtual HRESULT Add_Component() override;

protected:
	virtual void Free(void) override;

private:
	// 총알은 매니저를 통해서 생성할것.
	static CRootAttack*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

