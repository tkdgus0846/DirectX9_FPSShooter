#pragma once
#include "Component.h"

BEGIN(Engine)

class CCollider : public CComponent
{
	friend class CCollisionMgr;

protected:
	explicit CCollider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCollider(const CCollider& rhs);
	virtual ~CCollider();

private:
	// 감지 영역
	BoundingBox*		m_pBoundingBox;
	// 사각형 렌더링
	LPD3DXMESH			m_pMesh;
	// 현재 충돌 중인 콜리젼들을 체크한다.
	unordered_map<CCollider*, Collision>	m_CollisionList;

	_bool				m_bEnabled;
	_bool				m_bIsRender;
	_bool				m_bRenderByOwnerPos;

	_vec3				m_vCenterPos;
	_vec3				m_VOriginCenterPos;

	// 콜라이더 이름
	const _tchar*		m_Name;

	// 아래 두개 텍스쳐는 디버깅 용도로 넣었음. 나중에 지울거임.
	LPDIRECT3DBASETEXTURE9			m_GreenTexture;
	LPDIRECT3DBASETEXTURE9			m_RedTexture;

	
public:
	HRESULT			Ready_Collider();
	virtual _int	Update_Component(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Component() override;
	virtual void	Render_Component() override;

public:
	unordered_map<CCollider*, Collision>& Get_CollisionList() { return m_CollisionList; }
	void Get_Point(_vec3* MinPoint, _vec3* MaxPoint)
	{
		*MinPoint = m_pBoundingBox->_min;
		*MaxPoint = m_pBoundingBox->_max;
	}
	bool Intersect(const _vec3& point) { return m_pBoundingBox->Intersect(point); }
	_vec3 Get_BoundCenter() { return m_pBoundingBox->Get_Center(); }
	_vec3 Get_BoundSize() { return m_pBoundingBox->Get_Size();}

	void OnCollisionEnter(const Collision* collision);
	void OnCollisionStay(const Collision* collision);
	void OnCollisionExit(const Collision* collision);

	void Set_Enable(_bool bEnabled) { m_bEnabled = bEnabled; }
	_bool Get_Enable() const { return m_bEnabled; }
	bool Toggle_IsRender() 
	{
		return m_bIsRender = (m_bIsRender == true) ? false : true;
	}
	void Set_IsRender(_bool bIsRender) { m_bIsRender = bIsRender; }

	void Set_BoundingBox(const _vec3& vSize = {2.f, 2.f, 2.f});
	void Set_BoundingBox(const _vec3& vSize, const _vec3& vCenterPos);
	// 에디터에서만 사용해야됨.
	BoundingBox*	Get_BoundingBox() { return m_pBoundingBox; }
	const _tchar*	Get_Name() { return m_Name; }

public:
	static CCollider* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual CComponent * Clone(void) override;

private:
	virtual void Free(void) override;
};

END