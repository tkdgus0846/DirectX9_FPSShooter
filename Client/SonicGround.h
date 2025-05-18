#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CRcTex;
END

class CSonicGround : public CGameObject
{
private:
	explicit CSonicGround(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSonicGround();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;
	void			Game_Start();
	void			Game_End();
	void			Set_GameSpeed(_float speed)
	{
		m_fGameSpeed = speed;
	}
	

private:
	virtual HRESULT Add_Component() override;

	_matrix			m_ViewMat;
	_matrix			m_Projmat;
	CRcTex*			m_RcTex;

	_float			m_UValue;
	_vec3			m_vMaxScale;
	_bool			m_bGameStart;

	_float			m_fGameSpeed;

public:
	static CSonicGround*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	
};

