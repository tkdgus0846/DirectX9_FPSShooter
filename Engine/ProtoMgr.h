#pragma once

#include "Include.h"
#include "Base.h"

BEGIN(Engine)

class  CProtoMgr : public CBase
{
	DECLARE_SINGLETON(CProtoMgr)

private:
	explicit CProtoMgr(void);
	virtual ~CProtoMgr(void);

public:
	HRESULT		Ready_Proto(const _tchar* pProtoTag, class CComponent* pComponent);
	
	// 기본 클론
	class CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject);

	// AI 클론용
	class CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject, class CBlackBoard* pBlackBoard);

	// Collider 클론용
	class CComponent*	Clone_Proto(const _tchar * pProtoTag, const _tchar* colliderName, class CGameObject* pGameObject, COLGROUP eColGroup, const _vec3& boundSize = {2.f,2.f,2.f});

	// Particle 클론용
	class CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject, const _int& particleNums, const _vec3& origin, const _vec3& boundSize = { 2.f,2.f,2.f });

public:
	const unordered_map<const _tchar*, class CComponent*>& Get_ProtoMap() const { return m_uMapProto; }
	
private:
	class CComponent*	Find_Proto(const _tchar* pProtoTag);

private:
	unordered_map<const _tchar*, class CComponent*>			m_uMapProto;

private:
	virtual void Free(void);
};

END