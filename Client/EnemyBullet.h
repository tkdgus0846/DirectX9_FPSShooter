#pragma once
#include "Bullet.h"
class CEnemyBullet : public CBullet
{
	friend class CBulletPool;
	friend class CBulletMgr;
private:
	explicit CEnemyBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEnemyBullet();

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
	static CEnemyBullet*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

