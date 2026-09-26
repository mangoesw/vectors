#include <cmath>
#include <cstdio>
#include <iostream>
#include <limits>
#include <numbers>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

constexpr int NUM_VECTORS{90};

class VectorComponents {
public:
  const double x, y;

  VectorComponents(double x, double y) : x(x), y(y) {}
};

enum class Direction {
  east, north, west, south
};

Direction char_to_direction(char direction_char) {
  using enum Direction;
  switch (direction_char) {
    case 'E': return east;
    case 'N': return north;
    case 'W': return west;
    case 'S': return south;
  }
  throw std::invalid_argument("Received an unexpected direction character");
}

double deg_to_rad(double degrees) {
  return degrees * std::numbers::pi / 180.0;
}

VectorComponents parse_line() {
  double magnitude, degrees;
  char ref_char, direction_char;
  std::string input;
  std::getline(std::cin, input);
  if (std::sscanf(input.c_str(), "| %*d | %lf | [%c%lf°%c] |", &magnitude, &ref_char, &degrees, &direction_char) != 4) {
    std::sscanf(input.c_str(), "| %*d | %lf | [%c] |", &magnitude, &ref_char);
    direction_char = ref_char;
    degrees = 0;
  }
  std::cout << magnitude << ref_char << degrees << direction_char << '\n';

  Direction reference{char_to_direction(ref_char)};
  Direction direction{char_to_direction(direction_char)};
  double radians{0};
  using enum Direction;
  using namespace std::numbers;
  switch (reference) {
    case north: radians += pi / 2.0; break;
    case west: radians += pi; break;
    case south: radians += 3 * pi / 2.0;
  }
  radians += ((std::to_underlying(direction) > std::to_underlying(reference)) ? deg_to_rad(degrees) : -deg_to_rad(degrees));
  double x{magnitude * std::cos(radians)}, y{magnitude * std::sin(radians)};
  std::cout << radians * 180.0 / pi << ';' << radians << '\n' << x << ',' << y << "\n\n";
  return VectorComponents{x, y};
}

int main() {
  std::vector<VectorComponents> vectors{};
  vectors.reserve(NUM_VECTORS);
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  for (int i{0}; i < NUM_VECTORS; ++i) {
    vectors.emplace_back(parse_line());
  }
}
