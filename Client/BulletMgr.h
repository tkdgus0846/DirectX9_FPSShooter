#pragma once
#include "Base.h"
#include "Export_Function.h"

class CBulletPool : public CBase
{
	friend class CBulletMgr;

private:
	CBulletPool();
	~CBulletPool();

	class CBullet* CBulletPool::Pop(const _tchar* name, LPDIRECT3DDEVICE9 pDevice, const _vec3 & vPos, const _vec3 & vDir, const _vec3& vScale = { 1.f,1.f,1.f }, bool bIsEnemyBullet = false, const _float& fSpeed = -1.0f);

	void		Push(CBullet* pObj);

	list<CBullet*>		m_BulletPool;
	int				m_iCreateCnt = 0;

	virtual void Free(void) override;
	static CBulletPool* Create();

};

// 총알 오브젝트 풀 매니저
class CBulletMgr : public CBase
{
	DECLARE_SINGLETON(CBulletMgr)
private:
	explicit CBulletMgr();
	virtual ~CBulletMgr();

public:

	void Reserve(LPDIRECT3DDEVICE9 pDevice, _uint cnt, const _tchar* name);

	class CBullet* CBulletMgr::Pop(const _tchar* name, LPDIRECT3DDEVICE9 pDevice, const _vec3& vPos, const _vec3& vDir, const _vec3& vScale = { 1.f,1.f,1.f }, bool bIsEnemyBullet = false, const _float& fSpeed = -1.0f);
	
	void		Push(const _tchar* name, CBullet* pBullet);

	virtual void Free(void) override;

private:
	unordered_map<const _tchar*, CBulletPool*> m_BulletPool;
};


