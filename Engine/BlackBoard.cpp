#include "stdafx.h"
#include "BlackBoard.h"


CBlackBoard::CBlackBoard()
{
}

CBlackBoard::CBlackBoard(const CBlackBoard & rhs)
{
}

CBlackBoard::~CBlackBoard()
{
}

HRESULT CBlackBoard::Add_Type(IN const _tchar * pTypename, IN _int& iType)
{
	auto iter = find_if(m_mapInt.begin(), m_mapInt.end(), CTag_Finder(pTypename));

	if (iter == m_mapInt.end())
	{
		m_mapInt.emplace(pTypename, iType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Add_Type(IN const _tchar * pTypename, IN _float& fType)
{
	auto iter = find_if(m_mapFloat.begin(), m_mapFloat.end(), CTag_Finder(pTypename));

	if (iter == m_mapFloat.end())
	{
		m_mapFloat.emplace(pTypename, fType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Add_Type(IN const _tchar * pTypename, IN _bool& bType)
{
	auto iter = find_if(m_mapBool.begin(), m_mapBool.end(), CTag_Finder(pTypename));

	if (iter == m_mapBool.end())
	{
		m_mapBool.emplace(pTypename, bType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Add_Type(IN const _tchar* pTypename, IN _vec3& vType)
{
	auto iter = find_if(m_mapVec.begin(), m_mapVec.end(), CTag_Finder(pTypename));

	if (iter == m_mapVec.end())
	{
		m_mapVec.emplace(pTypename, vType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Add_Type(IN const _tchar* pTypename, IN CGameObject* pType)
{
	auto iter = find_if(m_mapGameObject.begin(), m_mapGameObject.end(), CTag_Finder(pTypename));

	if (iter == m_mapGameObject.end())
	{
		m_mapGameObject.emplace(pTypename, pType);
		return S_OK;
	}
	return E_FAIL;
}

HRESULT CBlackBoard::Get_Type(IN const _tchar * pTypename, OUT _int& pOut)
{
	auto iter = find_if(m_mapInt.begin(), m_mapInt.end(), CTag_Finder(pTypename));

	if (iter == m_mapInt.end())
		return E_FAIL;

	pOut = iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(IN const _tchar * pTypename, OUT _float& pOut)
{
	auto iter = find_if(m_mapFloat.begin(), m_mapFloat.end(), CTag_Finder(pTypename));

	if (iter == m_mapFloat.end())
		return E_FAIL;

	pOut = iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(IN const _tchar * pTypename, OUT _bool& pOut)
{
	auto iter = find_if(m_mapBool.begin(), m_mapBool.end(), CTag_Finder(pTypename));

	if (iter == m_mapBool.end())
		return E_FAIL;

	pOut = iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(IN const _tchar* pTypename, OUT _vec3& pOut)
{
	auto iter = find_if(m_mapVec.begin(), m_mapVec.end(), CTag_Finder(pTypename));

	if (iter == m_mapVec.end())
		return E_FAIL;

	pOut = iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Get_Type(IN const _tchar* pTypename, OUT CGameObject* pOut)
{
	auto iter = find_if(m_mapGameObject.begin(), m_mapGameObject.end(), CTag_Finder(pTypename));

	if (iter == m_mapGameObject.end())
		return E_FAIL;

	pOut = iter->second;
	return S_OK;
}

HRESULT CBlackBoard::Set_Type(IN const _tchar * pTypename, IN _int& iType)
{
	auto iter = find_if(m_mapInt.begin(), m_mapInt.end(), CTag_Finder(pTypename));

	if (iter == m_mapInt.end())
		return E_FAIL;

	iter->second = iType;

	return S_OK;
}

HRESULT CBlackBoard::Set_Type(IN const _tchar * pTypename, IN _float& fType)
{
	auto iter = find_if(m_mapFloat.begin(), m_mapFloat.end(), CTag_Finder(pTypename));

	if (iter == m_mapFloat.end())
		return E_FAIL;

	iter->second = fType;

	return S_OK;
}

HRESULT CBlackBoard::Set_Type(IN const _tchar * pTypename, IN _bool& bType)
{
	auto iter = find_if(m_mapBool.begin(), m_mapBool.end(), CTag_Finder(pTypename));

	if (iter == m_mapBool.end())
		return E_FAIL;

	iter->second = bType;

	return S_OK;
}

HRESULT CBlackBoard::Set_Type(IN const _tchar * pTypename, IN _vec3& vType)
{
	auto iter = find_if(m_mapVec.begin(), m_mapVec.end(), CTag_Finder(pTypename));

	if (iter == m_mapVec.end())
		return E_FAIL;

	iter->second = vType;

	return S_OK;
}
