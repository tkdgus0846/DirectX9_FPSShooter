#pragma once
#include "Bullet.h"

BEGIN(Engine)
class CCollider;
class CTexture;
class CRcTex;
END

class CRedLaserBullet : public CBullet
{
	friend class CBulletPool;
	friend class CBulletMgr;

private:
	explicit CRedLaserBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRedLaserBullet();

public:
	virtual void SetDead(_bool bDead = true) override;

	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const Collision* collsion) override;
	virtual void OnCollisionStay(const Collision* collision) override;
	virtual void OnCollisionExit(const Collision* collision) override;

	void AttackPoint_On() { m_bPoint = true; }
	virtual HRESULT Add_Component() override;

private:
	_bool		m_bShot;
	_bool		m_bPoint;
	_vec3		m_vDir;
	CTexture*	m_pTextureCom;
	CRcTex*		m_pRcTex;

protected:
	virtual void Free(void) override;

private:
	// 총알은 매니저를 통해서 생성할것.
	static CRedLaserBullet*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

