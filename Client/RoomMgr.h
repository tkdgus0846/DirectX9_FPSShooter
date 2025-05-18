#pragma once

#include "Base.h"
#include "Include.h"
#include "Room.h"
BEGIN(Engine)
class CCollider;
class CLayer;
END



class CRoomMgr : public CBase
{
	DECLARE_SINGLETON(CRoomMgr);

public:
	explicit CRoomMgr();
	~CRoomMgr();

public:
	HRESULT Ready_RoomMgr(LPDIRECT3DDEVICE9	pGraphicDev);
	void	Release_All_Room();

	class CRoom*		Get_CurRoom() { return m_pCurRoom; }
	void				Set_CurRoom(const _uint iIndex);

	class CTennel*		Get_Tennel(const _int i) { return m_pTennel[i]; }
	void Set_Tennel(class CTennel* tennel, _int iIndex);
	_bool Is_In_Tennel() { return m_bIsInTennel; }
	void Set_In_Tennel(_bool state) 
	{ m_bIsInTennel = state; }

	STAGEINFO			Get_CurStageInfo();



	_bool WriteMapFile(HANDLE hFile, DWORD& dwByte);
	_bool ReadMapFile(HANDLE hFile, DWORD& dwByte);

	vector<CLayer*>* Get_CurLayerVec();
	list<CCollider*>* Get_CurColliderList(_int iIndex);
	CRoom* Get_Room(const _int iIndex) { return m_arrRoom[iIndex]; }
	
	void			Create_Default_Room(STAGEINFO stageInfo);
	void			Push_Back_Obj(_int iIndex, CGameObject* pObj);

	void			Set_Tennel_Texture(STAGEINFO stageInfo);
			
private:
	class CRoom*		m_pCurRoom;
	array<CRoom*, 9>	m_arrRoom;

	class CTennel*		m_pTennel[2];	
	_bool				m_bIsInTennel;


	LPDIRECT3DDEVICE9	m_pGraphicDev;

public:
	void Free();
};

#define ROOM_MGR CRoomMgr::GetInstance()

