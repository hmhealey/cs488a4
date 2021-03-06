/*****************************************
 * Harrison Healey - hmhealey - 20376857 *
 *****************************************/

#ifndef CS488_ALGEBRA_HPP
#define CS488_ALGEBRA_HPP

#include <algorithm>
#include <cmath>
#include <iosfwd>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

struct Point2D {
    static const Point2D Zero;

    double values[2];

    Point2D();
    Point2D(double x, double y);
    Point2D(const Point2D& other);

    Point2D& operator=(const Point2D& other);

    double operator[](size_t i) const;
    double& operator[](size_t i);

    inline double x() const {
        return values[0];
    }
    inline double& x() {
        return values[0];
    }

    inline double y() const {
        return values[1];
    }
    inline double& y() {
        return values[1];
    }

    bool operator==(const Point2D& other) const;
    bool operator!=(const Point2D& other) const;
};

std::ostream& operator<<(std::ostream& out, const Point2D& p);

struct Point3D {
    static const Point3D Zero;

    double values[3];

    Point3D();
    Point3D(double x, double y, double z);
    Point3D(const Point3D& other);

    Point3D& operator=(const Point3D& other);

    double& operator[](size_t idx);
    double operator[](size_t idx) const;

    inline double x() const {
        return values[0];
    }
    inline double& x() {
        return values[0];
    }

    inline double y() const {
        return values[1];
    }
    inline double& y() {
        return values[1];
    }

    inline double z() const {
        return values[2];
    }
    inline double& z() {
        return values[2];
    }

    bool operator==(const Point3D& other);
    bool operator!=(const Point3D& other);
};

std::ostream& operator<<(std::ostream& out, const Point3D& p);

struct Vector3 {
    static const Vector3 Zero;

    double values[3];

    Vector3();
    Vector3(double x, double y, double z);
    Vector3(double* array);
    Vector3(const Vector3& other);

    Vector3& operator=(const Vector3& other);
    Vector3& operator=(const double* array);

    double& operator[](size_t i);
    double operator[](size_t i) const;

    inline double x() const {
        return values[0];
    }
    inline double& x() {
        return values[0];
    }

    inline double y() const {
        return values[1];
    }
    inline double& y() {
        return values[1];
    }

    inline double z() const {
        return values[2];
    }
    inline double& z() {
        return values[2];
    }

    bool operator==(const Vector3& other);

    bool operator!=(const Vector3& other);

    double dot(const Vector3& other) const;

    double length2() const;
    double length() const;

    double normalize();
    Vector3 normalized() const;

    Vector3 cross(const Vector3& other) const;

    /** Returns the reflection vector that is produced by reflecting this one off a surface with the provided normal. **/
    Vector3 reflect(const Vector3& normal) const;
};

std::ostream& operator<<(std::ostream& out, const Vector3& v);

inline Vector3 operator*(double c, const Vector3& v) {
    return Vector3(c * v[0], c * v[1], c * v[2]);
}

inline Vector3 operator*(const Vector3& v, double c) {
    return c * v;
}

inline Vector3 operator/(const Vector3& v, double c) {
    return Vector3(v[0] / c, v[1] / c, v[2] / c);
}

inline Vector3 operator+(const Vector3& a, const Vector3& b) {
    return Vector3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

inline Point3D operator+(const Point3D& a, const Vector3& b) {
    return Point3D(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

inline Vector3 operator-(const Point3D& a, const Point3D& b) {
    return Vector3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

inline Vector3 operator-(const Vector3& a, const Vector3& b) {
    return Vector3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

inline Vector3 operator-(const Vector3& v) {
    return Vector3(-v[0], -v[1], -v[2]);
}

inline Point3D operator-(const Point3D& a, const Vector3& b) {
    return Point3D(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

struct Matrix3 {
    static const Matrix3 Identity;

    double values[9];

    Matrix3();
    Matrix3(double v0, double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8);
    Matrix3(const Matrix3& other);
    Matrix3(const Vector3& row1, const Vector3& row2, const Vector3& row3);
    Matrix3(const double* values);

    Matrix3& operator=(const Matrix3& other);

    bool operator==(const Matrix3& other) const;
    bool operator!=(const Matrix3& other) const;

    Vector3 getRow(size_t row) const;
    double* getRow(size_t row);

    Vector3 getColumn(size_t col) const;

    Vector3 operator[](size_t row) const;
    double* operator[](size_t row);

    Matrix3 transposed() const;

    double determinant() const;

    const double* begin() const;
    const double* end() const;
};

inline Matrix3 operator*(const Matrix3& a, const Matrix3& b) {
    Matrix3 ret;

    ret.values[0] = a.values[0] * b.values[0] + a.values[1] * b.values[3] + a.values[2] + b.values[6];
    ret.values[1] = a.values[0] * b.values[1] + a.values[1] * b.values[4] + a.values[2] + b.values[7];
    ret.values[2] = a.values[0] * b.values[2] + a.values[1] * b.values[5] + a.values[2] + b.values[8];

    ret.values[3] = a.values[3] * b.values[0] + a.values[4] * b.values[3] + a.values[5] + b.values[6];
    ret.values[4] = a.values[3] * b.values[1] + a.values[4] * b.values[4] + a.values[5] + b.values[7];
    ret.values[5] = a.values[3] * b.values[2] + a.values[4] * b.values[5] + a.values[5] + b.values[8];

    ret.values[6] = a.values[6] * b.values[0] + a.values[7] * b.values[3] + a.values[8] + b.values[6];
    ret.values[7] = a.values[6] * b.values[1] + a.values[7] * b.values[4] + a.values[8] + b.values[7];
    ret.values[8] = a.values[6] * b.values[2] + a.values[7] * b.values[5] + a.values[8] + b.values[8];

    return ret;
}

inline Vector3 operator*(const Matrix3& m, const Vector3& v) {
    return Vector3(v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2],
                   v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2],
                   v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2]);
}

struct Vector4 {
    static const Vector4 Zero;

    double values[4];

    Vector4();
    Vector4(double x, double y, double z, double w);
    Vector4(const Vector4& other);

    Vector4& operator=(const Vector4& other);

    double& operator[](size_t i);
    double operator[](size_t i) const;

    inline double x() const {
        return values[0];
    }
    inline double& x() {
        return values[0];
    }

    inline double y() const {
        return values[1];
    }
    inline double& y() {
        return values[1];
    }

    inline double z() const {
        return values[2];
    }
    inline double& z() {
        return values[2];
    }

    inline double w() const {
        return values[3];
    }
    inline double& w() {
        return values[3];
    }

    bool operator==(const Vector4& other) const;
    bool operator!=(const Vector4& other) const;
};

std::ostream& operator<<(const std::ostream& out, const Vector4& v);

struct Matrix4 {
    static const Matrix4 Identity;

    double values[16];

    Matrix4();
    Matrix4(double v0, double v1, double v2, double v3, double v4, double v5, double v6, double v7,
            double v8, double v9, double v10, double v11, double v12, double v13, double v14, double v15);
    Matrix4(const Matrix4& other);
    Matrix4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4);
    Matrix4(const double* values);

    Matrix4& operator=(const Matrix4& other);

    bool operator==(const Matrix4& other) const;
    bool operator!=(const Matrix4& other) const;

    Vector4 getRow(size_t row) const;
    double* getRow(size_t row);

    Vector4 getColumn(size_t col) const;

    Vector4 operator[](size_t row) const;
    double* operator[](size_t row);

    Matrix4 transposed() const;
    Matrix4 inverse() const;

    Matrix3 upper3x3() const;

    const double* begin() const;
    const double* end() const;

    static Matrix4 makeXRotation(double angle);
    static Matrix4 makeYRotation(double angle);
    static Matrix4 makeZRotation(double angle);
    static Matrix4 makeRotation(double pitch, double yaw, double roll);
    static Matrix4 makeRotation(double angle, const Vector3& axis);

    static Matrix4 makeTranslation(double x, double y, double z);

    static Matrix4 makeScaling(double x, double y, double z);

    static Matrix4 makeOrtho(double left, double right, double bottom, double top, double near, double far);
    static Matrix4 makePerspective(double fov, double aspect, double far, double near);
};

std::ostream& operator<<(std::ostream& out, const Matrix4& m);

inline Matrix4 operator*(const Matrix4& a, const Matrix4& b) {
    Matrix4 ret;

    ret.values[0] = a.values[0] * b.values[0] + a.values[1] * b.values[4] + a.values[2] * b.values[8] + a.values[3] * b.values[12];
    ret.values[1] = a.values[0] * b.values[1] + a.values[1] * b.values[5] + a.values[2] * b.values[9] + a.values[3] * b.values[13];
    ret.values[2] = a.values[0] * b.values[2] + a.values[1] * b.values[6] + a.values[2] * b.values[10] + a.values[3] * b.values[14];
    ret.values[3] = a.values[0] * b.values[3] + a.values[1] * b.values[7] + a.values[2] * b.values[11] + a.values[3] * b.values[15];

    ret.values[4] = a.values[4] * b.values[0] + a.values[5] * b.values[4] + a.values[6] * b.values[8] + a.values[7] * b.values[12];
    ret.values[5] = a.values[4] * b.values[1] + a.values[5] * b.values[5] + a.values[6] * b.values[9] + a.values[7] * b.values[13];
    ret.values[6] = a.values[4] * b.values[2] + a.values[5] * b.values[6] + a.values[6] * b.values[10] + a.values[7] * b.values[14];
    ret.values[7] = a.values[4] * b.values[3] + a.values[5] * b.values[7] + a.values[6] * b.values[11] + a.values[7] * b.values[15];

    ret.values[8] = a.values[8] * b.values[0] + a.values[9] * b.values[4] + a.values[10] * b.values[8] + a.values[11] * b.values[12];
    ret.values[9] = a.values[8] * b.values[1] + a.values[9] * b.values[5] + a.values[10] * b.values[9] + a.values[11] * b.values[13];
    ret.values[10] = a.values[8] * b.values[2] + a.values[9] * b.values[6] + a.values[10] * b.values[10] + a.values[11] * b.values[14];
    ret.values[11] = a.values[8] * b.values[3] + a.values[9] * b.values[7] + a.values[10] * b.values[11] + a.values[11] * b.values[15];

    ret.values[12] = a.values[12] * b.values[0] + a.values[13] * b.values[4] + a.values[14] * b.values[8] + a.values[15] * b.values[12];
    ret.values[13] = a.values[12] * b.values[1] + a.values[13] * b.values[5] + a.values[14] * b.values[9] + a.values[15] * b.values[13];
    ret.values[14] = a.values[12] * b.values[2] + a.values[13] * b.values[6] + a.values[14] * b.values[10] + a.values[15] * b.values[14];
    ret.values[15] = a.values[12] * b.values[3] + a.values[13] * b.values[7] + a.values[14] * b.values[11] + a.values[15] * b.values[15];

    return ret;
}

inline Vector3 operator*(const Matrix4& M, const Vector3& v) {
    return Vector3(v[0] * M[0][0] + v[1] * M[0][1] + v[2] * M[0][2],
                   v[0] * M[1][0] + v[1] * M[1][1] + v[2] * M[1][2],
                   v[0] * M[2][0] + v[1] * M[2][1] + v[2] * M[2][2]);
}

inline Point3D operator*(const Matrix4& M, const Point3D& p) {
    return Point3D(p[0] * M[0][0] + p[1] * M[0][1] + p[2] * M[0][2] + M[0][3],
                   p[0] * M[1][0] + p[1] * M[1][1] + p[2] * M[1][2] + M[1][3],
                   p[0] * M[2][0] + p[1] * M[2][1] + p[2] * M[2][2] + M[2][3]);
}

inline Vector3 transNorm(const Matrix4& M, const Vector3& n) {
    return Vector3(n[0] * M[0][0] + n[1] * M[1][0] + n[2] * M[2][0],
                   n[0] * M[0][1] + n[1] * M[1][1] + n[2] * M[2][1],
                   n[0] * M[0][2] + n[1] * M[1][2] + n[2] * M[2][2]);
}

struct Colour {
    double components[3];

    Colour();
    Colour(double c);
    Colour(double r, double g, double b);
    Colour(const Colour& other);

    Colour& operator=(const Colour& other);
    Colour& operator+=(const Colour& other);

    double operator[](size_t i) const;
    double& operator[](size_t i);

    inline double r() const {
        return components[0];
    }
    inline double& r() {
        return components[0];
    }

    inline double g() const {
        return components[1];
    }
    inline double& g() {
        return components[1];
    }

    inline double b() const {
        return components[2];
    }
    inline double& b() {
        return components[2];
    }

    Colour inverse() const;
};

std::ostream& operator<<(std::ostream& out, const Colour& c);

inline Colour operator*(double c, const Colour& a) {
    return Colour(c * a.r(), c * a.g(), c * a.b());
}

inline Colour operator*(const Colour& a, double c) {
    return c * a;
}

inline Colour operator/(const Colour& a, double c) {
    return Colour(a.r() / c, a.g() / c, a.b() / c);
}

inline Colour operator*(const Colour& a, const Colour& b) {
    return Colour(a.r() * b.r(), a.g() * b.g(), a.b() * b.b());
}

inline Colour operator+(const Colour& a, const Colour& b) {
    return Colour(a.r() + b.r(), a.g() + b.g(), a.b() + b.b());
}

#endif // CS488_ALGEBRA_HPP
