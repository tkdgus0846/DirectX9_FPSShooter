#pragma once

#include "Component.h"
#include "Include.h"

BEGIN(Engine)

class  CTransform : public CComponent
{
public:
	// 지상인지	  공중인지
	enum MOVETYPE { LANDOBJECT, AIRCRAFT, MOVE_END };

private:
	explicit CTransform(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform();

public:
	void Set_MoveType(MOVETYPE eType = LANDOBJECT) { m_eMoveType = eType; }
	MOVETYPE Get_MoveType() const { return m_eMoveType; }

	const _matrix*		Get_WorldMatrixPointer() { return &m_matWorld; }
	void				Get_Info(INFO eType, _vec3* pInfo)
	{
		*pInfo = m_vInfo[eType];
	}
	const _vec3& Get_Scale()
	{
		return m_vScale;
	}

	void Set_Pos(const _float& x, const _float& y, const _float& z)
	{	
		m_vInfo[INFO_POS] = { x,y,z };
	}
	void Set_Pos(const _vec3& pos)
	{
		m_vInfo[INFO_POS] = pos;
	}

	void Set_Scale(const _vec3& scale) { m_vScale = scale; }
	void Set_BillMode(_bool bSwitch) { m_bIsBill = bSwitch; }
	_bool Get_BillMode() { return m_bIsBill; }

	void Rot_Reset()
	{
		m_vInfo[0] = { 1.f,0.f,0.f };
		m_vInfo[1] = { 0.f,1.f,0.f };
		m_vInfo[2] = { 0.f,0.f,1.f };
	}

	// 제대로 돌아가는지 확인 해봐야함.
	void Set_Dir(const _vec3& dir);

	// 해당 위치를 바라보게끔 만드는 함수.
	void Set_Target(const _vec3& targetPos);

	// 오브젝트의 위치쪽으로 look이 돌아가게 만드는 함수
	void Rot_To_TargetPos(const _vec3& vTargetPos, const _float& fTimeDelta);

	// 오른쪽 벡터로 움직이는거
	void	Move_Strafe(const _float& fUnits, const _float& fTimeDelta);// Move-Right

	// 업 벡터로 움직이는거
	void	Move_Fly(const _float& fUnits, const _float& fTimeDelta);	// Move-Up

	// 룩 벡터로 움직이는거
	void	Move_Walk(const _float& fUnits, const _float& fTimeDelta);  // Move-Look
	void	Move_Velocity(const _vec3& velocity);

	// 임의의 벡터로 움직이는 거
	void CTransform::Move_WalkWithVec(_vec3 vDir, const _float & fUnits, const _float& fTimeDelta);

	void	Rot_Pitch(const _float& fAngle, const _float& fTimeDelta);// Rot-Right
	void	Rot_Yaw(const _float& fAngle, const _float& fTimeDelta);  // Rot-Up
	void	Rot_Roll(const _float& fAngle, const _float& fTimeDelta); // Rot-Look
	// 빌보드모드 일때만 적용됨.
	void	Rot_Bill(const _float& fAngle);

	// 룩 벡터 반전.
	void	Reverse_Dir();

	void	Set_Billboard(_matrix* _matView)
	{
		D3DXMatrixIdentity(&m_matBill);
		m_matBill._11 = _matView->_11;
		m_matBill._13 = _matView->_13;
		m_matBill._31 = _matView->_31;
		m_matBill._33 = _matView->_33;

		D3DXMatrixInverse(&m_matBill, 0, &m_matBill);
	}

	void	Chase_Target(const _vec3* pTargetPos, const _float& fSpeed, const _float& fTimeDelta);

	_bool	WriteTransformFile(HANDLE hFile, DWORD& dwByte);
	_bool	ReadTransformFile(HANDLE hFile, DWORD& dwByte);

	_bool	WriteTransformFileForMonster(HANDLE hFile, DWORD& dwByte);
	_bool	ReadTransformFileForMonster(HANDLE hFile, DWORD& dwByte);

public:
	HRESULT		Ready_Transform(void);
	virtual		_int	Update_Component(const _float& fTimeDelta);
	virtual		void	LateUpdate_Component(void);

private:
	MOVETYPE	m_eMoveType;
	_bool		m_bIsBill;
	
public:
	_vec3		m_vInfo[INFO_END];
	_vec3		m_vScale;

	_matrix		m_matWorld;
	_matrix		m_matBill;
	_matrix		m_matRotBill;

public:
	static CTransform*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent*		Clone(void);

private:
	_matrix*	Compute_Lookattarget(const _vec3* pTargetPos);
	virtual void	Free(void) override;

};
END