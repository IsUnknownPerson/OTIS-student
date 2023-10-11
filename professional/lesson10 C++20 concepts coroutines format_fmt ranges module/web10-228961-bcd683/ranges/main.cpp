#include <ranges>
#include <algorithm>
#include <vector>
#include <iostream>

bool is_even(int x) { return x % 2 == 0; }

int main() {
    std::vector v {1, 2, 3};
    auto it0 = std::find(v.begin(), v.end(), 3);

    auto it1 = std::ranges::find(v, 3);

    for (int x: v | std::ranges::views::filter(is_even) | std::ranges::views::take(10)) {
        std::cout << x << "\n";
    }

    for (auto x: v | std::ranges::views::reverse) {
        std::cout << x << "\n";
    }
}
