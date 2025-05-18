#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CAnimation;
END

class CSonic : public CGameObject
{
private:
	explicit CSonic(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSonic();

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	void		Key_Input(const _float& fTimeDelta);
	void		Jump(const _float& fTimeDelta);

public:
	void		Set_Ground(CGameObject* obj);
	void		Set_UI(CGameObject* obj);
	_bool		Get_FirstJump() { return m_bFirstJump; }


	virtual void OnCollisionStay(const class Collision* collision) override;

private:
	virtual HRESULT Add_Component() override;

public:
	static CSonic*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	CAnimation*				m_pAnimation;
	class CSonicGround*		m_pGround;
	class CSonicUI*			m_pUI;

	_matrix					m_ViewMat;
	_matrix					m_Projmat;
	_float					m_fForce;

	_float					m_fJumpTime;
	const _float			m_fMaxJumpTime;
	_float					m_fPressedTime;

	_bool					m_bJumped;
	_bool					m_bFirstJump;
};

