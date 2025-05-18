#pragma once

#include "GameObject.h"
#include "FloorTile.h"

class CWall;
class CTile;
class CFloor;
class CDoor;

BEGIN(Engine)
	class CLayer;
	class CCollider;
END

class CRoom : public Engine::CGameObject
{
private:
	explicit CRoom(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CRoom();

public:
	HRESULT Ready_GameObject(STAGEINFO stageInfo, const _float& fVtxCntX, const _float& fVtxCntZ, const _float& fVtxItv);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	CFloorTile* GetCurFloorTile(CGameObject* pGameObject);
	void		SetNullFloorTile(_int x, _int z)
	{
		m_pTileArray[z][x] = nullptr;
	}
	CDoor* Get_Door(DOOR_DIR eDir) { return m_apDoor[eDir].second; }
	DOOR_TYPE Get_DoorType() { return m_eDoorType; }
	CFloor* GetFloor() const { return m_pFloor; }
	CWall* GetWallArray(_uint index) const { return m_apWall[index]; }

	_int Get_Room_Index();
	void Open_Doors();
	void Close_Doors();

	_bool& Cur_Door_State(DOOR_DIR eDir) { return m_apDoor[eDir].first; }
	void Set_DoorType(DOOR_TYPE eType);

private:
	virtual HRESULT Add_Component() override;
	HRESULT CreateSubset(STAGEINFO stageInfo);
	void	FreeSubset();
	
public:
	void EraseGameObject(CGameObject* obj);

	void FloorSubSet();
	void PlaceSubSet();
	_bool WriteRoomFile(HANDLE hFile, DWORD& dwByte);
	_bool ReadRoomFile(HANDLE hFile, DWORD& dwByte);
	_int ObjNum() const  { return m_vecGameObj.size(); }
	CGameObject* GetObjByIndex(_int iIndex) const
	{
		if (iIndex < 0 || iIndex >= m_vecGameObj.size()) return nullptr;
		return m_vecGameObj[iIndex];
	}

	void PushBack_GameObj(CGameObject* pObj, _bool bObjectHead = true);

public:
	vector<CLayer*>* GetLayerVec() { return &m_vecLayer; }
	list<CCollider*>* GetColliderList(_int iIndex) 
	{
		if (iIndex >= COL_STATIC_END) return nullptr;
		return &m_ColliderList[iIndex];
	}

private:
	_float				m_fVtxCntX;
	_float				m_fVtxCntZ;
	_float				m_fVtxItv;
 
	vector<CGameObject*>	m_vecGameObj;	

	CFloor*				m_pFloor;
	array<CWall*, 4>	m_apWall;
	array<pair<_bool, CDoor*>, 4>	m_apDoor;
	DOOR_TYPE			m_eDoorType;

	array<array<CFloorTile*, VTXCNTX - 1>, VTXCNTZ - 1> m_pTileArray;
	
private:
	vector<CLayer*> m_vecLayer;
	list<CCollider*> m_ColliderList[COL_STATIC_END];

public:
	static CRoom*		Create(LPDIRECT3DDEVICE9 pGraphicDev, STAGEINFO stageInfo,  const	_float& fVtxCntX = VTXCNTX, const _float& fVtxCntZ = VTXCNTZ, const _float& fVtxItv = VTXITV);

private:
	virtual void Free(void) override;
};

