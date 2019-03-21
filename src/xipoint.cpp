////////////////////////////////////////////////////////////////////////////////
// Module Name:  xipoint.h/cpp
// Authors:      S
// Version:      0.2.1
// Date:         08.09.2017
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "xipoint.h"

#include <algorithm>        // min
#include <cmath>

namespace xi
{



// TODO: put the method implementations here



Point::Point(int x, int y)
{
    _x = x;
    _y = y;
}

void Point::shift(int shf)
{
    _x += shf;
    _y += shf;
}

void Point::shift(int xSh, int ySh)
{
    _x += xSh;
    _y += ySh;
}

void Point::shift(const Point &pt)
{
    _x += pt.getX();
    _y += pt.getY();
}

double Point::dist(const Point &other)
{
    return sqrt(((_x - other.getX()) * (_x - other.getX())) + (_y - other.getY()) * (_y - other.getY()));
}

int Point::getX() const
{
    return _x;
}

int Point::getY() const
{
    return _y;
}

void Point::setX(int x)
{
    _x = x;
}

void Point::setY(int y)
{
    _y = y;
}

PointArray::PointArray()
{
    _arr = nullptr;
    _size = 0;

}

PointArray::PointArray(const xi::Point *points, xi::PointArray::Uint n)
{
    _size = n;
    _arr = new Point[_size];
    for (int i = 0; i < _size; ++i)
    {
        _arr[i] = points[i];
    }
}

PointArray::PointArray(const xi::PointArray &pv)
{
    _size = pv.getSize();
    _arr = new Point[_size];

    for (int i = 0; i < _size; ++i)
    {
        _arr[i] = pv.getRawPtr()[i];
    }
}

PointArray::~PointArray()
{
    _size = 0;
    delete[] _arr;
}

void PointArray::append(const xi::Point &pt)
{
    resize(_size + 1);
    _arr[_size - 1] = pt;
}

void PointArray::insert(const xi::Point &pt, xi::PointArray::Uint pos)
{
    if (pos == 0)
    {
        Point *buf_arr = new Point[_size + 1];
        buf_arr[0] = pt;
        for (int i = 0; i < _size; i++)
        {
            buf_arr[i + 1] = _arr[i];
        }
        delete[] _arr;
        _size++;
        _arr = new Point[_size];
        for (int i = 0; i < _size; ++i)
        {
            _arr[i] = buf_arr[i];
        }
        delete[] buf_arr;
    } else if (pos > _size)
    {
        resize(_size + 1);
        _arr[_size - 1] = pt;
    } else
    {
        Point *buf_arr = new Point[_size + 1];
        resize(_size + 1);
        int i = 0;
        while (i < _size)
        {
            if (i < pos)
            {
                buf_arr[i] = _arr[i];
                i++;
            }
            if (i == pos)
            {
                buf_arr[i] = pt;
                i++;
            } else
            {
                buf_arr[i] = _arr[i - 1];
                i++;
            }

        }
        delete[] _arr;
        _arr = new Point[_size];
        for (int i = 0; i < _size; ++i)
        {
            _arr[i] = buf_arr[i];
        }
        delete[] buf_arr;
    }

}

void PointArray::remove(xi::PointArray::Uint pos)
{
    if (pos < getSize())
    {
        if (getSize() == 1)
        {
            delete[] _arr;
            _arr = nullptr;
            _size = 0;
        } else
        {
            _size--;
            Point *newPointArray = new Point[_size];
            for (int i = 0; i < pos; i++)
                newPointArray[i] = _arr[i];
            for (int i = pos; i < _size; i++)
                newPointArray[i] = _arr[i + 1];
            delete[] _arr;
            _arr = newPointArray;
        }

    }
}

void PointArray::clear()
{
    _arr = nullptr;
    _size = 0;
}

double PointArray::computePath()
{
    double distance = 0;
    for (int i = 0; i < _size - 1; ++i)
    {
        distance += _arr[i].dist(_arr[i + 1]);
    }
    return distance;

}

PointArray::Uint PointArray::getSize() const
{
    return _size;
}

Point *PointArray::get(PointArray::Uint pos)
{
    if (pos < _size)
    {
        return &_arr[pos];
    } else
    {
        return nullptr;
    }

}

const Point *PointArray::get(PointArray::Uint pos) const
{
    if (pos < _size)
    {
        return &_arr[pos];
    } else
    {
        return nullptr;
    }
}

void PointArray::resize(xi::PointArray::Uint n)
{
    Point *bufferarr = new Point[n];
    for (int i = 0; i < _size; ++i)
    {

        if (i >= n)
        {
            bufferarr[i] = 0;
        } else
        {
            bufferarr[i] = _arr[i];
        }

    }
    delete[]_arr;
    _size = n;
    _arr = new Point[_size];
    for (int i = 0; i < _size; ++i)
    {
        _arr[i] = bufferarr[i];
    }
    delete[]bufferarr;

} // namespace xi {
}