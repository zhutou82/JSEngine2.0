#include "PCH.h"
#include "JSEngine/Math/Vec3.h"
const Vec3f & Vec3f::operator=(const Vec3f & rhs)
{
    m_XYZMM = rhs.m_XYZMM;
    return *this;
}

const Vec3f & Vec3f::operator+=(const Vec3f & rhs)
{ 
    m_XYZMM = _mm_add_ps(m_XYZMM, rhs.m_XYZMM);
    return *this;
}

const Vec3f & Vec3f::operator-=(const Vec3f & rhs)
{
    m_XYZMM = _mm_sub_ps(m_XYZMM, rhs.m_XYZMM);
    return *this;
}

const Vec3f & Vec3f::operator*=(const Vec3f & rhs)
{
    m_XYZMM = _mm_mul_ps(m_XYZMM, rhs.m_XYZMM);
    return *this;
}

const Vec3f & Vec3f::operator*=(float rhs)
{
    m_XYZMM = _mm_mul_ps(m_XYZMM, _mm_load_ps1(&rhs));
    return *this;
}

const Vec3f & Vec3f::operator/=(const Vec3f & rhs)
{
    m_XYZMM = _mm_div_ps(m_XYZMM, rhs.m_XYZMM);
    return *this;
}

const Vec3f & Vec3f::operator/=(float rhs)
{
    m_XYZMM = _mm_div_ps(m_XYZMM, _mm_load_ps1(&rhs));
    return *this;
}

float Vec3f::Dot(const Vec3f & rhs) const
{
    __m128 result = _mm_mul_ps(m_XYZMM, rhs.m_XYZMM);
    result = _mm_hadd_ps(result, result);
    return _mm_hadd_ps(result, result).m128_f32[0];
}

const Vec3f & Vec3f::NormalizeThis()
{
    float mag = Magnitude();
    _mm_div_ps(m_XYZMM, _mm_load_ps1(&mag));
    return *this;
}
