#pragma once
#include "GameObject.h"

class CPortal : public CGameObject
{
protected:
	explicit CPortal(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPortal();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual HRESULT Add_Component() override;
	virtual void OnCollisionEnter(const class Collision* collsion);

	static CPortal*		Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static const _tchar* Tag() { return L"Portal"; }


	virtual void OnCollisionStay(const class Collision* collision) override;

protected:
	virtual void Free(void) override;
};

