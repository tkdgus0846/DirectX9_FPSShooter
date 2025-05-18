#pragma once
#include "Bullet.h"

class CSwordBullet : public CBullet
{
	friend class CBulletPool;
	friend class CBulletMgr;
private:
	explicit CSwordBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSwordBullet();

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

public:
	virtual void Pop_Initialize();

protected:
	virtual void Free(void) override;

private:
	// 총알은 매니저를 통해서 생성할것.
	static CSwordBullet*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

