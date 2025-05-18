#pragma once
#include "Base.h"

BEGIN(Engine)

class CCollider;

class CCollisionMgr : public CBase
{
	DECLARE_SINGLETON(CCollisionMgr)

private:
	explicit CCollisionMgr();
	virtual ~CCollisionMgr();

public:
	// 실질적으로 콜리젼을 체크해주는 함수.
	void		Check_Collision(COLGROUP ID1, COLGROUP ID2);
	
	// 콜라이더들의 렌더를 꺼주는 함수.
	void		Toggle_ColliderRender();
	void		Change_ColGroup(CCollider* collider, COLGROUP changeID);
	_bool		GetIsRender() const { return m_bIsRender; }

	void		Add_Collider(COLGROUP eID, CCollider* pCollider);
	void		Add_Collider(CGameObject* gameObject);

	void		Remove_Collider(CCollider* collider, COLGROUP colID);
	void		Remove_Collider(CGameObject* gameObject);
	
	void		Set_StaticColliderList(list<CCollider*>* pStaticColliderList, _int iIndex);
	void		Clear_Static_ColliderList()
	{
		for (int i = 0; i < COL_STATIC_END; i++)
			m_StaticColliderList[i] = nullptr;
	}


private:
	list<CCollider*>* Get_ColliderList(COLGROUP colID);
	void		Find_Remove_Collider(CGameObject* gameObject, COLGROUP colID);
	bool		Collision_Box(CCollider* pSrc, CCollider* pDest, COL_DIR& colDir, BoundingBox& bound, _vec3& amountVec);
	_bool		Check_BoundingBox(CCollider * pSrc, CCollider * pDest, _float * pX, _float * pY, _float * pZ);

	
	
private:
	list<CCollider*>*	m_StaticColliderList [COL_STATIC_END]; // 룸에 있을 콜라이더들의 리스트
	list<CCollider*>	m_DynamicColliderList[COL_DYNAMIC_END - COL_STATIC_END - 1];
	_bool				m_bIsRender;

private:
	virtual void Free(void) override;
};

END