#include "StdAfx.h"
#include "MyMemTxtFile.h"


CMyMemTxtFile::CMyMemTxtFile()
{

}
CMyMemTxtFile::~CMyMemTxtFile()
{
	CloseFile();
}
bool CMyMemTxtFile::OpenFile(CString strFilePath)
{
	m_hFile = INVALID_HANDLE_VALUE;
	m_hFileMap = NULL;
	m_lpbFile = NULL;
	m_dwFileSize = 0;
	if (!PathFileExists(strFilePath)) return false;
	m_hFile = CreateFile(strFilePath, //·��
		GENERIC_READ,//��
		FILE_SHARE_READ, //����ֻ��
		NULL,//��ȫ����
		OPEN_EXISTING,//�ļ��������
		FILE_FLAG_SEQUENTIAL_SCAN,//����������ʶ��ļ���������Ż�
		NULL);  //�����Ϊ0����ָ��һ���ļ����
	if (INVALID_HANDLE_VALUE == m_hFile) return false;
	m_dwFileSize = ::GetFileSize(m_hFile, NULL);
	m_hFileMap = CreateFileMapping(m_hFile,
		NULL,//��ȫ����
		PAGE_READONLY,//ֻ����ʽ��ӳ��
		0,
		0,//�ô����ļ�ʵ�ʳ���
		NULL);//ָ���ļ�ӳ����������
	if (NULL == m_hFileMap) return false;
	m_lpbFile = (char*)MapViewOfFile(
		m_hFileMap,
		FILE_MAP_READ,
		0,
		0,//ӳ�������ļ�ӳ�����
		0);//0��ʾ����WindowsѰ�ҵ�ַ
	if (NULL == m_lpbFile) return false;
	return true;
}
void CMyMemTxtFile::CloseFile()
{
	if (m_lpbFile != NULL) UnmapViewOfFile(m_lpbFile);
	if (m_hFileMap != NULL) CloseHandle(m_hFileMap);
	if (m_hFile != INVALID_HANDLE_VALUE) CloseHandle(m_hFile);
	m_hFile = INVALID_HANDLE_VALUE;
	m_hFileMap = NULL;
	m_lpbFile = NULL;
	m_dwFileSize = 0;
}
