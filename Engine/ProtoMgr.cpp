#include "stdafx.h"
#include "ProtoMgr.h"

#include "Export_Function.h"

IMPLEMENT_SINGLETON(CProtoMgr)

CProtoMgr::CProtoMgr(void)
{
}

CProtoMgr::~CProtoMgr(void)
{
	Free();
}

HRESULT CProtoMgr::Ready_Proto(const _tchar * pProtoTag, CComponent * pComponent)
{
	CComponent*		pPrototype = Find_Proto(pProtoTag);

	if (nullptr != pPrototype || nullptr == pComponent)
		return E_FAIL;

	m_uMapProto.insert({ pProtoTag, pComponent });

	return S_OK;
}

CComponent* CProtoMgr::Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject)
{
	CComponent*		pPrototype = Find_Proto(pProtoTag);
	NULL_CHECK_RETURN(pPrototype, nullptr);

	CComponent* pClone = pPrototype->Clone();
	pClone->SetOwner(pGameObject);

	return pClone;
}

CComponent * CProtoMgr::Clone_Proto(const _tchar * pProtoTag, CGameObject* pGameObject, CBlackBoard* pBlackBoard)
{
	
	CComponent* pClone = Clone_Proto(pProtoTag, pGameObject);
	dynamic_cast<CBehavior*>(pClone)->m_pBlackBoard = pBlackBoard;
	return pClone;
}

CComponent * CProtoMgr::Clone_Proto(const _tchar * pProtoTag, const _tchar* colliderName, CGameObject* pGameObject, COLGROUP eColGroup, const _vec3& boundSize)
{
	CComponent* pClone = Clone_Proto(pProtoTag, pGameObject);
	CCollider* pCollider = dynamic_cast<CCollider*>(pClone);

	pGameObject->Add_Colldier_Info(colliderName, eColGroup);

	if (eColGroup > COL_STATIC_END)
		Engine::Add_Collider(eColGroup, pCollider); // 콜리젼 매니저에 넣어주는 함수

	pCollider->Set_BoundingBox(boundSize);
	return pCollider;
}

CComponent * CProtoMgr::Clone_Proto(const _tchar * pProtoTag, CGameObject * pGameObject, const _int& particleNums, const _vec3& origin, const _vec3 & boundSize)
{
	CComponent* pClone = Clone_Proto(pProtoTag, pGameObject);

	CParticleSystem* pParticle = dynamic_cast<CParticleSystem*>(pClone);

	pParticle->SetOffset(origin);
	pParticle->SetBoundingSize(boundSize);
	pParticle->SetNumParticle(particleNums);

	return pParticle;
}



CComponent * CProtoMgr::Find_Proto(const _tchar * pProtoTag)
{
	auto	iter = find_if(m_uMapProto.begin(), m_uMapProto.end(), CTag_Finder(pProtoTag));

	if (iter == m_uMapProto.end())
		return nullptr;

	return iter->second;
}

void CProtoMgr::Free(void)
{
	for_each(m_uMapProto.begin(), m_uMapProto.end(), CDeleteMap());
	m_uMapProto.clear();
}
