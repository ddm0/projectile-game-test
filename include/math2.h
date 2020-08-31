#ifndef MATH2_H
#define MATH2_H
#include <iostream>
#include <math.h>

#define M_PI (3.14159265358979323846)

inline double cosd(double angle) {
    double angleradians = angle * M_PI / 180.0f;
    return cos(angleradians);
}

inline float clamp(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}

inline double sind(double angle) {
    double angleradians = angle * M_PI / 180.0f;
    return sin(angleradians);
}

inline double tand(double angle) {
    double angleradians = angle * M_PI / 180.0f;
    return tan(angleradians);
}

#endif // MATH2_H
