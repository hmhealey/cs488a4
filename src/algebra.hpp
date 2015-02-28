/*****************************************
 * Harrison Healey - hmhealey - 20376857 *
 *****************************************/

#ifndef CS488_ALGEBRA_HPP
#define CS488_ALGEBRA_HPP

#include <iostream>
#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class Point2D
{
public:
  Point2D()
  {
    v_[0] = 0.0;
    v_[1] = 0.0;
  }
  Point2D(double x, double y)
  { 
    v_[0] = x;
    v_[1] = y;
  }
  Point2D(const Point2D& other)
  {
    v_[0] = other.v_[0];
    v_[1] = other.v_[1];
  }

  Point2D& operator =(const Point2D& other)
  {
    v_[0] = other.v_[0];
    v_[1] = other.v_[1];
    return *this;
  }

  double& operator[](size_t idx) 
  {
    return v_[ idx ];
  }
  double operator[](size_t idx) const 
  {
    return v_[ idx ];
  }

    double x() const {
        return v_[0];
    }
    double& x() {
        return v_[0];
    }

    double y() const {
        return v_[1];
    }
    double& y() {
        return v_[1];
    }

    bool operator==(const Point2D& other) {
        return other.x() == x() && other.y() == y();
    }

    bool operator!=(const Point2D& other) {
        return !(*this == other);
    }

private:
  double v_[2];
};

class Point3D
{
public:
  Point3D()
  {
    v_[0] = 0.0;
    v_[1] = 0.0;
    v_[2] = 0.0;
  }
  Point3D(double x, double y, double z)
  { 
    v_[0] = x;
    v_[1] = y;
    v_[2] = z;
  }
  Point3D(const Point3D& other)
  {
    v_[0] = other.v_[0];
    v_[1] = other.v_[1];
    v_[2] = other.v_[2];
  }

  Point3D& operator =(const Point3D& other)
  {
    v_[0] = other.v_[0];
    v_[1] = other.v_[1];
    v_[2] = other.v_[2];
    return *this;
  }

  double& operator[](size_t idx) 
  {
    return v_[ idx ];
  }
  double operator[](size_t idx) const 
  {
    return v_[ idx ];
  }

    double x() const {
        return v_[0];
    }
    double& x() {
        return v_[0];
    }

    double y() const {
        return v_[1];
    }
    double& y() {
        return v_[1];
    }

    double z() const {
        return v_[2];
    }
    double& z() {
        return v_[2];
    }

    bool operator==(const Point3D& other) {
        return other.x() == x() && other.y() == y() && other.z() == z();
    }

    bool operator!=(const Point3D& other) {
        return !(*this == other);
    }

private:
  double v_[3];
};

class Vector3
{
public:
  Vector3()
  {
    v_[0] = 0.0;
    v_[1] = 0.0;
    v_[2] = 0.0;
  }
  Vector3(double x, double y, double z)
  { 
    v_[0] = x;
    v_[1] = y;
    v_[2] = z;
  }
  Vector3(float* array)
  {
    v_[0] = array[0];
    v_[1] = array[1];
    v_[2] = array[2];
  }
  Vector3(const Vector3& other)
  {
    v_[0] = other.v_[0];
    v_[1] = other.v_[1];
    v_[2] = other.v_[2];
  }

  Vector3& operator =(const Vector3& other)
  {
    v_[0] = other.v_[0];
    v_[1] = other.v_[1];
    v_[2] = other.v_[2];
    return *this;
  }
  Vector3& operator=(const float* array)
  {
    v_[0] = array[0];
    v_[1] = array[1];
    v_[2] = array[2];
    return *this;
  }

  double& operator[](size_t idx) 
  {
    return v_[ idx ];
  }
  double operator[](size_t idx) const 
  {
    return v_[ idx ];
  }

    double x() const {
        return v_[0];
    }
    double& x() {
        return v_[0];
    }

    double y() const {
        return v_[1];
    }
    double& y() {
        return v_[1];
    }

    double z() const {
        return v_[2];
    }
    double& z() {
        return v_[2];
    }

    bool operator==(const Vector3& other) {
        return other.x() == x() && other.y() == y() && other.z() == z();
    }

    bool operator!=(const Vector3& other) {
        return !(*this == other);
    }

  double dot(const Vector3& other) const
  {
    return v_[0]*other.v_[0] + v_[1]*other.v_[1] + v_[2]*other.v_[2];
  }

  double length2() const
  {
    return v_[0]*v_[0] + v_[1]*v_[1] + v_[2]*v_[2];
  }
  double length() const
  {
    return sqrt(length2());
  }

  double normalize();
  Vector3 normalized();

  Vector3 cross(const Vector3& other) const
  {
    return Vector3(
                    v_[1]*other[2] - v_[2]*other[1],
                    v_[2]*other[0] - v_[0]*other[2],
                    v_[0]*other[1] - v_[1]*other[0]);
  }

private:
  double v_[3];
};

inline Vector3 operator*(double s, const Vector3& v)
{
  return Vector3(s*v[0], s*v[1], s*v[2]);
}

inline Vector3 operator*(const Vector3& v, double s)
{
  return s * v;
}

inline Vector3 operator/(const Vector3& v, double s)
{
  return Vector3(v[0] / s, v[1] / s, v[2] / s);
}

inline Vector3 operator +(const Vector3& a, const Vector3& b)
{
  return Vector3(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}

inline Point3D operator +(const Point3D& a, const Vector3& b)
{
  return Point3D(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}

inline Vector3 operator -(const Point3D& a, const Point3D& b)
{
  return Vector3(a[0]-b[0], a[1]-b[1], a[2]-b[2]);
}

inline Vector3 operator -(const Vector3& a, const Vector3& b)
{
  return Vector3(a[0]-b[0], a[1]-b[1], a[2]-b[2]);
}

inline Vector3 operator -(const Vector3& a)
{
  return Vector3(-a[0], -a[1], -a[2]);
}

inline Point3D operator -(const Point3D& a, const Vector3& b)
{
  return Point3D(a[0]-b[0], a[1]-b[1], a[2]-b[2]);
}

inline Vector3 cross(const Vector3& a, const Vector3& b) 
{
  return a.cross(b);
}

inline std::ostream& operator <<(std::ostream& os, const Point2D& p)
{
  return os << "p<" << p[0] << "," << p[1] << ">";
}

inline std::ostream& operator <<(std::ostream& os, const Point3D& p)
{
  return os << "p<" << p[0] << "," << p[1] << "," << p[2] << ">";
}

inline std::ostream& operator <<(std::ostream& os, const Vector3& v)
{
  return os << "v<" << v[0] << "," << v[1] << "," << v[2] << ">";
}

struct Matrix4;

class Vector4D
{
public:
  Vector4D()
  {
    v_[0] = 0.0;
    v_[1] = 0.0;
    v_[2] = 0.0;
    v_[3] = 0.0;
  }
  Vector4D(double x, double y, double z, double w)
  { 
    v_[0] = x;
    v_[1] = y;
    v_[2] = z;
    v_[3] = w;
  }
  Vector4D(const Vector4D& other)
  {
    v_[0] = other.v_[0];
    v_[1] = other.v_[1];
    v_[2] = other.v_[2];
    v_[3] = other.v_[3];
  }

  Vector4D& operator =(const Vector4D& other)
  {
    v_[0] = other.v_[0];
    v_[1] = other.v_[1];
    v_[2] = other.v_[2];
    v_[3] = other.v_[3];
    return *this;
  }

  double& operator[](size_t idx) 
  {
    return v_[ idx ];
  }
  double operator[](size_t idx) const 
  {
    return v_[ idx ];
  }

    double x() const {
        return v_[0];
    }
    double& x() {
        return v_[0];
    }

    double y() const {
        return v_[1];
    }
    double& y() {
        return v_[1];
    }

    double z() const {
        return v_[2];
    }
    double& z() {
        return v_[2];
    }

    double w() const {
        return v_[3];
    }
    double& w() {
        return v_[3];
    }

    bool operator==(const Vector4D& other) {
        return other.x() == x() && other.y() == y() && other.z() == z() && other.w() == w();
    }

    bool operator!=(const Vector4D& other) {
        return !(*this == other);
    }

private:
  double v_[4];
};

struct Matrix4
{
  double values[16];

  Matrix4()
  {
    // Construct an identity matrix
    std::fill(values, values+16, 0.0);
    values[0] = 1.0;
    values[5] = 1.0;
    values[10] = 1.0;
    values[15] = 1.0;
  }
    Matrix4(double v0, double v1, double v2, double v3, double v4, double v5, double v6, double v7,
            double v8, double v9, double v10, double v11, double v12, double v13, double v14, double v15) {
        values[0] = v0;
        values[1] = v1;
        values[2] = v2;
        values[3] = v3;
        values[4] = v4;
        values[5] = v5;
        values[6] = v6;
        values[7] = v7;
        values[8] = v8;
        values[9] = v9;
        values[10] = v10;
        values[11] = v11;
        values[12] = v12;
        values[13] = v13;
        values[14] = v14;
        values[15] = v15;
    }
  Matrix4(const Matrix4& other)
  {
    std::copy(other.values, other.values+16, values);
  }
  Matrix4(const Vector4D row1, const Vector4D row2, const Vector4D row3, 
             const Vector4D row4)
  {
    values[0] = row1[0]; 
    values[1] = row1[1]; 
    values[2] = row1[2]; 
    values[3] = row1[3]; 

    values[4] = row2[0]; 
    values[5] = row2[1]; 
    values[6] = row2[2]; 
    values[7] = row2[3]; 

    values[8] = row3[0]; 
    values[9] = row3[1]; 
    values[10] = row3[2]; 
    values[11] = row3[3]; 

    values[12] = row4[0]; 
    values[13] = row4[1]; 
    values[14] = row4[2]; 
    values[15] = row4[3]; 
  }
  Matrix4(double *vals)
  {
    std::copy(vals, vals + 16, (double*)values);
  }

  Matrix4& operator=(const Matrix4& other)
  {
    std::copy(other.values, other.values+16, values);
    return *this;
  }

  Vector4D getRow(size_t row) const
  {
    return Vector4D(values[4*row], values[4*row+1], values[4*row+2], values[4*row+3]);
  }
  double *getRow(size_t row) 
  {
    return (double*)values + 4*row;
  }

  Vector4D getColumn(size_t col) const
  {
    return Vector4D(values[col], values[4+col], values[8+col], values[12+col]);
  }

  Vector4D operator[](size_t row) const
  {
    return getRow(row);
  }
  double *operator[](size_t row) 
  {
    return getRow(row);
  }

  Matrix4 transposed() const
  {
    return Matrix4(getColumn(0), getColumn(1), 
                      getColumn(2), getColumn(3));
  }
  Matrix4 inverse() const;

  const double *begin() const
  {
    return (double*)values;
  }
  const double *end() const
  {
    return begin() + 16;
  }
		
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

inline Matrix4 operator *(const Matrix4& a, const Matrix4& b)
{
  Matrix4 ret;

  for(size_t i = 0; i < 4; ++i) {
    Vector4D row = a.getRow(i);
		
    for(size_t j = 0; j < 4; ++j) {
      ret[i][j] = row[0] * b[0][j] + row[1] * b[1][j] + 
        row[2] * b[2][j] + row[3] * b[3][j];
    }
  }

  return ret;
}

inline Vector3 operator *(const Matrix4& M, const Vector3& v)
{
  return Vector3(
                  v[0] * M[0][0] + v[1] * M[0][1] + v[2] * M[0][2],
                  v[0] * M[1][0] + v[1] * M[1][1] + v[2] * M[1][2],
                  v[0] * M[2][0] + v[1] * M[2][1] + v[2] * M[2][2]);
}

inline Point3D operator *(const Matrix4& M, const Point3D& p)
{
  return Point3D(
                 p[0] * M[0][0] + p[1] * M[0][1] + p[2] * M[0][2] + M[0][3],
                 p[0] * M[1][0] + p[1] * M[1][1] + p[2] * M[1][2] + M[1][3],
                 p[0] * M[2][0] + p[1] * M[2][1] + p[2] * M[2][2] + M[2][3]);
}

inline Vector3 transNorm(const Matrix4& M, const Vector3& n)
{
  return Vector3(
                  n[0] * M[0][0] + n[1] * M[1][0] + n[2] * M[2][0],
                  n[0] * M[0][1] + n[1] * M[1][1] + n[2] * M[2][1],
                  n[0] * M[0][2] + n[1] * M[1][2] + n[2] * M[2][2]);
}

inline std::ostream& operator <<(std::ostream& os, const Matrix4& M)
{
  return os << "[" << M[0][0] << " " << M[0][1] << " " 
            << M[0][2] << " " << M[0][3] << "]" << std::endl
            << "[" << M[1][0] << " " << M[1][1] << " " 
            << M[1][2] << " " << M[1][3] << "]" << std::endl
            << "[" << M[2][0] << " " << M[2][1] << " " 
            << M[2][2] << " " << M[2][3] << "]" << std::endl
            << "[" << M[3][0] << " " << M[3][1] << " " 
            << M[3][2] << " " << M[3][3] << "]";
}

class Colour
{
public:
    Colour() : r_(1.0), g_(1.0), b_(1.0) { }
  Colour(double r, double g, double b)
    : r_(r)
    , g_(g)
    , b_(b)
  {}
  Colour(double c)
    : r_(c)
    , g_(c)
    , b_(c)
  {}
  Colour(const Colour& other)
    : r_(other.r_)
    , g_(other.g_)
    , b_(other.b_)
  {}

  Colour& operator =(const Colour& other)
  {
    r_ = other.r_;
    g_ = other.g_;
    b_ = other.b_;
    return *this;
  }

    double operator[](int i) const {
        switch(i) {
        case 0:
            return r_;
        case 1:
            return g_;
        case 2:
            return b_;
        default:
            return -1;
        }
    }

  double R() const 
  { 
    return r_;
  }
  double G() const 
  { 
    return g_;
  }
  double B() const 
  { 
    return b_;
  }

    Colour inverse() const;

private:
  double r_;
  double g_;
  double b_;
};

inline Colour operator *(double s, const Colour& a)
{
  return Colour(s*a.R(), s*a.G(), s*a.B());
}

inline Colour operator *(const Colour& a, const Colour& b)
{
  return Colour(a.R()*b.R(), a.G()*b.G(), a.B()*b.B());
}

inline Colour operator +(const Colour& a, const Colour& b)
{
  return Colour(a.R()+b.R(), a.G()+b.G(), a.B()+b.B());
}

inline std::ostream& operator <<(std::ostream& os, const Colour& c)
{
  return os << "c<" << c.R() << "," << c.G() << "," << c.B() << ">";
}

#endif // CS488_ALGEBRA_HPP
