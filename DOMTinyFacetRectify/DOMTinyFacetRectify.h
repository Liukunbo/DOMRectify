#ifdef DOMTINYFACETRECTIFY_EXPORTS
//#define DOMTINYFACETRECTIFY_API __declspec(dllexport)
//#else
//#define DOMTINYFACETRECTIFY_API __declspec(dllimport)
//#endif

#define DOMTINYFACETRECTIFY_API _declspec(dllexport)
#else
#define DOMTINYFACETRECTIFY_API _declspec(dllimport)
#pragma comment(lib, "DOMTinyFacetRectify.lib")
#pragma message("Automatically Linking With DOMTinyFacetRectify.dll")
#endif


#include "CorrespondPtIO.h"
/************************************************************************/
/*                           ��Ӱ�񣺴�����Ӱ��                           */
/*                           ��Ӱ�񣺵�ͼDOM                             */
/************************************************************************/
/*                           lpstrCpPts��ʽ                             */
/*                           ����Ӱ��·��                                */
/************************************************************************/

DOMTINYFACETRECTIFY_API bool DOMTinyFacetRectify_images(const char* lpstrCpPts, const char* lpstrTarImage);

//���ƥ������С��Ԫ���������ھ���Ӱ���ڴ�飨��Ӱ��λ������Ӱ��
//ltfw�� rtfw ����Ӱ��ķ���任����
//plindata ������Ӱ��� poutdata ������Ӱ���
//lrows lcols ��Ӱ��������
//slrow slcol ��Ӱ�����ʼ����
//nPxlBytes ��������
//CorrespondPt* CpPt, int npt �������ƥ�������
DOMTINYFACETRECTIFY_API void DOMminiTinyFacetRectify8bit(const double *ltfw, const double *rtfw, const unsigned char* plindata, int lrows, int lcols, int nPxlBytes, int slrow, int slcol, CorrespondPt* CpPt, int npt, unsigned char* poutdata, int nBkgrdClr = 0);

DOMTINYFACETRECTIFY_API void DOMminiTinyFacetRectify16bit(const double *ltfw, const double *rtfw, const unsigned short* plindata, int lrows, int lcols, int nPxlBytes, int slrow, int slcol, CorrespondPt* CpPt, int npt, unsigned short* poutdata, int nBkgrdClr = 0);
