#ifndef _openvr_matrix_h_
#define _openvr_matrix_h_

#include "third_party/openvr/src/headers/openvr.h"
#include "device/vr/openvr/test/out.h"

float vectorLength(float x, float y, float z);
void setPoseMatrix(float *dstMatrixArray, const vr::HmdMatrix44_t &srcMatrix);
void setPoseMatrix(float *dstMatrixArray, const vr::HmdMatrix34_t &srcMatrix);
void setPoseMatrix(vr::HmdMatrix34_t &dstMatrix, const float *srcMatrixArray);
float matrixDeterminant(float *matrix);
void getQuaternionFromRotationMatrix(float *quaternion, const float *matrix);
void getMatrixInverse(const float *inMatrix, float *outMatrix);
void multiplyMatrices(const float *aMatrix, const float *bMatrix, float *outMatrix);
void composeMatrix(float *matrix, const float *position, const float *quaternion, const float *scale);
void decomposeMatrix(const float *matrix, float *position, float *quaternion, float *scale);
void addVector3(float *a, const float *b);
void addVector4(float *a, const float *b);
void applyVector3Quaternion(float *v, const float *q);
void applyVector3Matrix(float *v, const float *m);
void applyVector4Matrix(float *v, const float *m);
void multiplyVectors3(float *a, const float *b);
void multiplyVectors4(float *a, const float *b);
void divideVectors3(float *a, const float *b);
void divideVectors4(float *a, const float *b);
void multiplyVector3Scalar(float *v, const float s);
void multiplyVector4Scalar(float *v, const float s);
void addVector3Scalar(float *v, const float s);
void addVector4Scalar(float *v, const float s);
void perspectiveDivideVector(float *v);

#endif