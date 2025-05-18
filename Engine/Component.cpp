#include "stdafx.h"
#include "Component.h"
#include "GameObject.h"


CComponent::CComponent() 
	: m_pGraphicDev(nullptr)
	, m_pGameObject(nullptr)
	, m_bClone(false)
{
}

CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_pGameObject(nullptr)
	, m_bClone(false)
{
	m_pGraphicDev->AddRef();
}

CComponent::CComponent(const CComponent & rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev)
	, m_pGameObject(rhs.m_pGameObject)
	, m_bClone(true)
{
	m_RenderOrder = 0;
	m_pGraphicDev->AddRef();
}


CComponent::~CComponent()
{
}

Engine::CComponent* Engine::CComponent::Get_Component(const _tchar* pComponentTag, COMPONENTID eID)
{
	CComponent*		pComponent = m_pGameObject->Get_Component(pComponentTag, eID);
	NULL_CHECK_RETURN(pComponent, nullptr);

	return pComponent;
}

void CComponent::SetOwner(CGameObject * gameObject)
{
	m_pGameObject = gameObject;
}

void Engine::CComponent::Free(void)
{
	Safe_Release(m_pGraphicDev);
}

// Composite

CComposite::CComposite()
	:CComponent()
{
}

CComposite::CComposite(LPDIRECT3DDEVICE9 pGraphicDev)
	: CComponent(pGraphicDev)
	, m_iterCurComponent(m_VecComponents[ID_UPDATE].begin())
	, m_iterPreComponent(m_VecComponents[ID_UPDATE].begin())
{
}

CComposite::CComposite(const CComposite & rhs)
	: CComponent(rhs)
	, m_iterCurComponent(rhs.m_iterCurComponent)
	, m_iterPreComponent(rhs.m_iterPreComponent)
{
}

CComposite::~CComposite()
{
}

HRESULT CComposite::Ready_Composite(void)
{
	m_iterCurComponent = m_VecComponents[ID_UPDATE].begin();
	m_iterPreComponent = m_VecComponents[ID_UPDATE].begin();

	return S_OK;
}

_int CComposite::Update_Component(const _float & fTimeDelta)
{
	for (auto& iter : m_VecComponents[ID_UPDATE])
	{
		iter.pComponent->Update_Component(fTimeDelta);
	}
	return S_OK;
}

void CComposite::LateUpdate_Component(void)
{
	for (auto& iter : m_VecComponents[ID_UPDATE])
	{
		iter.pComponent->LateUpdate_Component();
	}
}

void CComposite::Render_Component(void)
{
	/*for (auto& iter : m_VecComponents[ID_UPDATE])
	{
		iter.pComponent->Render_Component();
	}*/
}

HRESULT CComposite::Add_Component(COMPONENTID eID, 
									const _tchar * pComponentTag, 
									CComponent * pComponent)
{
	if (nullptr == pComponent)
		return E_FAIL;

	m_VecComponents[eID].push_back({ pComponentTag, pComponent });

	return S_OK;
}

CComponent * CComposite::Get_Component(const _tchar * pComponentTag, COMPONENTID eID)
{
	auto iter = find_if(m_VecComponents[eID].begin(), m_VecComponents[eID].end(), [&](auto& Comp)->bool 
	{
		if (0 == lstrcmp(pComponentTag, Comp.pTag))
			return true;
		
		return false;
	});

	if(iter == m_VecComponents[eID].end())
		return nullptr;

	return iter->pComponent;
}


HRESULT CComposite::Remove_Component(const _tchar * pComponentTag)
{
	for (_uint i = 0; i < ID_END; ++i)
	{
		for (auto iter = m_VecComponents[i].begin(); iter != m_VecComponents[i].end(); ++iter)
		{
			if (0 == lstrcmp(pComponentTag, iter->pTag))
			{
				Safe_Release(iter->pComponent);
				m_VecComponents[i].erase(iter);

				return S_OK;
			}
		}
	}
	return E_FAIL;
}

void Engine::CComposite::Free(void)
{
	for (int i = 0; i < ID_END; i++)
	{
		for (auto& comp : m_VecComponents[i])
		{
			Safe_Release(comp.pComponent);
		}
	}

	__super::Free();
}