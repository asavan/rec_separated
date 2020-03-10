#include <cassert>
#include <cstddef>
#include <limits>

template <typename ContainerType>
constexpr int size_as_int(const ContainerType &c) {
    const auto size = c.size();  // if no auto, use `typename ContainerType::size_type`
    assert(size <= static_cast<std::size_t>(std::numeric_limits<int>::max()));
    return static_cast<int>(size);
}
