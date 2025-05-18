#pragma once
#include "Bullet.h"

class CSonicBird : public CBullet
{
private:
	explicit CSonicBird(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSonicBird();

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

public:
	virtual void SetDead(_bool bDead = true) override;

private:
	virtual HRESULT Add_Component() override;

public:
	static CSonicBird*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& pos);
	static CSonicBird*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
private:
	_matrix					m_ViewMat;
	_matrix					m_Projmat;
};

