#pragma once

#include <geometry_msgs/Point.h>

namespace geometry
{

template <class T> class CNPointTemplate : public geometry_msgs::Point
{
  public:
    T rotateZ(double radian)
    {
        return T(x * cos(radian) - y * sin(radian), x * sin(radian) + y * cos(radian), z);
    }

    double angleZ()
    {
        return atan2(y, x);
    }

    double angleZToPoint(T &point)
    {
        return atan2(point->y - this->y, point->x - this->x);
    }

    T normalize()
    {
        T norm = T();
        double length = this->length();

        if (length > 0)
        {
            norm.x = this->x / length;
            norm.y = this->y / length;
            norm.z = this->z / length;
        }
        else
        {
            std::cerr << "CNPoint: Trying to normalize (0, 0, 0)!" << std::endl;
        }

        return norm;
    }

    double distanceTo(T &pos)
    {
        T delta = *this - pos;
        return delta.length();
    }

    double length()
    {
        return sqrt(x * x + y * y + z * z);
    }

    // Self
    T operator+(const T &right)
    {
        return T(this->x + right.x, this->y + right.y, this->z + right.z);
    }

    T operator-(const CNPointTemplate<T> &right)
    {
        return T(this->x - right.x, this->y - right.y, this->z - right.z);
    }

    // Scalar
    T operator/(const double &right)
    {
        return T(this->x / right, this->y / right, this->z / right);
    }

    T operator*(const double &right)
    {
        return T(this->x * right, this->y * right, this->z * right);
    }
};

} /* namespace geometry */
