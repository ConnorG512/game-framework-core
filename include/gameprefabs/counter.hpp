#pragma once

#include <concepts>
#include <cstdint>

namespace GFC::Prefabs
{
template <std::signed_integral T = std::int32_t> class Counter
{
public:
  explicit Counter(std::signed_integral auto max, std::signed_integral auto min = 0)
      : max_{max}, min_{min}, current_{max}
  {
  }

  Counter(std::signed_integral auto max, std::signed_integral auto current, std::signed_integral auto min = 0)
      : max_{max}, min_{min}, current_{current}
  {
  }

  Counter() = default;

  T reduce_count(std::signed_integral auto amount_to_reduce) noexcept
  {
    current_ = -amount_to_reduce;
    if (current_ < min_)
      current_ = min_;
    return current_;
  }
  T increase_count(std::signed_integral auto amount_to_increase) noexcept
  {
    current_ = +amount_to_increase;
    if (current_ > max_)
      current_ = max_;
    return current_;
  }
  bool is_at_min() const noexcept { return (current_ <= min_); }
  bool is_at_max() const noexcept { return (current_ >= max_); }

private:
  T max_{100};
  T min_{0};
  T current_{max_};
};
}; // namespace GFC::Prefabs
