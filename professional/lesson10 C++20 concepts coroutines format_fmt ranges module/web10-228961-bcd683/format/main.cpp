#include <format>
#include <iostream>
#include <vector>

struct point {
  double x, y;
};

template <class CharT>
struct std::formatter<point, CharT> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

  // Define format() by calling the base class implementation with the wrapped
  // value
  template <class FormatContext>
  auto format(point p, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "({}, {})", p.x, p.y);
  }
};

int main() {
  std::cout << std::format("Number: {}", 1) << "\n";
  std::cout << std::format("Point: {}", point{3, 5}) << "\n";
  
  std::string s = "runtime {}\n";
  //std::format(s, 3);
  std::cout << std::vformat(s, std::make_format_args(3));
}
