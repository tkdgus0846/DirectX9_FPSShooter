#pragma once

#include "Base.h"
#include "Include.h"

BEGIN(Engine)

class CComponent : public CBase
{
	friend class CProtoMgr;
	friend class CComposite;

protected:
	explicit CComponent();
	explicit CComponent(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CComponent(const CComponent& rhs);
	virtual ~CComponent();

public:
	virtual			_int	Update_Component(const _float& fTimeDelta) { return 0; }
	virtual			void	LateUpdate_Component() {}
	virtual			void	Render_Component() {}

	CComponent*			Get_Component(const _tchar* pComponentTag, COMPONENTID eID);
	class CGameObject*	Get_GameObject() const { return m_pGameObject; }

protected:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	_bool				m_bClone;

public:
	class CGameObject*	m_pGameObject;
	_uint				m_RenderOrder;

public:
	virtual	CComponent*	Clone(void) PURE;
	virtual void		Free(void)override;

private:
	void SetOwner(class CGameObject* gameObject);
};

// 비해비어 트리에 우선순위를 정하기 위한 구조체
typedef struct PriComp
{
	const _tchar*	pTag;
	CComponent*		pComponent;
}PRICOMP;

class CComposite : public CComponent
{
protected:
	explicit CComposite();
	explicit CComposite(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CComposite(const CComposite& rhs);
	virtual ~CComposite();

public:
	virtual HRESULT		Ready_Composite(void);
	virtual _int		Update_Component(const _float& fTimeDelta);
	virtual void		LateUpdate_Component(void);
	virtual void		Render_Component(void);

public:
	HRESULT				Add_Component(COMPONENTID eID, 
										const _tchar* pComponentTag, 
										CComponent* pComponent);
	CComponent*			Get_Component(const _tchar* pComponentTag, COMPONENTID eID);
	HRESULT				Remove_Component(const _tchar* pComponentTag);
	virtual void		Free(void) override;

protected:
	vector<PRICOMP>			  m_VecComponents[ID_END];
	vector<PRICOMP>::iterator m_iterCurComponent;
	vector<PRICOMP>::iterator m_iterPreComponent;
};

END