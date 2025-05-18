#pragma once
#include "MapObj.h"

class COnlyCollisionObj :
	public CMapObj
{
private:
	explicit COnlyCollisionObj(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~COnlyCollisionObj();

public:
	virtual HRESULT		Ready_GameObject(void);
	virtual _int		Update_GameObject(const _float& fTimeDelta);
	virtual void		LateUpdate_GameObject(void);
	virtual void		Render_GameObject(void);

public:
	static COnlyCollisionObj* Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, _vec3 ColSize);

	void	Set_ColSize(_vec3 ColSize) { m_vColSize = ColSize; }

	virtual void OnCollisionEnter(const class Collision* collsion);
	virtual void OnCollisionStay(const class Collision* collision);
	virtual void OnCollisionExit(const class Collision* collision);
private:
	// CGameObject을(를) 통해 상속됨
	virtual HRESULT Add_Component() override;

	_vec3		m_vColSize;
};

