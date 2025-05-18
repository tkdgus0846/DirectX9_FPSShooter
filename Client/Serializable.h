#pragma once
__interface ISerializable
{
	virtual void Serialization(HANDLE hFile, DWORD& dwByte) = 0;
	virtual void Deserialization(HANDLE hFile, DWORD& dwByte) = 0;
};