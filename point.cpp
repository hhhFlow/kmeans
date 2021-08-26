

#include "point.h"
#include <cmath>


point point::operator+(const point &right) const {
    return point(x_ + right.x_, y_ + right.y_);
}

point point::operator-(const point &right) const {
    return point(x_ - right.x_, y_ - right.y_);
}

double point::operator*(const point &right) const {
    return static_cast<long long int>(x_) * right.x_ + static_cast<long long int>(y_) * right.y_;
}

point point::operator*(int k) const {
    return point(k * x_, k * y_);
}

double point::operator^(const point &right) const {
    return static_cast<long long int>(x_) * right.y_ - static_cast<long long int>(right.x_) * y_;
}

bool point::operator==(const point &right) const {
    return (x_ == right.x_) && (y_ == right.y_);
}

bool point::operator!=(const point &right) const {
    return (x_ != right.x_) || (y_ != right.y_);
}

bool point::operator<(const point &right) const {
    if (y_ == right.y_) {
        return x_ < right.x_;
    }
    return y_ < right.y_;
}

point::operator bool () const {
    return !isNull();
}


void point::clear() {
    x_ = 0;
    y_ = 0;
}

double point::len() const {
    return std::sqrt(len2());
}

long long int point::len2() const {
    return static_cast<long long int>(x_) * x_ + static_cast<long long int>(y_) * y_;
}

bool point::isNull() const {
    if (0 == x_ && 0 == y_) {
        return true;
    }
    return false;
}