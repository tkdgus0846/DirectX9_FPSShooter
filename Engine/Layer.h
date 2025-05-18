#pragma once

#include "Base.h"

BEGIN(Engine)

class CGameObject;
class CComponent;

class  CLayer : public CBase
{
private:
	explicit CLayer();
	virtual ~CLayer();

public:
	CComponent*			Get_Component(const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);

public:
	HRESULT				Add_GameObject(const _tchar* pObjTag, CGameObject* pGameObject);
	HRESULT				Remove_GameObject(CGameObject* obj);

	CGameObject*		Get_GameObject(const _tchar* pObjTag);
	void				Get_GameObject_ALL(vector<CGameObject*>* pVec);

	HRESULT				Ready_Layer(void);
	_int				Update_Layer(const _float& fTimeDelta);
	void				LateUpdate_Layer(void);
	_int				Get_ObjectSize() { return m_uMapObject.size(); }

private:
	// 이름 중복이 문제였으니까 이렇게하면 이름중복 삽입 문제는 없지만 고유 식별값이 없어서 찾아오진 못한다.
	multimap<const _tchar*, CGameObject*>			m_uMapObject;

public:
	static CLayer*		Create(void);

private:
	virtual void Free(void);

};

END