#pragma once

BEGIN(Engine)

class CGameObject;
class CBlackBoard
{
public:
	explicit CBlackBoard();
	explicit CBlackBoard(const CBlackBoard& rhs);
	~CBlackBoard();

public:
	HRESULT Add_Type(IN const _tchar* pTypename, IN _int& iType);
	HRESULT Add_Type(IN const _tchar* pTypename, IN _float& fType);
	HRESULT Add_Type(IN const _tchar* pTypename, IN _bool& bType);
	HRESULT Add_Type(IN const _tchar* pTypename, IN _vec3& vType);
	HRESULT Add_Type(IN const _tchar* pTypename, IN CGameObject* pType);

	HRESULT Get_Type(IN const _tchar* pTypename, OUT _int& pOut);
	HRESULT Get_Type(IN const _tchar* pTypename, OUT _float& pOut);
	HRESULT Get_Type(IN const _tchar* pTypename, OUT _bool& pOut);
	HRESULT Get_Type(IN const _tchar* pTypename, OUT _vec3& pOut);
	HRESULT Get_Type(IN const _tchar* pTypename, OUT CGameObject* pOut);

	HRESULT Set_Type(IN const _tchar* pTypename, IN _int& iType);
	HRESULT Set_Type(IN const _tchar* pTypename, IN _float& fType);
	HRESULT Set_Type(IN const _tchar* pTypename, IN _bool& bType);
	HRESULT Set_Type(IN const _tchar* pTypename, IN _vec3& vType);

private:
	map<const _tchar*, _int&>			m_mapInt;
	map<const _tchar*, _float&>			m_mapFloat;
	map<const _tchar*, _bool&>			m_mapBool;
	map<const _tchar*, _vec3&>			m_mapVec;
	map<const _tchar*, CGameObject*>	m_mapGameObject;
};

END