#pragma once

namespace my {
template <typename T>
void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}
}  // namespace my
