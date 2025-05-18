#include "ItemManager.h"
#include "BulletItem.h"
#include "CoinItem.h"
#include "HeartItem.h"

IMPLEMENT_SINGLETON(CItemManager)

CItemPool::CItemPool()
{
}

CItemPool::~CItemPool()
{
}

void CItemPool::Push(CItem* pObj)
{
	if (nullptr == pObj)
		return;

	m_ItemPool.push_back(pObj);
}

CItem * CItemPool::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar * name, const _vec3 & vPos)
{
	CItem*		pItem = nullptr;

	if (m_ItemPool.empty())
	{
		if (name == L"BulletItem")
		{
			pItem = CBulletItem::Create(pDevice);
		}
		else if (name == L"CoinItem")
		{
			pItem = CCoinItem::Create(pDevice);
		}
		else if (name == L"HeartItem")
		{
			pItem = CHeartItem::Create(pDevice);
		}
		
		++m_iCreateCnt;
		
	}
	else
	{
		pItem = m_ItemPool.front();
		m_ItemPool.pop_front();
	}

	if (nullptr == pItem)
		return nullptr;

	(pItem)->Set_Pos(vPos);
	(pItem)->SetDead(false);
	(pItem)->SetAge();
	(pItem)->m_bDrop = false;
	return pItem;
}

CItemPool* CItemPool::Create()
{
	CItemPool*		pInstance = new CItemPool();
	return pInstance;
}

void CItemPool::Free(void)
{
	for_each(m_ItemPool.begin(), m_ItemPool.end(), CDeleteObj());
	m_ItemPool.clear();
}

//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

CItemManager::CItemManager()
{

}

CItemManager::~CItemManager()
{
	Free();
}

CItem * CItemManager::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar * name, const _vec3 & vPos)
{
	if (m_ItemPool[name] == nullptr)
	{
		m_ItemPool[name] = CItemPool::Create();
	}
	CItem*		pItem = m_ItemPool[name]->Pop(pDevice, name, vPos);
	if (pItem == nullptr)
		return nullptr;

	return pItem;
}


void CItemManager::Reserve(LPDIRECT3DDEVICE9 pDevice, _uint cnt, const _tchar* name)
{
	for (int i = 0; i < cnt; i++)
	{
		CItem* pItem = nullptr;
		if (name == L"BulletItem")
		{
			pItem = CBulletItem::Create(pDevice);
		}
		else if (name == L"CoinItem")
		{
			pItem = CCoinItem::Create(pDevice);
		}
		else if (name == L"HeartItem")
		{
			pItem = CHeartItem::Create(pDevice);
		}

		if (m_ItemPool[name] == nullptr)
		{
			m_ItemPool[name] = CItemPool::Create();
		}
		Push(name, pItem);
	}
}

void CItemManager::Push(const _tchar* name, CItem* pItem)
{
	if (m_ItemPool[name] == nullptr) return;

	m_ItemPool[name]->Push(pItem);
}

void CItemManager::Free(void)
{
	for_each(m_ItemPool.begin(), m_ItemPool.end(), CDeleteMap());
	m_ItemPool.clear();
}
