#pragma once
#include "Base.h"
#include "Item.h"
#include "Export_Function.h"

class CItemPool : public CBase
{
	friend class CItemManager;

private:
	CItemPool();
	~CItemPool();

	CItem* CItemPool::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar* name, const _vec3 & vPos);

	void		Push(CItem* pObj);

	list<CItem*>		m_ItemPool;
	int				m_iCreateCnt = 0;

	virtual void Free(void) override;
	static CItemPool* Create();

};

class CItemManager : public CBase
{
	DECLARE_SINGLETON(CItemManager)
private:
	explicit CItemManager();
	virtual ~CItemManager();

public:
	void Reserve(LPDIRECT3DDEVICE9 pDevice, _uint cnt, const _tchar* name);

	CItem* CItemManager::Pop(LPDIRECT3DDEVICE9 pDevice, const _tchar* name, const _vec3 & vPos);

	void		Push(const _tchar* name, CItem* pItem);

	virtual void Free(void) override;

private:
	unordered_map<const _tchar*, CItemPool*> m_ItemPool;
};

