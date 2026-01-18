# ease.hpp
Easy to use easing functions based on https://easings.net/ for C++17


## Features
- Header only, just copy [ease.hpp](ease.hpp) to your project, include it and you're good to go
- Templated for supporting both `float` and `double` types
- `ease::get(ease::function)` function accepting an enum to choose from all available ease functions
- `ease::get(std::string_view)` function accepting a name to choose from all available ease functions
  + Many cases are supported, such as "camelCase", "snake_case", "kebab-case", "SCREAMING_CASE" and "Title Case".
    For example, "InCubic", "in-cubic", "IN_CUBIC" and "in cubic" all resolve to the same function `ease::in_cubic`.


## Usage example
```cpp
#include "ease.hpp"

float interpolate(float start, float end, float amount, ease::function f = ease::LINEAR) {
    // transform `amount` with the passed ease function
    if (auto ease_function_ptr = ease::get<float>(f)) {
        amount = ease_function_ptr(amount);
    }
    // then interpolate using the transformed amount
    return start + amount * (end - start);
}
```


## Integrating with CMake
You can integrate ease.hpp with CMake targets by adding a copy of this repository and linking with the `ease.hpp` target:
```cmake
add_subdirectory("path/to/ease.hpp")
target_link_libraries(my_awesome_target ease.hpp)
```
