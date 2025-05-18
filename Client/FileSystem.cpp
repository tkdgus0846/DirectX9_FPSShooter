#include "FileSystem.h"
#include <locale>
#include <codecvt>
#include "RoomMgr.h"
#include "Export_Function.h"

CFileSystem::CFileSystem()
{
}


CFileSystem::~CFileSystem()
{
}

string CFileSystem::wstrToStr(const wstring & wstr)
{
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.to_bytes(wstr);
}

wstring CFileSystem::strToWStr(const string & str)
{
	wstring_convert<codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.from_bytes(str);
}

string CFileSystem::FileNameFromPath(IN const string& strFilePathName)
{
	string strFileName;
	size_t lastSlashPosition = strFilePathName.find_last_of("\\/");
	if (lastSlashPosition != std::string::npos) {
		strFileName = strFilePathName.substr(lastSlashPosition + 1);
	}
	else {
		strFileName = strFilePathName;
	}
	return strFileName;
}

wstring  CFileSystem::PathRemoveFileSpec(IN const wstring& filePath)
{
	size_t lastSlashPosition = filePath.find_last_of(L"\\/");
	if (lastSlashPosition != wstring::npos) {
		return filePath.substr(0, lastSlashPosition);
	}
	else {
		return filePath;
	}
}

wstring CFileSystem::GetCurDirectory()
{
	_tchar buffer[MAX_PATH];
	DWORD length = GetCurrentDirectory(MAX_PATH, buffer);
	wstring tmp(buffer);
	return tmp;
}

void CFileSystem::Save(const TCHAR* path)
{
	HANDLE		hFile = CreateFile(path,		// 파일 경로와 이름을 명시
		GENERIC_WRITE,			// 파일 접근 모드(쓰기 전용), GENERIC_READ(읽기 전용)
		NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대한 설정, NULL을 지정하면 공유하지 않겠다는 의미
		NULL,					// 보안 속성, NULL인 경우 기본값으로 보안 상태를 설정
		CREATE_ALWAYS,			// 생성 방식, 해당 파일을 열어서 작업을 할 것인지, 새로 만들 것인지 설정(CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다)
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성, FILE_ATTRIBUTE_NORMAL 아무런 속싱 없는 일반적인 파일 생성
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 안쓰니까 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Save File", L"Fail", MB_OK);
		return;
	}
	DWORD		dwByte = 0;

	ROOM_MGR->WriteMapFile(hFile, dwByte);

	// 파일 소멸
	CloseHandle(hFile);
}

void CFileSystem::Load(const TCHAR* path)
{
	HANDLE		hFile = CreateFile(path,		// 파일 경로와 이름을 명시
		GENERIC_READ,			// 파일 접근 모드(쓰기 전용), GENERIC_READ(읽기 전용)
		NULL,					// 공유 방식, 파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대한 설정, NULL을 지정하면 공유하지 않겠다는 의미
		NULL,					// 보안 속성, NULL인 경우 기본값으로 보안 상태를 설정
		OPEN_EXISTING,			// 생성 방식, 해당 파일을 열어서 작업을 할 것인지, 새로 만들 것인지 설정(CREATE_ALWAYS : 파일이 없다면 생성, 있다면 덮어쓰기, OPEN_EXISTING : 파일이 있을 경우에만 연다)
		FILE_ATTRIBUTE_NORMAL,  // 파일 속성, FILE_ATTRIBUTE_NORMAL 아무런 속싱 없는 일반적인 파일 생성
		NULL);					// 생성될 파일의 속성을 제공할 템플릿 파일, 안쓰니까 NULL

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load File", L"Fail", MB_OK);
		return;
	}
	DWORD		dwByte = 0;

	ROOM_MGR->ReadMapFile(hFile, dwByte);

	// 파일 소멸
	CloseHandle(hFile);
}