#include "PCH.h"
#include "JSEngine/Math/Mat3.h"

const Mat3f & Mat3f::operator=(const Mat3f & rhs)
{
    m_XYZMM[0] = rhs.m_XYZMM[0];
    m_XYZMM[1] = rhs.m_XYZMM[1];
    return *this;
}

const Mat3f & Mat3f::operator+=(const Mat3f & rhs)
{
    m_XYZMM[0] = _mm256_add_ps(m_XYZMM[0], rhs.m_XYZMM[0]);
    m_XYZMM[1] = _mm256_add_ps(m_XYZMM[1], rhs.m_XYZMM[1]);
    return *this;
};

const Mat3f & Mat3f::operator-=(const Mat3f & rhs)
{
    m_XYZMM[0] = _mm256_sub_ps(m_XYZMM[0], rhs.m_XYZMM[0]);
    m_XYZMM[1] = _mm256_sub_ps(m_XYZMM[1], rhs.m_XYZMM[1]);
    return *this;
}

const Mat3f & Mat3f::operator*=(const Mat3f & rhs)
{
    // TODO: insert return statement here
    //float result[16] = {
    //x1 = m_XYZMat[0][0] * rhs.m_XYZMat[0][0] + m_XYZMat[0][1] * rhs.m_XYZMat[1][0] + m_XYZMat[0][2] * rhs.m_XYZMat[2][0],
    //y1 = m_XYZMat[0][0] * rhs.m_XYZMat[0][1] + m_XYZMat[0][1] * rhs.m_XYZMat[1][1] + m_XYZMat[0][2] * rhs.m_XYZMat[2][1],
    //z1 = m_XYZMat[0][0] * rhs.m_XYZMat[0][2] + m_XYZMat[0][1] * rhs.m_XYZMat[1][2] + m_XYZMat[0][2] * rhs.m_XYZMat[2][2],
    //w1,
    //x2 = m_XYZMat[1][0] * rhs.m_XYZMat[0][0] + m_XYZMat[1][1] * rhs.m_XYZMat[1][0] + m_XYZMat[1][2] * rhs.m_XYZMat[2][0],
    //y2 = m_XYZMat[1][0] * rhs.m_XYZMat[0][1] + m_XYZMat[1][1] * rhs.m_XYZMat[1][1] + m_XYZMat[1][2] * rhs.m_XYZMat[2][1],
    //z2 = m_XYZMat[1][0] * rhs.m_XYZMat[0][2] + m_XYZMat[1][1] * rhs.m_XYZMat[1][2] + m_XYZMat[1][2] * rhs.m_XYZMat[2][2],
    //w2,

    //x3 = m_XYZMat[2][0] * rhs.m_XYZMat[0][0] + m_XYZMat[2][1] * rhs.m_XYZMat[1][0] + m_XYZMat[2][2] * rhs.m_XYZMat[2][0],
    //y3 = m_XYZMat[2][0] * rhs.m_XYZMat[0][1] + m_XYZMat[2][1] * rhs.m_XYZMat[1][1] + m_XYZMat[2][2] * rhs.m_XYZMat[2][1],
    //z3 = m_XYZMat[2][0] * rhs.m_XYZMat[0][2] + m_XYZMat[2][1] * rhs.m_XYZMat[1][2] + m_XYZMat[2][2] * rhs.m_XYZMat[2][2],
    //w3,
    //0.f, 0.f, 0.f, 0.f
    //};
    float x1x3[] = { rhs.m_XYZMat[0][0], rhs.m_XYZMat[1][0], rhs.m_XYZMat[2][0], 0.f,
                                     rhs.m_XYZMat[0][0], rhs.m_XYZMat[1][0], rhs.m_XYZMat[2][0], 0.f };
    float y1y3[] = { rhs.m_XYZMat[0][1], rhs.m_XYZMat[1][1], rhs.m_XYZMat[2][1], 0.f,
                                     rhs.m_XYZMat[0][1], rhs.m_XYZMat[1][1], rhs.m_XYZMat[2][1], 0.f };
    float z1z3[] = { rhs.m_XYZMat[0][2], rhs.m_XYZMat[1][2], rhs.m_XYZMat[2][2], 0.f,    
                                     rhs.m_XYZMat[0][2], rhs.m_XYZMat[1][2], rhs.m_XYZMat[2][2], 0.f };

    //__m256 rhsXYZ8 = _mm256_load_ps(tmp1);
    //__m256 rhsXYZ18 = _mm256_load_ps(tmp2);
    //__m256 rhsXYZ28 = _mm256_load_ps(tmp3);

    m_XYZMM[0] = _mm256_hadd_ps(_mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[0], _mm256_load_ps(x1x3)), _mm256_mul_ps(m_XYZMM[0], _mm256_load_ps(y1y3))),
                                                            _mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[0], _mm256_load_ps(z1z3)), _mm256_setzero_ps()));
    m_XYZMM[1] = _mm256_hadd_ps(_mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[1], _mm256_load_ps(x1x3)), _mm256_mul_ps(m_XYZMM[1], _mm256_load_ps(y1y3))),
                                                            _mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[1], _mm256_load_ps(z1z3)), _mm256_setzero_ps()));

    return *this;
}

const Mat3f & Mat3f::operator*=(float rhs)
{
    __m256 d = _mm256_set1_ps(rhs);
    m_XYZMM[0] = _mm256_mul_ps(m_XYZMM[0], d);
    m_XYZMM[1] = _mm256_mul_ps(m_XYZMM[1], d);
    return *this;
}

Vec3f Mat3f::operator*=(const Vec3f& rhs)
{
    __m256 r1 = _mm256_hadd_ps(_mm256_hadd_ps(_mm256_mul_ps(m_XYZMM[0], _mm256_set_m128(rhs.GetXMM(), rhs.GetXMM())), 
                                                                                        _mm256_mul_ps(m_XYZMM[1], _mm256_set_m128(rhs.GetXMM(), rhs.GetXMM()))),
                                                         _mm256_setzero_ps());
    return Vec3f(r1.m256_f32[0], 
                             r1.m256_f32[4], 
                             r1.m256_f32[1]);
}

const Mat3f & Mat3f::operator/=(const Mat3f & rhs)
{
    m_XYZMM[0] = _mm256_div_ps(m_XYZMM[0], rhs.m_XYZMM[0]);
    m_XYZMM[1] = _mm256_div_ps(m_XYZMM[1], rhs.m_XYZMM[1]);
    return *this;
}

const Mat3f & Mat3f::operator/=(float rhs)
{
    __m256 d = _mm256_set1_ps(rhs);
    m_XYZMM[0] = _mm256_div_ps(m_XYZMM[0], d);
    m_XYZMM[1] = _mm256_div_ps(m_XYZMM[1], d);
    return *this;
}

const Mat3f& Mat3f::TransposeThis()
{
    __m128 row1 = _mm_load_ps(m_XYZMat[0]);
    __m128 row2 = _mm_load_ps(m_XYZMat[1]);
    __m128 row3 = _mm_load_ps(m_XYZMat[2]);
    __m128 row4 = _mm_load_ps(m_XYZMat[3]);
    _MM_TRANSPOSE4_PS(row1, row2, row3, row4);
    _mm_store_ps(m_XYZMat[0], row1);
    _mm_store_ps(m_XYZMat[1], row2);
    _mm_store_ps(m_XYZMat[2], row3);
    _mm_store_ps(m_XYZMat[3], row4);
    return *this;
}

float Mat3f::GetValue(int row, int col) const
{ 
    //assert(row >= GLOBAL::ZERO && row <= MAT3_ROW &&
    //             col >= GLOBAL::ZERO && col <= MAT3_COL);
    return m_XYZMat[row][col];
}
