#pragma once

#include "Component.h"
#include "Base.h"

BEGIN(Engine)

struct ComponentCmp 
{
	bool operator()(const pair<const _tchar*, CComponent*>* a, const pair<const _tchar*, CComponent*>* b) const
	{
		return a->second->m_RenderOrder < b->second->m_RenderOrder;
	}
};

struct OBJ_INFO
{
	LAYERID					layerID;
	const _tchar*			pObjTag;
	vector<COLGROUP>		colGroupVec;
	vector<const _tchar*>	colNameVec;
};

class  CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGameObject();

public:
	CComponent*			Get_Component(const _tchar* pComponentTag, COMPONENTID eID);
	_float				Get_ViewZ(void) { return m_fViewZ; }
	class CVIBuffer*	Get_VIBuffer();
	class CTexture*		Get_Texture();
	wstring				Get_TextureKey();
	// 순수 가상함수 왜냐하면 게임오브젝트에 컴포넌트가 추가되지 않을일은 없으니까
	virtual HRESULT		Add_Component() PURE;

	void				Remove_Texture(const _tchar* name, COMPONENTID componentID = ID_RENDER);
	void				Change_Texture(const _tchar* beforeName, const _tchar* afterName, COMPONENTID componentID = ID_RENDER);

	// 에디터에서만 사용해야됨.
	unordered_map<const _tchar*, CComponent*>* Get_ComponentMap() { return m_uMapComponent; }


public:
	virtual HRESULT		Ready_GameObject(void);
	virtual _int		Update_GameObject(const _float& fTimeDelta);
	virtual void		LateUpdate_GameObject(void);
	virtual void		Render_GameObject(void);

	virtual void OnCollisionEnter(const class Collision* collsion) {}
	virtual void OnCollisionStay(const class Collision* collision) {}
	virtual void OnCollisionExit(const class Collision* collision) {}

	void			Compute_ViewZ(const _vec3* pPos);

	void			Set_Pos(const _vec3& pos);
	void			Set_Dir(const _vec3& dir);

	virtual void	SetDead(_bool bDead = true) { m_bDead = bDead; }
	_bool			GetDead() const { 
		return m_bDead; }

	void			Add_Colldier_Info(const _tchar* colName, COLGROUP colGroup);
	void			Set_LayerID(LAYERID layerID);
	void			Set_ObjTag(const _tchar* pObjTag);

	LAYERID							Get_LayerID() { return m_ObjInfo.layerID; }
	const _tchar*					Get_ObjTag() { return m_ObjInfo.pObjTag; }
	vector<const _tchar*>			Get_ColNameVec() { return m_ObjInfo.colNameVec; }
	vector<COLGROUP>				Get_ColGroupVec() { return m_ObjInfo.colGroupVec; }
	OBJ_INFO						Get_ObjInfo() { return m_ObjInfo; }
	
	list<CGameObject*>* Get_Static_GameObject_List() { return &m_StaticObjectList; }
	_int				Get_Static_GameObject_Size() { return m_StaticObjectList.size(); }

	// 하위 객체가 죽었을때 처리해주기 위함이다.
	void			Remove_InOwnerObject();
	void			Set_Flag(_bool state = FALSE);

protected:
	// 에디터에서만 사용하세요.
	/*void			Remove_Render_Component(const _tchar* pComponentTag);*/
	// 에디터에서만 사용하세요.
	void			Add_Render_Component();

	// 게임 오브젝트가 게임오브젝트를 가지고있는 꼴의 정적 레이어 오브젝트들이라면, 이 함수를 호출하여야 한다. 동적 레이어 오브젝트면 굳이 부를 필요가 없다.
	void			Add_Static_GameObject(CGameObject* childObject) 
	{ 
		childObject->m_pOwnerObject = this;
		m_StaticObjectList.push_back(childObject); 
	}	
	
	

private:
	CComponent*			Find_Component(const _tchar* pComponentTag, COMPONENTID eID);
	
protected:
	unordered_map<const _tchar*, CComponent*>			m_uMapComponent[ID_END];	
	LPDIRECT3DDEVICE9		m_pGraphicDev;
	_float					m_fViewZ = 0.f;

	OBJ_INFO				m_ObjInfo;

	_float					m_fZGap;
	_bool					m_bReleaseFlag;
	
private:
	// 컴포넌트들의 렌더순서를 정해주는 벡터 컨테이너
	vector<pair<const _tchar*, CComponent*>> m_RenderComponent;
	_bool					m_bDead;

	// 만약 게임오브젝트가 게임 오브젝트를 가지고 있는 정적 그룹의 객체라면 리스트에 오브젝트들을 추가해줘야한다.
	list<CGameObject*>		m_StaticObjectList;
	CGameObject*			m_pOwnerObject;

public:
	class CTransform*		m_pTransform;

protected:
	virtual void		Free(void);
};

END