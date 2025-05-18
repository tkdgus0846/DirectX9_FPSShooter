#pragma once

#include "Include.h"
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CCollider;
END

class CWall : public Engine::CGameObject
{
	friend class CRoom;
public:
	explicit CWall(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CWall();


	virtual void OnCollisionEnter(const class Collision* collision) override;
	virtual void OnCollisionStay(const class Collision* collision) override;
	virtual void OnCollisionExit(const class Collision* collision) override;

public:
	HRESULT Ready_GameObject(STAGEINFO stageInfo);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	Engine::CCollider*	m_pCollider;
	Engine::CTexture*	m_pTextureCom;
	const _tchar*		m_WallTextureName;

	virtual HRESULT Add_Component() override;

public:
	static CWall*		Create(LPDIRECT3DDEVICE9 pGraphicDev, STAGEINFO stageInfo);

private:
	virtual void Free(void) override;
};