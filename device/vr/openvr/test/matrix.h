#ifndef _openvr_matrix_h_
#define _openvr_matrix_h_

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"

void setPoseMatrix(float *dstMatrixArray, const vr::HmdMatrix34_t &srcMatrix);
void setPoseMatrix(float *dstMatrixArray, const vr::HmdMatrix44_t &srcMatrix);
void setPoseMatrix(vr::HmdMatrix34_t &dstMatrix, const float *srcMatrixArray);
void getMatrixInverse(const float *inMatrix, float *outMatrix);
void multiplyMatrices(const float *aMatrix, const float *bMatrix, float *outMatrix);
void composeMatrix(float *matrix, const float *position, const float *quaternion, const float *scale);
void addVector(float *a, const float *b);
void applyVectorQuaternion(float *v, const float *q);
void applyVectorMatrix(float *v, const float *m);
void multiplyVectors(float *a, const float *b);
void divideVectors(float *a, const float *b);
void multiplyVectorScalar(float *v, const float s);
void addVectorScalar(float *v, const float s);

#endif