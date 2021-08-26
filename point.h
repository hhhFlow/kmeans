
#ifndef __POINT_H__
#define __POINT_H__

#include <string>

class point {

public:
    point():x_(0), y_(0) {}
    point(int x, int y):x_(x), y_(y) {}
    point(long long int x, long long int y):x_(x), y_(y) {}
    point(double x, double y):x_(x), y_(y) {}
    point(const point &obj) {
        x_ = obj.x_;
        y_ = obj.y_;
    }
    point& operator=(const point &right) = default;
    point operator+(const point &right) const;
    point operator-(const point &right) const;
    double operator*(const point &right) const; // 点乘
    point operator*(int k) const;
    double operator^(const point &right) const; // 叉乘
    bool operator==(const point &right) const;
    bool operator!=(const point &right) const;
    bool operator<(const point &right) const;
    operator bool () const;
    void clear();
    double len() const; // 长度
    long long int len2() const; // 长度的平方
    bool isNull() const;
    std::string ShortDebugString() const {
        return "{x = " + std::to_string(x_) + ", y = " + std::to_string(y_) + "}";
    }

public:
    // int x_, y_;
    long long int x_, y_;
};

#endif //__POINT_H__