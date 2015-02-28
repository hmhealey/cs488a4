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
    Vector3 normalized();

    Vector3 cross(const Vector3& other) const;
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

struct Vector4 {
    double values[];

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

struct Matrix4 {
    double values[16];

    Matrix4();
    Matrix4(double v0, double v1, double v2, double v3, double v4, double v5, double v6, double v7,
            double v8, double v9, double v10, double v11, double v12, double v13, double v14, double v15);
    Matrix4(const Matrix4& other);
    Matrix4(const Vector4 row1, const Vector4 row2, const Vector4 row3, const Vector4 row4);
    Matrix4(const double* values);

    Matrix4& operator=(const Matrix4& other);

    Vector4 getRow(size_t row) const;
    double* getRow(size_t row);

    Vector4 getColumn(size_t col) const;

    Vector4 operator[](size_t row) const;
    double* operator[](size_t row);

    Matrix4 transposed() const;
    Matrix4 inverse() const;

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

    for(size_t i = 0; i < 4; ++i) {
        Vector4 row = a.getRow(i);
		
        for(size_t j = 0; j < 4; ++j) {
            ret[i][j] = row[0] * b[0][j] + row[1] * b[1][j] + row[2] * b[2][j] + row[3] * b[3][j];
        }
    }

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

inline Colour operator*(double s, const Colour& a) {
    return Colour(s * a.r(), s * a.g(), s * a.b());
}

inline Colour operator*(const Colour& a, const Colour& b) {
    return Colour(a.r() * b.r(), a.g() * b.g(), a.b() * b.b());
}

inline Colour operator+(const Colour& a, const Colour& b) {
    return Colour(a.r() + b.r(), a.g() + b.g(), a.b() + b.b());
}

#endif // CS488_ALGEBRA_HPP
