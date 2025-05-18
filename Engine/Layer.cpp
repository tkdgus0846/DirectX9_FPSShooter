#include "stdafx.h"
#include "Layer.h"

#include "Export_Function.h"
#include "GameObject.h"
#include "Component.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
}

CComponent * CLayer::Get_Component(const _tchar* pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	auto iter = find_if(m_uMapObject.begin(), m_uMapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_uMapObject.end())
		return nullptr;
	
	return iter->second->Get_Component(pComponentTag, eID);
}

HRESULT CLayer::Add_GameObject(const _tchar * pObjTag, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;
	if (pGameObject == nullptr) return S_OK;

	m_uMapObject.insert({ pObjTag, pGameObject });

	return S_OK;
}

HRESULT CLayer::Remove_GameObject(CGameObject* obj)
{
	for (auto it = m_uMapObject.begin(); it != m_uMapObject.end(); it++)
	{
		if ((it->second) == obj)
		{
			m_uMapObject.erase(it);
			break;
		}
	}

	return S_OK;
}

CGameObject* CLayer::Get_GameObject(const _tchar* pObjTag)
{
	auto iter = m_uMapObject.find(pObjTag);
	if (iter == m_uMapObject.end()) return nullptr;

	return iter->second;
}

void CLayer::Get_GameObject_ALL(vector<CGameObject*>* pVec)
{
	if (m_uMapObject.empty()) return;
	auto iter = m_uMapObject.begin();
	for (; iter != m_uMapObject.end(); iter++)
	{
		pVec->push_back(iter->second);
	}
}

HRESULT CLayer::Ready_Layer(void)
{
	return S_OK;
}


// 정적인 레이어에서 불렸다면?
_int CLayer::Update_Layer(const _float & fTimeDelta)
{
	for (auto iter = m_uMapObject.begin(); iter != m_uMapObject.end(); )
	{
		_int result = iter->second->Update_GameObject(fTimeDelta);

		if (result == OBJ_DEAD)
		{		
			Engine::Remove_Collider(iter->second);
			Safe_Release(iter->second);
		}

		if (result != OBJ_NOEVENT) 
			iter = m_uMapObject.erase(iter);
		else 
			++iter; 
	}
	return 0;
}

void CLayer::LateUpdate_Layer(void)
{
	for (auto& iter : m_uMapObject)
		iter.second->LateUpdate_GameObject();
}


CLayer * CLayer::Create(void)
{
	CLayer *	pInstance = new CLayer;

	if (FAILED(pInstance->Ready_Layer()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Layer Create Failed");
	}

	return pInstance;
}

void CLayer::Free(void)
{
	for (auto it : m_uMapObject)
	{
		Engine::Remove_Collider(it.second);
		Safe_Release(it.second);
	}
	m_uMapObject.clear();
}
