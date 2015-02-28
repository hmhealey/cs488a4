/*****************************************
 * Harrison Healey - hmhealey - 20376857 *
 *****************************************/

#include "Algebra.hpp"

double Vector3::normalize()
{
  double denom = 1.0;
  double x = (v_[0] > 0.0) ? v_[0] : -v_[0];
  double y = (v_[1] > 0.0) ? v_[1] : -v_[1];
  double z = (v_[2] > 0.0) ? v_[2] : -v_[2];

  if(x > y) {
    if(x > z) {
      if(1.0 + x > 1.0) {
        y = y / x;
        z = z / x;
        denom = 1.0 / (x * sqrt(1.0 + y*y + z*z));
      }
    } else { /* z > x > y */ 
      if(1.0 + z > 1.0) {
        y = y / z;
        x = x / z;
        denom = 1.0 / (z * sqrt(1.0 + y*y + x*x));
      }
    }
  } else {
    if(y > z) {
      if(1.0 + y > 1.0) {
        z = z / y;
        x = x / y;
        denom = 1.0 / (y * sqrt(1.0 + z*z + x*x));
      }
    } else { /* x < y < z */
      if(1.0 + z > 1.0) {
        y = y / z;
        x = x / z;
        denom = 1.0 / (z * sqrt(1.0 + y*y + x*x));
      }
    }
  }

  if(1.0 + x + y + z > 1.0) {
    v_[0] *= denom;
    v_[1] *= denom;
    v_[2] *= denom;
    return 1.0 / denom;
  }

  return 0.0;
}

Vector3 Vector3::normalized()
{
  return *this / length();
}

/*
 * Define some helper functions for matrix inversion.
 */

static void swaprows(Matrix4& a, size_t r1, size_t r2)
{
  std::swap(a[r1][0], a[r2][0]);
  std::swap(a[r1][1], a[r2][1]);
  std::swap(a[r1][2], a[r2][2]);
  std::swap(a[r1][3], a[r2][3]);
}

static void dividerow(Matrix4& a, size_t r, double fac)
{
  a[r][0] /= fac;
  a[r][1] /= fac;
  a[r][2] /= fac;
  a[r][3] /= fac;
}

static void submultrow(Matrix4& a, size_t dest, size_t src, double fac)
{
  a[dest][0] -= fac * a[src][0];
  a[dest][1] -= fac * a[src][1];
  a[dest][2] -= fac * a[src][2];
  a[dest][3] -= fac * a[src][3];
}

/*
 * invertMatrix
 *
 * I lifted this code from the skeleton code of a raytracer assignment
 * from a different school.  I taught that course too, so I figured it
 * would be okay.
 */
Matrix4 Matrix4::inverse() const
{
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

Colour Colour::inverse() const {
    return Colour(1 - r_, 1 - g_, 1 - b_);
}
