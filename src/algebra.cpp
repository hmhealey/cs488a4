/*****************************************
 * Harrison Healey - hmhealey - 20376857 *
 *****************************************/

#include "algebra.hpp"

#include <iostream>

using namespace std;

// --------------- Point2D ---------------

const Point2D Point2D::Zero;

Point2D::Point2D() : Point2D(0, 0) { }

Point2D::Point2D(double x, double y) {
    values[0] = x;
    values[1] = y;
}

Point2D::Point2D(const Point2D& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
}

Point2D& Point2D::operator=(const Point2D& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];

    return *this;
}

double Point2D::operator[](size_t i) const {
    return values[i];
}

double& Point2D::operator[](size_t i) {
    return values[i];
}

bool Point2D::operator==(const Point2D& other) const {
    return values[0] == other.values[0] && values[1] == other.values[1];
}

bool Point2D::operator!=(const Point2D& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& out, const Point2D& p) {
    return out << "p<" << p[0] << "," << p[1] << ">";
}

// --------------- Point3D ---------------

const Point3D Point3D::Zero;

Point3D::Point3D() : Point3D(0, 0, 0) { }

Point3D::Point3D(double x, double y, double z) {
    values[0] = x;
    values[1] = y;
    values[2] = z;
}

Point3D::Point3D(const Point3D& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];
}

Point3D& Point3D::operator=(const Point3D& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];

    return *this;
}

double Point3D::operator[](size_t i) const {
    return values[i];
}

double& Point3D::operator[](size_t i) {
    return values[i];
}

bool Point3D::operator==(const Point3D& other) {
    return values[0] == other.values[0] && values[1] == other.values[1] && values[2] == other.values[2];
}

bool Point3D::operator!=(const Point3D& other) {
    return !(*this == other);
}

ostream& operator<<(ostream& out, const Point3D& p) {
    return out << "p<" << p[0] << "," << p[1] << "," << p[2] << ">";
}

// --------------- Vector3 ---------------

const Vector3 Vector3::Zero;

Vector3::Vector3() : Vector3(0, 0, 0) { }

Vector3::Vector3(double x, double y, double z) { 
    values[0] = x;
    values[1] = y;
    values[2] = z;
}

Vector3::Vector3(double* array) {
    values[0] = array[0];
    values[1] = array[1];
    values[2] = array[2];
}

Vector3::Vector3(const Vector3& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];
}

Vector3& Vector3::operator=(const Vector3& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];
    return *this;
}

Vector3& Vector3::operator=(const double* array) {
    values[0] = array[0];
    values[1] = array[1];
    values[2] = array[2];
    return *this;
}

double& Vector3::operator[](size_t i) {
    return values[i];
}

double Vector3::operator[](size_t i) const {
    return values[i];
}

bool Vector3::operator==(const Vector3& other) {
    return values[0] == other.values[0] && values[1] == other.values[1] && values[2] == other.values[2];
}

bool Vector3::operator!=(const Vector3& other) {
    return !(*this == other);
}

double Vector3::dot(const Vector3& other) const {
    return values[0] * other.values[0] + values[1] * other.values[1] + values[2] * other.values[2];
}

double Vector3::length2() const {
    return dot(*this);
}

double Vector3::length() const {
    return sqrt(length2());
}

double Vector3::normalize() {
    double denom = 1.0;
    double x = (values[0] > 0.0) ? values[0] : -values[0];
    double y = (values[1] > 0.0) ? values[1] : -values[1];
    double z = (values[2] > 0.0) ? values[2] : -values[2];

    if (x > y) {
        if (x > z) {
            if (1.0 + x > 1.0) {
                y = y / x;
                z = z / x;
                denom = 1.0 / (x * sqrt(1.0 + y * y + z * z));
            }
        } else { /* z > x > y */ 
            if (1.0 + z > 1.0) {
                y = y / z;
                x = x / z;
                denom = 1.0 / (z * sqrt(1.0 + y * y + x * x));
            }
        }
    } else {
        if (y > z) {
            if (1.0 + y > 1.0) {
                z = z / y;
                x = x / y;
                denom = 1.0 / (y * sqrt(1.0 + z * z + x * x));
            }
        } else { /* x < y < z */
            if (1.0 + z > 1.0) {
                y = y / z;
                x = x / z;
                denom = 1.0 / (z * sqrt(1.0 + y * y + x * x));
            }
        }
    }

    if (1.0 + x + y + z > 1.0) {
        values[0] *= denom;
        values[1] *= denom;
        values[2] *= denom;
        return 1.0 / denom;
    } else {
        return 0.0;
    }
}

Vector3 Vector3::normalized() const {
    return *this / length();
}

Vector3 Vector3::cross(const Vector3& other) const {
    return Vector3(values[1] * other[2] - values[2] * other[1],
                   values[2] * other[0] - values[0] * other[2],
                   values[0] * other[1] - values[1] * other[0]);
}

Vector3 Vector3::reflect(const Vector3& normal) const {
    // r = i - 2 * (i . n) * n
    return *this - 2 * dot(normal) * normal;
}

ostream& operator <<(ostream& out, const Vector3& v) {
    return out << "v<" << v[0] << "," << v[1] << "," << v[2] << ">";
}

// --------------- Matrix3 ---------------

const Matrix3 Matrix3::Identity = Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);

Matrix3::Matrix3() : Matrix3(Matrix3::Identity) { }

Matrix3::Matrix3(double v0, double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8) {
    values[0] = v0;
    values[1] = v1;
    values[2] = v2;
    values[3] = v3;
    values[4] = v4;
    values[5] = v5;
    values[6] = v6;
    values[7] = v7;
    values[8] = v8;
}

Matrix3::Matrix3(const Matrix3& other) {
    copy(other.values, other.values + 9, values);
}

Matrix3::Matrix3(const Vector3& row1, const Vector3& row2, const Vector3& row3) {
    values[0] = row1[0]; 
    values[1] = row1[1]; 
    values[2] = row1[2]; 

    values[3] = row2[0]; 
    values[4] = row2[1]; 
    values[5] = row2[2]; 

    values[6] = row3[0]; 
    values[7] = row3[1]; 
    values[8] = row3[2]; 
}

Matrix3::Matrix3(const double* values) {
    copy(values, values + 9, this->values);
}

Matrix3& Matrix3::operator=(const Matrix3& other) {
    copy(other.values, other.values + 9, values);

    return *this;
}

bool Matrix3::operator==(const Matrix3& other) const {
    for (size_t i = 0; i < 9; i++) {
        if (values[i] != other.values[i]) {
            return false;
        }
    }

    return true;
}

bool Matrix3::operator!=(const Matrix3& other) const {
    return !(*this == other);
}

Vector3 Matrix3::getRow(size_t row) const {
    return Vector3(values[3 * row], values[3 * row + 1], values[3 * row + 2]);
}

double* Matrix3::getRow(size_t row) {
    return values + 3 * row;
}

Vector3 Matrix3::getColumn(size_t col) const {
    return Vector3(values[col], values[3 + col], values[6 + col]);
}

Vector3 Matrix3::operator[](size_t row) const {
    return getRow(row);
}

double* Matrix3::operator[](size_t row) {
    return getRow(row);
}

Matrix3 Matrix3::transposed() const {
    return Matrix3(getColumn(0), getColumn(1), getColumn(2));
}

double Matrix3::determinant() const {
    return (values[0] * values[4] * values[8] + values[1] * values[5] * values[6] + values[2] * values[3] * values[7]) -
           (values[2] * values[4] * values[6] + values[1] * values[3] * values[8] + values[0] * values[5] * values[7]);
}

const double* Matrix3::begin() const {
    return values;
}

const double* Matrix3::end() const {
    return begin() + 9;
}

// --------------- Vector4 ---------------

Vector4::Vector4() : Vector4(0, 0, 0, 0) { }

Vector4::Vector4(double x, double y, double z, double w) { 
    values[0] = x;
    values[1] = y;
    values[2] = z;
    values[3] = w;
}

Vector4::Vector4(const Vector4& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];
    values[3] = other.values[3];
}

Vector4& Vector4::operator=(const Vector4& other) {
    values[0] = other.values[0];
    values[1] = other.values[1];
    values[2] = other.values[2];
    values[3] = other.values[3];

    return *this;
}

double& Vector4::operator[](size_t i) {
    return values[i];
}

double Vector4::operator[](size_t i) const {
    return values[i];
}

bool Vector4::operator==(const Vector4& other) const {
    return values[0] == other.values[0] && values[1] == other.values[1] && values[2] == other.values[2] && values[3] == other.values[3];
}

bool Vector4::operator!=(const Vector4& other) const {
    return !(*this == other);
}

ostream& operator <<(ostream& out, const Vector4& v) {
    return out << "v<" << v[0] << "," << v[1] << "," << v[2] << "," << v[3] << ">";
}

// --------------- Matrix4 ---------------

const Matrix4 Matrix4::Identity(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

Matrix4::Matrix4() : Matrix4(Matrix4::Identity) { }

Matrix4::Matrix4(double v0, double v1, double v2, double v3, double v4, double v5, double v6, double v7,
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

Matrix4::Matrix4(const Matrix4& other) {
    copy(other.values, other.values + 16, values);
}

Matrix4::Matrix4(const Vector4& row1, const Vector4& row2, const Vector4& row3, const Vector4& row4) {
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

Matrix4::Matrix4(const double* values) {
    copy(values, values + 16, this->values);
}

Matrix4& Matrix4::operator=(const Matrix4& other) {
    copy(other.values, other.values + 16, values);

    return *this;
}

bool Matrix4::operator==(const Matrix4& other) const {
    for (size_t i = 0; i < 16; i++) {
        if (values[i] != other.values[i]) {
            return false;
        }
    }

    return true;
}

bool Matrix4::operator!=(const Matrix4& other) const {
    return !(*this == other);
}

Vector4 Matrix4::getRow(size_t row) const {
    return Vector4(values[4 * row], values[4 * row + 1], values[4 * row + 2], values[4 * row + 3]);
}

double* Matrix4::getRow(size_t row) {
    return values + 4 * row;
}

Vector4 Matrix4::getColumn(size_t col) const {
    return Vector4(values[col], values[4 + col], values[8 + col], values[12 + col]);
}

Vector4 Matrix4::operator[](size_t row) const {
    return getRow(row);
}

double* Matrix4::operator[](size_t row) {
    return getRow(row);
}

Matrix4 Matrix4::transposed() const {
    return Matrix4(getColumn(0), getColumn(1), getColumn(2), getColumn(3));
}

static void swaprows(Matrix4& a, size_t r1, size_t r2) {
    swap(a[r1][0], a[r2][0]);
    swap(a[r1][1], a[r2][1]);
    swap(a[r1][2], a[r2][2]);
    swap(a[r1][3], a[r2][3]);
}

static void dividerow(Matrix4& a, size_t r, double fac) {
    a[r][0] /= fac;
    a[r][1] /= fac;
    a[r][2] /= fac;
    a[r][3] /= fac;
}

static void submultrow(Matrix4& a, size_t dest, size_t src, double fac) {
    a[dest][0] -= fac * a[src][0];
    a[dest][1] -= fac * a[src][1];
    a[dest][2] -= fac * a[src][2];
    a[dest][3] -= fac * a[src][3];
}

Matrix4 Matrix4::inverse() const {
    /* The algorithm is plain old Gauss-Jordan elimination 
       with partial pivoting. */

    Matrix4 a(*this);
    Matrix4 ret;

    /* Loop over cols of a from left to right, 
       eliminating above and below diag */

    /* Find largest pivot in column j among rows j..3 */
    for(size_t j = 0; j < 4; ++j) { 
        size_t i1 = j; /* Row with largest pivot candidate */
        for(size_t i = j + 1; i < 4; ++i) {
            if(fabs(a[i][j]) > fabs(a[i1][j])) {
                i1 = i;
            }
        }

        /* Swap rows i1 and j in a and ret to put pivot on diagonal */
        swaprows(a, i1, j);
        swaprows(ret, i1, j);

        /* Scale row j to have a unit diagonal */
        if(a[j][j] == 0.0) {
            // Theoretically throw an exception.
            return ret;
        }

        dividerow(ret, j, a[j][j]);
        dividerow(a, j, a[j][j]);

        /* Eliminate off-diagonal elems in col j of a, doing identical 
           ops to b */
        for(size_t i = 0; i < 4; ++i) {
            if(i != j) {
                submultrow(ret, i, j, a[i][j]);
                submultrow(a, i, j, a[i][j]);
            }
        }
    }

    return ret;
}

Matrix3 Matrix4::upper3x3() const {
    return Matrix3(values[0], values[1], values[2],
                   values[4], values[5], values[6],
                   values[8], values[9], values[10]);
}

const double* Matrix4::begin() const {
    return values;
}

const double* Matrix4::end() const {
    return begin() + 16;
}

Matrix4 Matrix4::makeXRotation(double angle) {
    angle = angle * M_PI / 180.0;

    float ca = cos(angle);
    float sa = sin(angle);

    return Matrix4(
        1, 0, 0, 0,
        0, ca, -sa, 0,
        0, sa, ca, 0,
        0, 0, 0, 1
    );
}

Matrix4 Matrix4::makeYRotation(double angle) {
    angle = angle * M_PI / 180.0;

    float ca = cos(angle);
    float sa = sin(angle);

    return Matrix4(
        ca, 0, sa, 0,
        0, 1, 0, 0,
        -sa, 0, ca, 0,
        0, 0, 0, 1
    );
}

Matrix4 Matrix4::makeZRotation(double angle) {
    angle = angle * M_PI / 180.0;

    float ca = cos(angle);
    float sa = sin(angle);

    return Matrix4(
        ca, -sa, 0, 0,
        sa, ca, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

Matrix4 Matrix4::makeRotation(double pitch, double yaw, double roll) {
    return makeYRotation(yaw) * makeXRotation(pitch) * makeZRotation(roll);
}

Matrix4 Matrix4::makeRotation(double angle, const Vector3& axis) {
    angle = angle * M_PI / 180.0;

    // formula taken from http://en.wikipedia.org/wiki/Rotation_matrix
    float ux = axis[0];
    float uy = axis[1];
    float uz = axis[2];

    float ca = cos(angle);
    float sa = sin(angle);

    return Matrix4(
        ca + ux * ux * (1 - ca),        ux * uy * (1 - ca) - uz * sa,   ux * uz * (1 - ca) + uy * sa,   0,
        uy * ux * (1 - ca) + uz * sa,   ca + uy * uy * (1 - ca),        uy * uz * (1 - ca) - ux * sa,   0,
        uz * ux * (1 - ca) - uy * sa,   uz * uy * (1 - ca) + ux * sa,   ca + uz * uz * (1 - ca),        0,
        0,                              0,                              0,                              1
    );
}

Matrix4 Matrix4::makeTranslation(double x, double y, double z) {
    return Matrix4(
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    );
}

Matrix4 Matrix4::makeScaling(double x, double y, double z) {
    return Matrix4(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    );
}

Matrix4 Matrix4::makeOrtho(double left, double right, double bottom, double top, double near, double far) {
    // formula from http://en.wikipedia.org/wiki/Orthographic_projection#Geometry
    return Matrix4(
        2 / (right - left), 0,                  0,                  -(right + left) / (right - left),
        0,                  2 / (top - bottom), 0,                  -(top + bottom) / (top - bottom),
        0,                  0,                  -2 / (far - near),  (far + near) / (far - near),
        0,                  0,                  0,                  1
    );
}

Matrix4 Matrix4::makePerspective(double fov, double aspect, double near, double far) {
    // because holy crap I just wasted so much time by passing in fov in degrees when it expected radians
    fov = fov * M_PI / 180.0;

    // formula adapted from http://www.songho.ca/opengl/gl_projectionmatrix.html
    double right = near * tan(fov / 2);
    double top = aspect * right;

    return Matrix4(
        near / right,   0,          0,                              0,
        0,              near / top, 0,                              0,
        0,              0,          (far + near) / (near - far),    (2 * far * near) / (near - far),
        0,              0,          -1,                             0
    );
}

ostream& operator<<(ostream& out, const Matrix4& m) {
    return out << "[" << m[0][0] << " " << m[0][1] << " " << m[0][2] << " " << m[0][3] << "]" << endl
               << "[" << m[1][0] << " " << m[1][1] << " " << m[1][2] << " " << m[1][3] << "]" << endl
               << "[" << m[2][0] << " " << m[2][1] << " " << m[2][2] << " " << m[2][3] << "]" << endl
               << "[" << m[3][0] << " " << m[3][1] << " " << m[3][2] << " " << m[3][3] << "]";
}

// --------------- Colour ---------------

Colour::Colour() : Colour(1, 1, 1) { }

Colour::Colour(double c) : Colour(c, c, c) { }

Colour::Colour(double r, double g, double b) {
    components[0] = r;
    components[1] = g;
    components[2] = b;
}

Colour::Colour(const Colour& other) {
    components[0] = other.components[0];
    components[1] = other.components[1];
    components[2] = other.components[2];
}

Colour& Colour::operator=(const Colour& other) {
    components[0] = other.components[0];
    components[1] = other.components[1];
    components[2] = other.components[2];

    return *this;
}

Colour& Colour::operator+=(const Colour& other) {
    return *this = *this + other;
}

double Colour::operator[](size_t i) const {
    return components[i];
}
double& Colour::operator[](size_t i) {
    return components[i];
}

ostream& operator<<(ostream& out, const Colour& c) {
    return out << "c<" << c.r() << "," << c.g() << "," << c.b() << ">";
}

Colour Colour::inverse() const {
    return Colour(1 - r(), 1 - g(), 1 - b());
}
