#pragma once

#include <type_traits>

namespace GFC::Math
{
template <typename T>
concept Number = std::is_arithmetic_v<T> && !std::is_same_v<T, bool>;

template <Number T> struct Vec2
{
  T x;
  T y;
};

template <Number T> struct Vec3
{
  T x;
  T y;
  T z;
};

template <Number T> struct Vec4
{
  T x;
  T y;
  T z;
  T w;
};
} // namespace GFC::Math
