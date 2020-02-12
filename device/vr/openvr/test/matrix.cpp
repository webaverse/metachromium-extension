#include "device/vr/openvr/test/matrix.h"

float vectorLength(float x, float y, float z) {
  return std::sqrt(x*x + y*y + z*z);
}
void setPoseMatrix(float *dstMatrixArray, const vr::HmdMatrix44_t &srcMatrix) {
  for (unsigned int v = 0; v < 4; v++) {
    for (unsigned int u = 0; u < 4; u++) {
      dstMatrixArray[v * 4 + u] = srcMatrix.m[u][v];
    }
  }
}
void setPoseMatrix(float *dstMatrixArray, const vr::HmdMatrix34_t &srcMatrix) {
  for (unsigned int v = 0; v < 4; v++) {
    for (unsigned int u = 0; u < 3; u++) {
      dstMatrixArray[v * 4 + u] = srcMatrix.m[u][v];
    }
  }
  dstMatrixArray[0 * 4 + 3] = 0;
  dstMatrixArray[1 * 4 + 3] = 0;
  dstMatrixArray[2 * 4 + 3] = 0;
  dstMatrixArray[3 * 4 + 3] = 1;
}
void setPoseMatrix(vr::HmdMatrix34_t &dstMatrix, const float *srcMatrixArray) {
  for (unsigned int v = 0; v < 4; v++) {
    for (unsigned int u = 0; u < 3; u++) {
      dstMatrix.m[u][v] = srcMatrixArray[v * 4 + u];
    }
  }
}
float matrixDeterminant(const float *matrix) {
  const float *te = matrix;

  float n11 = te[ 0 ], n12 = te[ 4 ], n13 = te[ 8 ], n14 = te[ 12 ];
  float n21 = te[ 1 ], n22 = te[ 5 ], n23 = te[ 9 ], n24 = te[ 13 ];
  float n31 = te[ 2 ], n32 = te[ 6 ], n33 = te[ 10 ], n34 = te[ 14 ];
  float n41 = te[ 3 ], n42 = te[ 7 ], n43 = te[ 11 ], n44 = te[ 15 ];

  //TODO: make this more efficient
  //( based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm )

  return (
    n41 * (
      + n14 * n23 * n32
       - n13 * n24 * n32
       - n14 * n22 * n33
       + n12 * n24 * n33
       + n13 * n22 * n34
       - n12 * n23 * n34
    ) +
    n42 * (
      + n11 * n23 * n34
       - n11 * n24 * n33
       + n14 * n21 * n33
       - n13 * n21 * n34
       + n13 * n24 * n31
       - n14 * n23 * n31
    ) +
    n43 * (
      + n11 * n24 * n32
       - n11 * n22 * n34
       - n14 * n21 * n32
       + n12 * n21 * n34
       + n14 * n22 * n31
       - n12 * n24 * n31
    ) +
    n44 * (
      - n13 * n22 * n31
       - n11 * n23 * n32
       + n11 * n22 * n33
       + n13 * n21 * n32
       - n12 * n21 * n33
       + n12 * n23 * n31
    )
  );
}
void getQuaternionFromRotationMatrix(float *quaternion, const float *matrix) {
  // http://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
  // assumes the upper 3x3 of m is a pure rotation matrix (i.e, unscaled)

  const float *te = matrix;

  const float m11 = te[ 0 ], m12 = te[ 4 ], m13 = te[ 8 ],
    m21 = te[ 1 ], m22 = te[ 5 ], m23 = te[ 9 ],
    m31 = te[ 2 ], m32 = te[ 6 ], m33 = te[ 10 ];

  float trace = m11 + m22 + m33,
    s;

  if (trace > 0.0f) {
    s = 0.5f / std::sqrt(trace + 1.0f);

    quaternion[0] = (m32 - m23) * s;
    quaternion[1] = (m13 - m31) * s;
    quaternion[2] = (m21 - m12) * s;
    quaternion[3] = 0.25f / s;
  } else if (m11 > m22 && m11 > m33) {
    s = 2.0f * std::sqrt(1.0f + m11 - m22 - m33 );

    quaternion[0] = 0.25f * s;
    quaternion[1] = (m12 + m21) / s;
    quaternion[2] = (m13 + m31) / s;
    quaternion[3] = (m32 - m23) / s;
  } else if (m22 > m33) {
    s = 2.0f * std::sqrt(1.0f + m22 - m11 - m33);

    quaternion[0] = (m12 + m21) / s;
    quaternion[1] = 0.25f * s;
    quaternion[2] = (m23 + m32) / s;
    quaternion[3] = (m13 - m31) / s;
  } else {
    s = 2.0f * std::sqrt(1.0f + m33 - m11 - m22);

    quaternion[0] = (m13 + m31) / s;
    quaternion[1] = (m23 + m32) / s;
    quaternion[2] = 0.25f * s;
    quaternion[3] = (m21 - m12) / s;
  }
}
void getMatrixInverse(const float *inMatrix, float *outMatrix) {
  // based on http://www.euclideanspace.com/maths/algebra/matrix/functions/inverse/fourD/index.htm
  float *te = outMatrix;
  const float *me = inMatrix;

  const float n11 = me[ 0 ], n21 = me[ 1 ], n31 = me[ 2 ], n41 = me[ 3 ],
    n12 = me[ 4 ], n22 = me[ 5 ], n32 = me[ 6 ], n42 = me[ 7 ],
    n13 = me[ 8 ], n23 = me[ 9 ], n33 = me[ 10 ], n43 = me[ 11 ],
    n14 = me[ 12 ], n24 = me[ 13 ], n34 = me[ 14 ], n44 = me[ 15 ],

    t11 = n23 * n34 * n42 - n24 * n33 * n42 + n24 * n32 * n43 - n22 * n34 * n43 - n23 * n32 * n44 + n22 * n33 * n44,
    t12 = n14 * n33 * n42 - n13 * n34 * n42 - n14 * n32 * n43 + n12 * n34 * n43 + n13 * n32 * n44 - n12 * n33 * n44,
    t13 = n13 * n24 * n42 - n14 * n23 * n42 + n14 * n22 * n43 - n12 * n24 * n43 - n13 * n22 * n44 + n12 * n23 * n44,
    t14 = n14 * n23 * n32 - n13 * n24 * n32 - n14 * n22 * n33 + n12 * n24 * n33 + n13 * n22 * n34 - n12 * n23 * n34;

  const float det = n11 * t11 + n21 * t12 + n31 * t13 + n41 * t14;

  if (det == 0.0f) {
    getOut() << "Can't invert matrix, determinant is 0" << std::endl;
  }

  const float detInv = 1.0f / det;

  te[ 0 ] = t11 * detInv;
  te[ 1 ] = ( n24 * n33 * n41 - n23 * n34 * n41 - n24 * n31 * n43 + n21 * n34 * n43 + n23 * n31 * n44 - n21 * n33 * n44 ) * detInv;
  te[ 2 ] = ( n22 * n34 * n41 - n24 * n32 * n41 + n24 * n31 * n42 - n21 * n34 * n42 - n22 * n31 * n44 + n21 * n32 * n44 ) * detInv;
  te[ 3 ] = ( n23 * n32 * n41 - n22 * n33 * n41 - n23 * n31 * n42 + n21 * n33 * n42 + n22 * n31 * n43 - n21 * n32 * n43 ) * detInv;

  te[ 4 ] = t12 * detInv;
  te[ 5 ] = ( n13 * n34 * n41 - n14 * n33 * n41 + n14 * n31 * n43 - n11 * n34 * n43 - n13 * n31 * n44 + n11 * n33 * n44 ) * detInv;
  te[ 6 ] = ( n14 * n32 * n41 - n12 * n34 * n41 - n14 * n31 * n42 + n11 * n34 * n42 + n12 * n31 * n44 - n11 * n32 * n44 ) * detInv;
  te[ 7 ] = ( n12 * n33 * n41 - n13 * n32 * n41 + n13 * n31 * n42 - n11 * n33 * n42 - n12 * n31 * n43 + n11 * n32 * n43 ) * detInv;

  te[ 8 ] = t13 * detInv;
  te[ 9 ] = ( n14 * n23 * n41 - n13 * n24 * n41 - n14 * n21 * n43 + n11 * n24 * n43 + n13 * n21 * n44 - n11 * n23 * n44 ) * detInv;
  te[ 10 ] = ( n12 * n24 * n41 - n14 * n22 * n41 + n14 * n21 * n42 - n11 * n24 * n42 - n12 * n21 * n44 + n11 * n22 * n44 ) * detInv;
  te[ 11 ] = ( n13 * n22 * n41 - n12 * n23 * n41 - n13 * n21 * n42 + n11 * n23 * n42 + n12 * n21 * n43 - n11 * n22 * n43 ) * detInv;

  te[ 12 ] = t14 * detInv;
  te[ 13 ] = ( n13 * n24 * n31 - n14 * n23 * n31 + n14 * n21 * n33 - n11 * n24 * n33 - n13 * n21 * n34 + n11 * n23 * n34 ) * detInv;
  te[ 14 ] = ( n14 * n22 * n31 - n12 * n24 * n31 - n14 * n21 * n32 + n11 * n24 * n32 + n12 * n21 * n34 - n11 * n22 * n34 ) * detInv;
  te[ 15 ] = ( n12 * n23 * n31 - n13 * n22 * n31 + n13 * n21 * n32 - n11 * n23 * n32 - n12 * n21 * n33 + n11 * n22 * n33 ) * detInv;
}
void multiplyMatrices(const float *aMatrix, const float *bMatrix, float *outMatrix) {
  const float *ae = aMatrix;
  const float *be = bMatrix;
  float *te = outMatrix;

  const float a11 = ae[ 0 ], a12 = ae[ 4 ], a13 = ae[ 8 ], a14 = ae[ 12 ];
  const float a21 = ae[ 1 ], a22 = ae[ 5 ], a23 = ae[ 9 ], a24 = ae[ 13 ];
  const float a31 = ae[ 2 ], a32 = ae[ 6 ], a33 = ae[ 10 ], a34 = ae[ 14 ];
  const float a41 = ae[ 3 ], a42 = ae[ 7 ], a43 = ae[ 11 ], a44 = ae[ 15 ];

  const float b11 = be[ 0 ], b12 = be[ 4 ], b13 = be[ 8 ], b14 = be[ 12 ];
  const float b21 = be[ 1 ], b22 = be[ 5 ], b23 = be[ 9 ], b24 = be[ 13 ];
  const float b31 = be[ 2 ], b32 = be[ 6 ], b33 = be[ 10 ], b34 = be[ 14 ];
  const float b41 = be[ 3 ], b42 = be[ 7 ], b43 = be[ 11 ], b44 = be[ 15 ];

  te[ 0 ] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
  te[ 4 ] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
  te[ 8 ] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
  te[ 12 ] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;

  te[ 1 ] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
  te[ 5 ] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
  te[ 9 ] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
  te[ 13 ] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;

  te[ 2 ] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
  te[ 6 ] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
  te[ 10 ] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
  te[ 14 ] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;

  te[ 3 ] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;
  te[ 7 ] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;
  te[ 11 ] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;
  te[ 15 ] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;
}
void composeMatrix(float *matrix, const float *position, const float *quaternion, const float *scale) {
  float *te = matrix;

  float x = quaternion[0], y = quaternion[1], z = quaternion[2], w = quaternion[3];
  float x2 = x + x, y2 = y + y, z2 = z + z;
  float xx = x * x2, xy = x * y2, xz = x * z2;
  float yy = y * y2, yz = y * z2, zz = z * z2;
  float wx = w * x2, wy = w * y2, wz = w * z2;

  float sx = scale[0], sy = scale[1], sz = scale[2];

  te[ 0 ] = ( 1 - ( yy + zz ) ) * sx;
  te[ 1 ] = ( xy + wz ) * sx;
  te[ 2 ] = ( xz - wy ) * sx;
  te[ 3 ] = 0;

  te[ 4 ] = ( xy - wz ) * sy;
  te[ 5 ] = ( 1 - ( xx + zz ) ) * sy;
  te[ 6 ] = ( yz + wx ) * sy;
  te[ 7 ] = 0;

  te[ 8 ] = ( xz + wy ) * sz;
  te[ 9 ] = ( yz - wx ) * sz;
  te[ 10 ] = ( 1 - ( xx + yy ) ) * sz;
  te[ 11 ] = 0;

  te[ 12 ] = position[0];
  te[ 13 ] = position[1];
  te[ 14 ] = position[2];
  te[ 15 ] = 1;
}
void decomposeMatrix(const float *matrix, float *position, float *quaternion, float *scale) {
  const float *te = matrix;

  float sx = vectorLength(te[ 0 ], te[ 1 ], te[ 2 ]);
  float sy = vectorLength(te[ 4 ], te[ 5 ], te[ 6 ]);
  float sz = vectorLength(te[ 8 ], te[ 9 ], te[ 10 ]);

  // if determine is negative, we need to invert one scale
  float det = matrixDeterminant(matrix);
  if ( det < 0 ) sx = - sx;

  position[0] = te[ 12 ];
  position[1] = te[ 13 ];
  position[2] = te[ 14 ];

  // scale the rotation part
  float _m1[16];
  memcpy(_m1, matrix, 16 * sizeof(float));

  float invSX = 1.0f / sx;
  float invSY = 1.0f / sy;
  float invSZ = 1.0f / sz;

  _m1[ 0 ] *= invSX;
  _m1[ 1 ] *= invSX;
  _m1[ 2 ] *= invSX;

  _m1[ 4 ] *= invSY;
  _m1[ 5 ] *= invSY;
  _m1[ 6 ] *= invSY;

  _m1[ 8 ] *= invSZ;
  _m1[ 9 ] *= invSZ;
  _m1[ 10 ] *= invSZ;

  getQuaternionFromRotationMatrix(quaternion, matrix);

  scale[0] = sx;
  scale[1] = sy;
  scale[2] = sz;
}
void addVector3(float *a, const float *b) {
  a[0] += b[0];
  a[1] += b[1];
  a[2] += b[2];
}
void addVector4(float *a, const float *b) {
  a[0] += b[0];
  a[1] += b[1];
  a[2] += b[2];
  a[3] += b[3];
}
void applyVector3Quaternion(float *v, const float *q) {
  float x = v[0], y = v[1], z = v[2];
  float qx = q[0], qy = q[1], qz = q[2], qw = q[3];

  // calculate quat * vector

  float ix = qw * x + qy * z - qz * y;
  float iy = qw * y + qz * x - qx * z;
  float iz = qw * z + qx * y - qy * x;
  float iw = - qx * x - qy * y - qz * z;

  // calculate result * inverse quat

  v[0] = ix * qw + iw * - qx + iy * - qz - iz * - qy;
  v[1] = iy * qw + iw * - qy + iz * - qx - ix * - qz;
  v[2] = iz * qw + iw * - qz + ix * - qy - iy * - qx;
}
void applyVector3Matrix(float *v, const float *m) {
  float x = v[0], y = v[1], z = v[2];
  const float *e = m;

  float w = 1.0f / ( e[ 3 ] * x + e[ 7 ] * y + e[ 11 ] * z + e[ 15 ] );

  v[0] = ( e[ 0 ] * x + e[ 4 ] * y + e[ 8 ] * z + e[ 12 ] ) * w;
  v[1] = ( e[ 1 ] * x + e[ 5 ] * y + e[ 9 ] * z + e[ 13 ] ) * w;
  v[2] = ( e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z + e[ 14 ] ) * w;
}
void applyVector4Matrix(float *v, const float *m) {
  float x = v[0], y = v[1], z = v[2], w = v[3];
  const float *e = m;

  v[0] = e[ 0 ] * x + e[ 4 ] * y + e[ 8 ] * z + e[ 12 ] * w;
  v[1] = e[ 1 ] * x + e[ 5 ] * y + e[ 9 ] * z + e[ 13 ] * w;
  v[2] = e[ 2 ] * x + e[ 6 ] * y + e[ 10 ] * z + e[ 14 ] * w;
  v[3] = e[ 3 ] * x + e[ 7 ] * y + e[ 11 ] * z + e[ 15 ] * w;
}
void multiplyVectors3(float *a, const float *b) {
  a[0] *= b[0];
  a[1] *= b[1];
  a[2] *= b[2];
}
void multiplyVectors4(float *a, const float *b) {
  a[0] *= b[0];
  a[1] *= b[1];
  a[2] *= b[2];
  a[3] *= b[3];
}
void divideVectors3(float *a, const float *b) {
  a[0] /= b[0];
  a[1] /= b[1];
  a[2] /= b[2];
}
void divideVectors4(float *a, const float *b) {
  a[0] /= b[0];
  a[1] /= b[1];
  a[2] /= b[2];
  a[3] /= b[3];
}
void multiplyVector3Scalar(float *v, const float s) {
  v[0] *= s;
  v[1] *= s;
  v[2] *= s;
}
void multiplyVector4Scalar(float *v, const float s) {
  v[0] *= s;
  v[1] *= s;
  v[2] *= s;
  v[3] *= s;
}
void addVector3Scalar(float *v, const float s) {
  v[0] += s;
  v[1] += s;
  v[2] += s;
}
void addVector4Scalar(float *v, const float s) {
  v[0] += s;
  v[1] += s;
  v[2] += s;
}