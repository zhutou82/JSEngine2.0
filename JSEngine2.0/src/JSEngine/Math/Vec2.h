#pragma once
#include "JSEngine/Math/JSMath.h"
class Vec2f
{ 
public:
  //constructor
  Vec2f(float x, float y) : m_XY { x, y } {}
  Vec2f(float x = 0.f) : m_XY {x, x} {}

  Vec2f(const Vec2f& rhs) { *this = rhs; }
  //operator overloading
  const Vec2f& operator+=(const Vec2f& rhs);
  const Vec2f  operator-=(const Vec2f& rhs);
  const Vec2f& operator*=(const Vec2f& rhs);
  const Vec2f& operator*=(float rhs);
  const Vec2f& operator=(const Vec2f& rhs);
  const Vec2f& operator/=(const Vec2f& rhs);  
  const Vec2f& operator/=(float rhs);
  /*  
  An ordered comparison checks if neither operand is NaN.
  Conversely, an unordered comparison checks if either operand is a NaN.

  Signaling (S) vs non-signaling (Q for quiet) will
  determine whether an exception is raised if an operand contains a NaN.
  */
  //bool         operator==(const Vec2f& rhs) const { return  _mm_movemask_ps(_mm_cmp_ps(m_XYMM, rhs.m_XYMM, _CMP_EQ_OQ)) == 0x0F; }
  float        Dot(const Vec2f& rhs) const;
  const float* GetValueInPtr() const {return m_XY; }
  void         SetValue(int index, float v) { m_XY[index] = v; }
  float        Magnitude() const { return sqrt(Dot(*this)); }
  const Vec2f& NormalizeThis();
  const float GetX() const { return m_XY[0]; }
  const float GetY() const { return m_XY[1]; }

  friend bool operator==(const Vec2f& lhs, const Vec2f& rhs) { return _mm_movemask_ps(_mm_cmpeq_ps(lhs.m_XYMM, rhs.m_XYMM)) == 0x0F; }
  friend std::ostream& operator<<(std::ostream& os, const Vec2f& rhs) { os << "(" << rhs.m_XY[0] << ", " << rhs.m_XY[1] << ")"; return os;}
private:
  union { __m128 m_XYMM; float m_XY[4]; };
};
class Vec2i
{
  public:
  Vec2i(int x, int y) : m_XY {x, y} {}
  Vec2i(int x = 0) : m_XY{ x, x } {}
  //operator overloading
  const Vec2i& operator+=(const Vec2i& rhs) { m_XY[0] += rhs.m_XY[0]; m_XY[1] += rhs.m_XY[1]; return *this;}
  const Vec2i& operator-=(const Vec2i& rhs) { m_XY[0] -= rhs.m_XY[0]; m_XY[1] -= rhs.m_XY[1]; return *this;}
  const Vec2i& operator*=(const Vec2i& rhs) { m_XY[0] *= rhs.m_XY[0]; m_XY[1] *= rhs.m_XY[1]; return *this;}
  const Vec2i& operator=(const Vec2i& rhs)  { m_XY[0] = rhs.m_XY[0]; m_XY[1] = rhs.m_XY[1]; return *this; }
  bool operator==(const Vec2i& rhs)         { return m_XY[0] == rhs.m_XY[0] && m_XY[1] == rhs.m_XY[1]; }
  int Dot(const Vec2i& rhs)                 { return m_XY[0] * rhs.m_XY[0] + m_XY[1] * rhs.m_XY[1]; }
  int GetX() const {return m_XY[0]; }
  int GetY() const {return m_XY[1]; }
  friend std::ostream& operator<<(std::ostream& os, const Vec2i& rhs){ os << "(" << rhs.m_XY[0] << ", " << rhs.m_XY[1] << ")"; return os;}
  private:
  int m_XY[2];
};

static Vec2f operator+(Vec2f lhs, const Vec2f& rhs) { return lhs += rhs; }
static Vec2f operator-(Vec2f lhs, const Vec2f& rhs) { return lhs -= rhs; }
static Vec2f operator*(Vec2f lhs, const Vec2f& rhs) { return lhs *= rhs; }
static Vec2f operator*(Vec2f lhs, float rhs) { return lhs *= rhs; }
static Vec2f operator/(Vec2f lhs, const Vec2f& rhs) { return lhs /= rhs; }
static Vec2f operator/(Vec2f lhs, float rhs) { return lhs /= rhs; }

namespace Vec2
{
  static float Dot(const Vec2f& lhs, const Vec2f& rhs) { return lhs.Dot(rhs); }
  static Vec2f Normalize(Vec2f rhs) { return rhs.NormalizeThis(); }
}