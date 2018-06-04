#ifndef  _GEOMETRY_H_
#define  _GEOMETRY_H_

#include "GeometryInclude.h"
#include "DelaunayTriangleation.h"

GEOMETRYAPI OGREnvelope GetRasterEnvelope(GDALDataset* pDataSet);

GEOMETRYAPI void   GeometryCompress(OGRGeometry* pGeometry, OGRGeometry*& pCompressGeometry); //����ѹ��

GEOMETRYAPI void   GeometryFilter(OGRGeometry* pGeometry, OGRGeometry*& pFilterGeometry);     //�����ظ���

GEOMETRYAPI void   GeometryZoom(const string& srcfilename, const string& dstfilename, double scale); //����

GEOMETRYAPI void   GeometryTranslate(OGRGeometry* pGeometry, double x, double y); //ƽ��

GEOMETRYAPI bool   Intersect(const OGREnvelope& e1, const OGREnvelope& e2, OGREnvelope& cross);

GEOMETRYAPI bool   Intersect(const OGREnvelope& e1, const OGREnvelope& e2);

GEOMETRYAPI void   Union(const OGREnvelope& e1, const OGREnvelope& e2, OGREnvelope& e);

GEOMETRYAPI OGRPolygon*    EnvelopeToPolygon(const OGREnvelope& enve);

GEOMETRYAPI OGRLinearRing* LineString2LinearRing(OGRLineString* pLinearRing);

GEOMETRYAPI void GraphCut(int* pCost, BYTE* pMask, int* pIndex, int nCols, int nRows, BYTE nSrc, BYTE nDst, BYTE nNone, BYTE nSrcDst);

#endif