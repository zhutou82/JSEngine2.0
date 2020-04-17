#pragma once
#include "JSEngine/Math/JSMath.h"
#include "JSEngine/Math/Vec4.h"
class Mat4f
{
    public:
    constexpr static int MAT4_ROW = 4;
    constexpr static int MAT4_COL = 4;

    Mat4f(float x1, float x2, float x3, float x4,
                float y1, float y2, float y3, float y4,
                float z1, float z2, float z3, float z4, 
                float w1, float w2, float w3, float w4 ) 
                :
                m_XYZW {x1, x2, x3, x4,
                                y1, y2, y3, y4,
                                z1, z2, z3, z4,
                                w1, w2, w3, w4} {}
    Mat4f(float x = 0.f)
    :
    m_XYZW{ x, x, x, x,
                    x, x, x, x,
                    x, x, x, x,
                    x, x, x, x } {}
    
    Mat4f(const Mat4f& rhs) {*this = rhs;}
    const Mat4f& operator=(const Mat4f& rhs);
    const Mat4f& operator+=(const Mat4f& rhs);
    const Mat4f& operator-=(const Mat4f& rhs);
    const Mat4f& operator*=(const Mat4f& rhs);
    const Mat4f& operator*=(float rhs);
    Vec4f operator*=(const Vec4f& rhs);
    const Mat4f& operator/=(const Mat4f& rhs);
    const Mat4f& operator/=(float rhs);
    const Mat4f& operator/=(const Vec4f& rhs);
    const Mat4f& TransposeThis();
    float GetValue(int row, int col) const;

    friend bool operator==(const Mat4f& lhs, const Mat4f& rhs) {    return _mm256_movemask_ps(_mm256_cmp_ps(lhs.m_XYZWMM[0], rhs.m_XYZWMM[0], _CMP_EQ_OQ)) == 0xFF && 
                                                                                                                                             _mm256_movemask_ps(_mm256_cmp_ps(lhs.m_XYZWMM[1], rhs.m_XYZWMM[1], _CMP_EQ_OQ)) == 0xFF; }
    friend std::ostream& operator<<(std::ostream& os, const Mat4f& rhs)
    {
      // os << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZWMat[0][0] << GLOBAL::COMMA << rhs.m_XYZWMat[0][1] << GLOBAL::COMMA << rhs.m_XYZWMat[0][2] << GLOBAL::COMMA << rhs.m_XYZWMat[0][3] << GLOBAL::SQUARE_BRACKET_C <<    GLOBAL::NEW_LINE
      //      << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZWMat[1][0] << GLOBAL::COMMA << rhs.m_XYZWMat[1][1] << GLOBAL::COMMA << rhs.m_XYZWMat[1][2] << GLOBAL::COMMA << rhs.m_XYZWMat[1][3] << GLOBAL::SQUARE_BRACKET_C << GLOBAL::NEW_LINE
      //      << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZWMat[2][0] << GLOBAL::COMMA << rhs.m_XYZWMat[2][1] << GLOBAL::COMMA << rhs.m_XYZWMat[2][2] << GLOBAL::COMMA << rhs.m_XYZWMat[2][3] << GLOBAL::SQUARE_BRACKET_C << GLOBAL::NEW_LINE
      //      << GLOBAL::SQUARE_BRACKET_O << rhs.m_XYZWMat[3][0] << GLOBAL::COMMA << rhs.m_XYZWMat[3][1] << GLOBAL::COMMA << rhs.m_XYZWMat[3][2] << GLOBAL::COMMA << rhs.m_XYZWMat[3][3] << GLOBAL::SQUARE_BRACKET_C;
        return os;
    }
    private:
    union {
        __m256 m_XYZWMM[2];
        float m_XYZW[16];
        float m_XYZWMat[4][4];
    };
};

static Mat4f operator+(Mat4f lhs, const Mat4f& rhs) { return lhs += rhs; }
static Mat4f operator-(Mat4f lhs, const Mat4f& rhs) { return lhs -= rhs; }
static Mat4f operator*(Mat4f lhs, const Mat4f& rhs) { return lhs *= rhs; }
static Mat4f operator*(Mat4f lhs, float rhs) { return lhs *= rhs; }
static Vec4f operator*(Mat4f lhs, const Vec4f& rhs) { return lhs *= rhs; }
static Mat4f operator/(Mat4f lhs, const Mat4f& rhs) { return lhs /= rhs; }
static Mat4f operator/(Mat4f lhs, float rhs) { return lhs /= rhs; }
static Mat4f operator/(Mat4f lhs, const Vec4f& rhs) { return lhs /= rhs; }

namespace Mat4
{
    static Mat4f Transpose(Mat4f rhs) { return rhs.TransposeThis(); }
}