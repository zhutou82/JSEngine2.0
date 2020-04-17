#include "PCH.h"
#include "JSEngine/Math/Mat4.h"

const Mat4f & Mat4f::operator=(const Mat4f & rhs)
{
    m_XYZWMM[0] = rhs.m_XYZWMM[0];
    m_XYZWMM[1] = rhs.m_XYZWMM[1];
    return *this;
}

const Mat4f & Mat4f::operator+=(const Mat4f & rhs)
{
    m_XYZWMM[0] = _mm256_add_ps(m_XYZWMM[0], rhs.m_XYZWMM[0]);
    m_XYZWMM[1] = _mm256_add_ps(m_XYZWMM[1], rhs.m_XYZWMM[1]);
    return *this;
}

const Mat4f & Mat4f::operator-=(const Mat4f & rhs)
{
    m_XYZWMM[0] = _mm256_sub_ps(m_XYZWMM[0], rhs.m_XYZWMM[0]);
    m_XYZWMM[1] = _mm256_sub_ps(m_XYZWMM[1], rhs.m_XYZWMM[1]);
    return *this;
}

const Mat4f & Mat4f::operator*=(const Mat4f & rhs)
{
    Mat4f tRhs = Mat4::Transpose(rhs);
    //float tmp [] = {
    //m_XYZWMat[0][0] * rhs.m_XYZWMat[0][0] + m_XYZWMat[0][1] * rhs.m_XYZWMat[1][0] + m_XYZWMat[0][2] * rhs.m_XYZWMat[2][0] + m_XYZWMat[0][3] * rhs.m_XYZWMat[3][0],
    //m_XYZWMat[1][0] * rhs.m_XYZWMat[0][0] + m_XYZWMat[1][1] * rhs.m_XYZWMat[1][0] + m_XYZWMat[1][2] * rhs.m_XYZWMat[2][0] + m_XYZWMat[1][3] * rhs.m_XYZWMat[3][0],
    //m_XYZWMat[2][0] * rhs.m_XYZWMat[0][0] + m_XYZWMat[2][1] * rhs.m_XYZWMat[1][0] + m_XYZWMat[2][2] * rhs.m_XYZWMat[2][0] + m_XYZWMat[2][3] * rhs.m_XYZWMat[3][0],
    //m_XYZWMat[3][0] * rhs.m_XYZWMat[0][0] + m_XYZWMat[3][1] * rhs.m_XYZWMat[1][0] + m_XYZWMat[3][2] * rhs.m_XYZWMat[2][0] + m_XYZWMat[3][3] * rhs.m_XYZWMat[3][0],

    //m_XYZWMat[0][0] * rhs.m_XYZWMat[0][1] + m_XYZWMat[0][1] * rhs.m_XYZWMat[1][1] + m_XYZWMat[0][2] * rhs.m_XYZWMat[2][1] + m_XYZWMat[0][3] * rhs.m_XYZWMat[3][1],
    //m_XYZWMat[1][0] * rhs.m_XYZWMat[0][1] + m_XYZWMat[1][1] * rhs.m_XYZWMat[1][1] + m_XYZWMat[1][2] * rhs.m_XYZWMat[2][1] + m_XYZWMat[1][3] * rhs.m_XYZWMat[3][1],
    //m_XYZWMat[2][0] * rhs.m_XYZWMat[0][1] + m_XYZWMat[2][1] * rhs.m_XYZWMat[1][1] + m_XYZWMat[2][2] * rhs.m_XYZWMat[2][1] + m_XYZWMat[2][3] * rhs.m_XYZWMat[3][1],
    //m_XYZWMat[3][0] * rhs.m_XYZWMat[0][1] + m_XYZWMat[3][1] * rhs.m_XYZWMat[1][1] + m_XYZWMat[3][2] * rhs.m_XYZWMat[2][1] + m_XYZWMat[3][3] * rhs.m_XYZWMat[3][1],

    //m_XYZWMat[0][0] * rhs.m_XYZWMat[0][2] + m_XYZWMat[0][1] * rhs.m_XYZWMat[1][2] + m_XYZWMat[0][2] * rhs.m_XYZWMat[2][2] + m_XYZWMat[0][3] * rhs.m_XYZWMat[3][2],
    //m_XYZWMat[1][0] * rhs.m_XYZWMat[0][2] + m_XYZWMat[1][1] * rhs.m_XYZWMat[1][2] + m_XYZWMat[1][2] * rhs.m_XYZWMat[2][2] + m_XYZWMat[1][3] * rhs.m_XYZWMat[3][2],
    //m_XYZWMat[2][0] * rhs.m_XYZWMat[0][2] + m_XYZWMat[2][1] * rhs.m_XYZWMat[1][2] + m_XYZWMat[2][2] * rhs.m_XYZWMat[2][2] + m_XYZWMat[2][3] * rhs.m_XYZWMat[3][2],
    //m_XYZWMat[3][0] * rhs.m_XYZWMat[0][2] + m_XYZWMat[3][1] * rhs.m_XYZWMat[1][2] + m_XYZWMat[3][2] * rhs.m_XYZWMat[2][2] + m_XYZWMat[3][3] * rhs.m_XYZWMat[3][2],

    //m_XYZWMat[0][0] * rhs.m_XYZWMat[0][3] + m_XYZWMat[0][1] * rhs.m_XYZWMat[1][3] + m_XYZWMat[0][2] * rhs.m_XYZWMat[2][3] + m_XYZWMat[0][3] * rhs.m_XYZWMat[3][3],
    //m_XYZWMat[1][0] * rhs.m_XYZWMat[0][3] + m_XYZWMat[1][1] * rhs.m_XYZWMat[1][3] + m_XYZWMat[1][2] * rhs.m_XYZWMat[2][3] + m_XYZWMat[1][3] * rhs.m_XYZWMat[3][3],
    //m_XYZWMat[2][0] * rhs.m_XYZWMat[0][3] + m_XYZWMat[2][1] * rhs.m_XYZWMat[1][3] + m_XYZWMat[2][2] * rhs.m_XYZWMat[2][3] + m_XYZWMat[2][3] * rhs.m_XYZWMat[3][3],
    //m_XYZWMat[3][0] * rhs.m_XYZWMat[0][3] + m_XYZWMat[3][1] * rhs.m_XYZWMat[1][3] + m_XYZWMat[3][2] * rhs.m_XYZWMat[2][3] + m_XYZWMat[3][3] * rhs.m_XYZWMat[3][3] };
    float x1x4[8] = { rhs.m_XYZWMat[0][0], rhs.m_XYZWMat[1][0], rhs.m_XYZWMat[2][0],    rhs.m_XYZWMat[3][0],
                                        rhs.m_XYZWMat[0][0], rhs.m_XYZWMat[1][0], rhs.m_XYZWMat[2][0],    rhs.m_XYZWMat[3][0] };
    float y1y4[8] = { rhs.m_XYZWMat[0][1], rhs.m_XYZWMat[1][1], rhs.m_XYZWMat[2][1],    rhs.m_XYZWMat[3][1],
                                        rhs.m_XYZWMat[0][1], rhs.m_XYZWMat[1][1], rhs.m_XYZWMat[2][1],    rhs.m_XYZWMat[3][1] };
    float z1z4[8] = { rhs.m_XYZWMat[0][2], rhs.m_XYZWMat[1][2], rhs.m_XYZWMat[2][2],    rhs.m_XYZWMat[3][2],
                                        rhs.m_XYZWMat[0][2], rhs.m_XYZWMat[1][2], rhs.m_XYZWMat[2][2],    rhs.m_XYZWMat[3][2] };
    float w1w4[8] = { rhs.m_XYZWMat[0][3], rhs.m_XYZWMat[1][3], rhs.m_XYZWMat[2][3],    rhs.m_XYZWMat[3][3],
                                        rhs.m_XYZWMat[0][3], rhs.m_XYZWMat[1][3], rhs.m_XYZWMat[2][3],    rhs.m_XYZWMat[3][3] };

    ////__m256 tmp = _mm256_load_ps(x0w0);
    //__m256 rx0y0 = _mm256_mul_ps(m_XYZWMM[0], _mm256_load_ps(x0w0));
    //__m256 rz0w0 = _mm256_mul_ps(m_XYZWMM[1], _mm256_load_ps(x0w0));
    //__m256 rx1y1 = _mm256_mul_ps(m_XYZWMM[0], _mm256_load_ps(x1w1));
    //__m256 rz1w1 = _mm256_mul_ps(m_XYZWMM[1], _mm256_load_ps(x1w1));
    //__m256 rx2y2 = _mm256_mul_ps(m_XYZWMM[0], _mm256_load_ps(x2w2));
    //__m256 rz2w2 = _mm256_mul_ps(m_XYZWMM[1], _mm256_load_ps(x2w2));
    //__m256 rx3y3 = _mm256_mul_ps(m_XYZWMM[0], _mm256_load_ps(x3w3));
    //__m256 rz3w3 = _mm256_mul_ps(m_XYZWMM[1], _mm256_load_ps(x3w3));
    ////__m256 rx0y1 = _mm256_hadd_ps(rx0y0, rx1y1); __m256 rx2y3 = _mm256_hadd_ps(rx2y2, rx3y3);
    //m_XYZWMM[0] = _mm256_hadd_ps(_mm256_hadd_ps(rx0y0, rx1y1), _mm256_hadd_ps(rx2y2, rx3y3));
    ////__m256 rz0w1 = _mm256_hadd_ps(rz0w0, rz1w1); __m256 rz2w3 = _mm256_hadd_ps(rz2w2, rz3w3);
    //m_XYZWMM[1] = _mm256_hadd_ps(_mm256_hadd_ps(rz0w0, rz1w1), _mm256_hadd_ps(rz2w2, rz3w3));
    m_XYZWMM[0] = _mm256_hadd_ps(_mm256_hadd_ps(_mm256_mul_ps(m_XYZWMM[0], _mm256_load_ps(x1x4)), _mm256_mul_ps(m_XYZWMM[0], _mm256_load_ps(y1y4))),
                                                             _mm256_hadd_ps(_mm256_mul_ps(m_XYZWMM[0], _mm256_load_ps(z1z4)), _mm256_mul_ps(m_XYZWMM[0], _mm256_load_ps(w1w4))));
    //__m256 rz0w1 = _mm256_hadd_ps(rz0w0, rz1w1); __m256 rz2w3 = _mm256_hadd_ps(rz2w2, rz3w3);
    //m_XYZWMM[1] = _mm256_hadd_ps(_mm256_hadd_ps(_mm256_mul_ps(m_XYZWMM[1], _mm256_load_ps(x0w0)), rz1w1), _mm256_hadd_ps(rz2w2, rz3w3));
    m_XYZWMM[1] = _mm256_hadd_ps(_mm256_hadd_ps(_mm256_mul_ps(m_XYZWMM[1], _mm256_load_ps(x1x4)), _mm256_mul_ps(m_XYZWMM[1], _mm256_load_ps(y1y4))),
                                                             _mm256_hadd_ps(_mm256_mul_ps(m_XYZWMM[1], _mm256_load_ps(z1z4)), _mm256_mul_ps(m_XYZWMM[1], _mm256_load_ps(w1w4))));
    //std::copy(std::begin(tmp), std::end(tmp), std::begin(m_XYZW));
    return *this;
}

const Mat4f & Mat4f::operator*=(float rhs)
{
    m_XYZWMM[0] = _mm256_sub_ps(m_XYZWMM[0], _mm256_set1_ps(rhs));
    m_XYZWMM[1] = _mm256_sub_ps(m_XYZWMM[1], _mm256_set1_ps(rhs));
    return *this;
}

Vec4f Mat4f::operator*=(const Vec4f& rhs)
{
    __m256 r = _mm256_set_m128(rhs.GetMM(), rhs.GetMM());
    __m256 r1 = _mm256_mul_ps(m_XYZWMM[0], r);
    __m256 r2 = _mm256_mul_ps(m_XYZWMM[1], r);
    r = _mm256_hadd_ps(r1, r2);
    r = _mm256_hadd_ps(r, r);
    return Vec4f(r.m256_f32[0],
                             r.m256_f32[4],
                             r.m256_f32[1],
                             r.m256_f32[5]);
}

const Mat4f & Mat4f::operator/=(const Mat4f & rhs)
{
    return *this;
}

const Mat4f & Mat4f::operator/=(float rhs)
{
    m_XYZWMM[0] = _mm256_div_ps(m_XYZWMM[0], _mm256_load_ps(&rhs));
    m_XYZWMM[1] = _mm256_div_ps(m_XYZWMM[1], _mm256_load_ps(&rhs));
    return *this;
}

const Mat4f & Mat4f::operator/=(const Vec4f & rhs)
{
    return *this; 
}

const Mat4f & Mat4f::TransposeThis()
{
    __m128 row1 = _mm_load_ps(m_XYZWMat[0]);
    __m128 row2 = _mm_load_ps(m_XYZWMat[1]);
    __m128 row3 = _mm_load_ps(m_XYZWMat[2]);
    __m128 row4 = _mm_load_ps(m_XYZWMat[3]);
    _MM_TRANSPOSE4_PS(row1, row2, row3, row4);
    _mm_store_ps(m_XYZWMat[0], row1);
    _mm_store_ps(m_XYZWMat[1], row2);
    _mm_store_ps(m_XYZWMat[2], row3);
    _mm_store_ps(m_XYZWMat[3], row4);
    return *this;
}

float Mat4f::GetValue(int row, int col) const
{
    //assert(row >= GLOBAL::ZERO && row <= MAT4_ROW &&
    //             col >= GLOBAL::ZERO && row <= MAT4_COL);

    return m_XYZWMat[row][col];
}
