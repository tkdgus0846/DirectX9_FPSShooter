#pragma once
#include "ImWindow.h"

BEGIN(Engine)
class CGameObject;
END

class CRoomMgr;
class CRoom;
class CEditCamera;
class CImPickBox;
class CFactory;

class CImInspector : public CImWindow
{
private:
	explicit CImInspector(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CImInspector();

public:
	virtual HRESULT Ready_ImWindow() override;
	virtual _int	Update(float fTimeDelta) override;
	_int	Get_PickType() { return m_iCurPickType; }
	wstring	Get_CurTag() { return m_CurTag; }
	_int	Get_Radio() { return m_radio; }

private:
	void Show_RoomInfo();
	void Show_Components();
	void Show_PlaceMode();
	void Show_MonsterList();

private:
	CRoom*			m_pCurRoom;
	_vec3			m_vObjectPos;
	CGameObject*	m_pCurTarget;
	CEditCamera*	m_pCamera;

	// PickMode
	_int		m_radio;
	_int		m_iCurPickType;
	wstring		m_CurTag;
	CImPickBox*		m_pPickBox[PICK_END];
	vector<pair<string, CFactory*>> items;

	// ObjectList
	class ListBox*	m_pObjListBox;

public:
	static CImInspector* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};