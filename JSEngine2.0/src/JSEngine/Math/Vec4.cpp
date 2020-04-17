#include "PCH.h"
#include "JSEngine/Math/Vec4.h"

const Vec4f& Vec4f::operator=(const Vec4f& rhs)
{
    m_XYZWMM = rhs.m_XYZWMM;
    return *this;
}

const Vec4f& Vec4f::operator+=(const Vec4f& rhs)
{
    return *this;
}

const Vec4f& Vec4f::operator-=(const Vec4f& rhs)
{
    m_XYZWMM = _mm_sub_ps(m_XYZWMM, rhs.m_XYZWMM);
    return *this;
}

const Vec4f& Vec4f::operator*=(const Vec4f& rhs)
{
    m_XYZWMM = _mm_mul_ps(m_XYZWMM, rhs.m_XYZWMM);
    return *this;
}

const Vec4f& Vec4f::operator*=(float rhs)
{
    m_XYZWMM = _mm_mul_ps(m_XYZWMM, _mm_load_ps1(&rhs));
    return *this;
}

const Vec4f& Vec4f::operator/=(const Vec4f& rhs)
{
    m_XYZWMM = _mm_div_ps(m_XYZWMM, rhs.m_XYZWMM);
    return *this;
}

const Vec4f& Vec4f::operator/=(float rhs)
{
    m_XYZWMM = _mm_div_ps(m_XYZWMM, _mm_load_ps1(&rhs));
    return *this;
}

const Vec4f& Vec4f::NormalizeThis()
{
    float m = Magnitude();
    m_XYZWMM = _mm_div_ps(m_XYZWMM, _mm_load_ps1(&m));
    return *this;
}

float Vec4f::Dot(const Vec4f& rhs) const
{
    __m128 result = _mm_mul_ps(m_XYZWMM, rhs.m_XYZWMM);
    result = _mm_hadd_ps(result, result);
    return _mm_hadd_ps(result, result).m128_f32[0];
}
