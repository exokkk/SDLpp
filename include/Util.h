#pragma once
#include <iostream>

namespace sdl {
typedef SDL_Rect Rect;

inline std::ostream &operator<<(std::ostream &os, const Rect &rect) {
    os << "[" << rect.x << ", "
       << rect.y << ", "
       << rect.w << ", "
       << rect.h << std::endl;
    return os;
}

inline void Throw() {
    std::cout << SDL_GetError() << std::endl;
    throw 0;
}
}
