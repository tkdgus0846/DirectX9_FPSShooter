#pragma once
#include "MapObj.h"

BEGIN(Engine)

class CRcTex;
class CTexture;

END

class CCheckPoint : public CMapObj
{
protected:
	explicit CCheckPoint(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CCheckPoint();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual HRESULT Add_Component() override;
	virtual void OnCollisionEnter(const class Collision* collsion);

	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"CheckPoint"; }

protected:
	virtual void Free(void) override;
};