#include "stdafx.h"
#include "CollisionMgr.h"
#include "Collider.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr()
{
	m_bIsRender = false;

	for (int i = 0; i < COL_STATIC_END; i++)
		m_StaticColliderList[i] = nullptr;
}


CCollisionMgr::~CCollisionMgr()
{
	Free();
}

void CCollisionMgr::Check_Collision(COLGROUP ID1, COLGROUP ID2)
{

	if (Get_ColliderList(ID1) == nullptr) return;
	if (Get_ColliderList(ID2) == nullptr) return;
	
	if (Get_ColliderList(ID1)->empty())
		return;
	if (Get_ColliderList(ID2)->empty())
		return;

	for (auto iterID1 = Get_ColliderList(ID1)->begin(); iterID1 != Get_ColliderList(ID1)->end(); iterID1++)
	{
		if ((*iterID1)->m_bEnabled == false) continue;

		for (auto iterID2 = Get_ColliderList(ID2)->begin(); iterID2 != Get_ColliderList(ID2)->end(); iterID2++)
		{
			if ((*iterID2)->m_bEnabled == false) continue;
			if (ID1 == ID2 && iterID1 == iterID2) continue;

			CCollider* collider1 = *iterID1;
			CCollider* collider2 = *iterID2;

			if (collider1 == nullptr || collider2 == nullptr) break;

			if (collider1->m_pBoundingBox == nullptr || collider2->m_pBoundingBox == nullptr) break;
			
			auto* colliderList1 = &collider1->m_CollisionList;
			auto* colliderList2 = &collider2->m_CollisionList;
			auto findCollider = colliderList1->find(collider2);
			
			COL_DIR colDir;
			Collision collision1;
			Collision collision2;

			// 충돌했다면
			if (Collision_Box(collider1, collider2, collision1.CollisionDir, collision1.intersectBox, collision1.amountVec))
			{
				collision2 = collision1;
				collision2.CollisionDir = (COL_DIR)((int)collision2.CollisionDir * -1);

				collision1.MyCollider = collider1;
				collision1.OtherCollider = collider2;
				collision1.OtherGameObject = collider2->Get_GameObject();

				collision2.MyCollider = collider2;
				collision2.OtherCollider = collider1;
				collision2.OtherGameObject = collider1->Get_GameObject();

				// 둘이 충돌하고 있지 않았으면
				if (findCollider == colliderList1->end())
				{
					collider1->OnCollisionEnter(&collision1);
					collider1->OnCollisionStay(&collision1);

					collider2->OnCollisionEnter(&collision2);
					collider2->OnCollisionStay(&collision2);
				}
				// 둘이 충돌하고 있었으면
				else
				{
					collider1->OnCollisionStay(&collision1);
					collider2->OnCollisionStay(&collision2);
				}

				(*colliderList1)[collider2] = collision1;
				(*colliderList2)[collider1] = collision2;

			}
			// 충돌 하지 않았다면
			else 
			{
				if (colliderList1->empty()) continue;
				if (colliderList2->empty()) continue;

				if (findCollider != colliderList1->end())
				{
					auto findCollider2 = colliderList2->find(collider1);

					if (findCollider2 == colliderList2->end()) continue;

					collider1->OnCollisionExit(&findCollider->second);
					collider2->OnCollisionExit(&findCollider2->second);

					colliderList1->erase(collider2);
					colliderList2->erase(collider1);
				}
			}
		}
	}
}

void CCollisionMgr::Add_Collider(COLGROUP eID, CCollider * pCollider)
{
	if (COL_DYNAMIC_END <= eID || nullptr == pCollider)
		return;
	Get_ColliderList(eID)->push_back(pCollider);

	if (m_bIsRender != pCollider->m_bIsRender)
		m_bIsRender = pCollider->m_bIsRender;
}

void CCollisionMgr::Add_Collider(CGameObject* gameObject)
{
	vector<COLGROUP> colGroupVec = gameObject->Get_ColGroupVec();
	vector<const _tchar*> colNameVec = gameObject->Get_ColNameVec();

	for (int i = 0; i < colGroupVec.size(); i++)
	{
		Add_Collider(colGroupVec[i], dynamic_cast<CCollider*>(gameObject->Get_Component(colNameVec[i], ID_ALL)));
	}
}

void CCollisionMgr::Change_ColGroup(CCollider* collider, COLGROUP changeID)
{
	list<CCollider*>::iterator iter;
	_bool found = false;
	for (int i = COL_STATIC_END+1; i < COL_DYNAMIC_END; i++)
	{
		for (iter = Get_ColliderList((COLGROUP)i)->begin(); iter != Get_ColliderList((COLGROUP)i)->end(); ++iter)
		{
			if (*iter == collider)
			{
				Get_ColliderList((COLGROUP)i)->erase(iter);
				found = true;
				break;
			}
		}
		if (found == true) break;
	}
	
	if (found == false) return;

	
	Get_ColliderList(changeID)->push_front(collider);
}

void CCollisionMgr::Remove_Collider(CCollider* collider, COLGROUP colID)
{
	for (auto it = Get_ColliderList(colID)->begin(); it != Get_ColliderList(colID)->end(); it++)
	{
		if (*it == collider)
		{
			Get_ColliderList(colID)->erase(it);
			break;
		}
	}
}

void Engine::CCollisionMgr::Set_StaticColliderList(list<CCollider*>* pStaticColliderList, _int iIndex)
{
	m_StaticColliderList[iIndex] = pStaticColliderList;
}

list<CCollider*>* CCollisionMgr::Get_ColliderList(COLGROUP colID)
{
	if (colID <= COL_STATIC_END)
	{
		if (m_StaticColliderList[colID] == nullptr) return nullptr;

		return m_StaticColliderList[colID];
	}
	else if (colID < COL_DYNAMIC_END)
	{
		return &m_DynamicColliderList[colID - COL_STATIC_END - 1];
	}
}

void Engine::CCollisionMgr::Find_Remove_Collider(CGameObject* gameObject, COLGROUP colID)
{
	// 콜리전 매니져에 들어와있는 콜라이더들을 싹다 돌면서 그놈의 게임오브젝트 주소와 매개변수로 넣은 게임오브젝트 주소가 같으면, 자기를 콜리젼매니저에서 빼버리고 자기랑 충돌하고있던 놈의 콜리젼리스트에서도 빠지게 함.

	//for (auto it = Get_ColliderList(colID)->begin(); it != Get_ColliderList(colID)->end(); )
	//{
	//	if ((*it)->Get_GameObject() == gameObject)
	//	{
	//		// 나의 콜리젼리스트를 돌면서 충돌한놈의 목록을 체크한다.
	//		for (auto& iter : (*it)->Get_CollisionList())
	//		{
	//			// 상대방의 콜리젼 리스트에서 제거해주는 거임 나의 콜라이더를
	//			iter.first->m_CollisionList.erase(*it);
	//		}
	//		it = Get_ColliderList(colID)->erase(it);
	//	}
	//	else
	//	{
	//		++it;
	//	}
	//}

	if (Get_ColliderList(colID) == nullptr) return;

	for (auto it = Get_ColliderList(colID)->begin(); it != Get_ColliderList(colID)->end();)
	{
		if ((*it)->Get_GameObject() == gameObject)
		{
			it = Get_ColliderList(colID)->erase(it);
		}
		else
			it++;
	}
}

void Engine::CCollisionMgr::Remove_Collider(CGameObject* gameObject)
{
	for (int i = 0; i < COL_DYNAMIC_END; i++)
	{
		if (i == COL_STATIC_END) continue;
		Find_Remove_Collider(gameObject, (COLGROUP)i);
	}
}

void Engine::CCollisionMgr::Toggle_ColliderRender()
{
	m_bIsRender = (m_bIsRender == false) ? true : false;
	for (int i = 0; i < COL_DYNAMIC_END; i++)
	{
		if (i == COL_STATIC_END) continue;
		if (Get_ColliderList((COLGROUP)i) == nullptr) continue;

		for (auto col : *Get_ColliderList((COLGROUP)i))
			col->Set_IsRender(m_bIsRender);
	}	
}

bool CCollisionMgr::Collision_Box(CCollider* pSrc, CCollider* pDest, COL_DIR& colDir, BoundingBox& bound, _vec3& amountVec)
{
	_float fX, fY, fZ;
	if (Check_BoundingBox(pSrc, pDest, &fX, &fY, &fZ))
	{
		amountVec = { fX, fY, fZ };

		_vec3 srcVec = pSrc->Get_BoundCenter() - pSrc->Get_BoundSize() / 2.f;
		_vec3 dstVec = pDest->Get_BoundCenter() - pDest->Get_BoundSize() / 2.f;

		_vec3 minVec = (srcVec.Length() < dstVec.Length()) ? dstVec : srcVec;

		srcVec = pSrc->Get_BoundCenter() + pSrc->Get_BoundSize() / 2.f;
		dstVec = pDest->Get_BoundCenter() + pDest->Get_BoundSize() / 2.f;

		_vec3 maxVec = (srcVec.Length() < dstVec.Length()) ? srcVec : dstVec;
		
		bound._min = minVec;
		bound._max = maxVec;
		bound._offsetMin = { 0.f,0.f,0.f };
		bound._offsetMax = maxVec - minVec;

		// src 기준
		if (fX > fY)
		{
			if (fZ > fY) // 상하
			{
				if (pSrc->Get_BoundCenter().y < pDest->Get_BoundCenter().y)
				{
					// 상충돌
					colDir = DIR_UP;
					return true;
				}
				else
				{
					// 하충돌
					colDir = DIR_DOWN;
					return true;
				}
			}
			
			if (fY > fZ) // 전후
			{
				if (pSrc->Get_BoundCenter().z < pDest->Get_BoundCenter().z)
				{
					// 후충돌
					colDir = DIR_FRONT;
					return true;
				}
				else
				{
					// 전충돌
					colDir = DIR_BACK;
					return true;
				}
			}
		}
		else
		{
			if (fZ > fX) // 좌우
			{
				if (pSrc->Get_BoundCenter().x < pDest->Get_BoundCenter().x)
				{
					// 우충돌
					colDir = DIR_RIGHT;
					return true;
				}
				else
				{
					// 좌충돌
					colDir = DIR_LEFT;
					return true;
				}
			}
			if (fX > fZ) // 전후
			{
				if (pSrc->Get_BoundCenter().z < pDest->Get_BoundCenter().z)
				{
					// 후충돌
					colDir = DIR_FRONT;
					return true;
				}
				else
				{
					// 전충돌
					colDir = DIR_BACK;
					return true;
				}
			}
		}
	}
	return false;
}

_bool CCollisionMgr::Check_BoundingBox(CCollider * pSrc, CCollider * pDest, _float * pX, _float * pY, _float * pZ)
{
	float	fX = fabs(pDest->Get_BoundCenter().x - pSrc->Get_BoundCenter().x);
	float	fY = fabs(pDest->Get_BoundCenter().y - pSrc->Get_BoundCenter().y);
	float	fZ = fabs(pDest->Get_BoundCenter().z - pSrc->Get_BoundCenter().z);

	float	fRadiusX = (pDest->Get_BoundSize().x + pSrc->Get_BoundSize().x) * 0.5f;
	float	fRadiusY = (pDest->Get_BoundSize().y + pSrc->Get_BoundSize().y) * 0.5f;
	float	fRadiusZ = (pDest->Get_BoundSize().z + pSrc->Get_BoundSize().z) * 0.5f;

	if ((fRadiusX > fX) && (fRadiusY > fY) && (fRadiusZ > fZ))
	{
		*pX = fRadiusX - fX;
		*pY = fRadiusY - fY;
		*pZ = fRadiusZ - fZ;
		return true;
	}

	return false;
}

void CCollisionMgr::Free(void)
{
		
}
