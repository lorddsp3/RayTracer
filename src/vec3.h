#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
  public:
    double e[3];

    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec3 operator-() const { 
        return vec3(-e[0], -e[1], -e[2]); 
    }
//  For example:
//      vec3 v(1, 2, 3);
//      vec3 result = -v;
//  produces:
//      (-1, -2, -3)
    double operator[](int i) const { return e[i]; }
//  Allows you to access the vector like an array.
//  Instead of:
//      v.e[0]
//  you can do:
//      v[0]
//  For example:
//      vec3 v(10, 20, 30);
//      cout << v[0]; //gives 10
    double& operator[](int i) { return e[i]; }
//  is the non-const version. The important difference is the &.
//  Because it returns a reference, you can modify the value:
//      v[0] = 50;

    vec3& operator+=(const vec3& v) {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }
//  a += b;
    vec3& operator*=(double t) {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }
//  v *= 5;
    vec3& operator/=(double t) {
        return *this *= 1/t;
    }
//  v /= 2;    it reuses operator*=

// *this is a pointer to the current object.
// means return the current object itself.

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    double length() const {
        return std::sqrt(length_squared());
    }
};

// point3 is just an alias for vec3, but useful for geometric clarity in the code.
using point3 = vec3;


// Vector Utility Functions

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}
// vec3 v(1,2,3);
// cout << v;

inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}
// u = (1,2,3)
// v = (4,5,6)
// u + v = (5,7,9)   // vec3 result = u + v;

inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}
// u - v

inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}
// u * v

inline vec3 operator*(double t, const vec3& v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}
// 5 * v

inline vec3 operator*(const vec3& v, double t) {
    return t * v;
}
// v * 5

inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}
// v / 5

inline double dot(const vec3& u, const vec3& v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}
// The dot product takes two vectors and returns a single number.
// Formula: U . V = Ux*Vx + Uy*Vy + Uz*Vz
// Example:
//      u = (1,2,3)
//      v = (4,5,6)
//      dot(u,v)
//      = 1×4 + 2×5 + 3×6
//      = 32

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
// The cross product takes two vectors and returns a new vector perpendicular to both.
// calculate X :  X = Uy*​Vz​ − Uz​*Vy
// calculate Y :  Y = Uz*Vx ​− Ux​*Vz
// Calculates Z:  Z = Ux*Vy ​− Uy*​Vx

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}
// A unit vector is a vector whose length is exactly 1.
// Suppose:  v = (3,4,0)
// Its length is: 5
// So: v / 5 = (0.6, 0.8, 0)
// Its length is now: 1
// This is called normalization.


#endif