#include <cmath> 
#pragma once

template<class type>
class Vector3d 
{
    private:
        type Vec[3];

    public:

        Vector3d(type x, type y, type z); 

        Vector3d<type> operator+(const Vector3d<type>& otherVector) const;
        Vector3d<type>& operator+=(const Vector3d<type>& otherVector);

        Vector3d<type> operator-(const Vector3d<type> &otherVector) const;
        Vector3d<type>& operator-=(const Vector3d<type>& otherVector);

        Vector3d<type> operator*(const type scalar);
        Vector3d<type>& operator*=(const type scalar);

        Vector3d<type> operator/(const type scalar);
        Vector3d<type>& operator/=(const type scalar);

        bool operator==(const Vector3d<type> &otherVector) const;
        bool operator!=(const Vector3d<type> &otherVector) const;

        Vector3d<type> invertVector(void);
        Vector3d<type> normalizeVector(void);

        Vector3d<type> crossProduct(const Vector3d<type>& otherVector);

        type getLength(void);
        type getDotProduct(const Vector3d<type>& otherVector);
        type getManhattanDistance(const Vector3d<type>& otherVector );

        type getVectorIndex(int Index) const;
};

template<class type>
Vector3d<type>::Vector3d(type x, type y, type z)
    : Vec{ x, y, z }
{
}


template<class type> 
Vector3d<type>&
Vector3d<type>::operator+=(const Vector3d<type>& otherVector)
{
    for(int i = 0; i < 3; i++)
    {
        this->Vec[i] += otherVector.Vec[i];
    }
    return (*this);
}

template<class type> 
Vector3d<type>
Vector3d<type>::operator+(const Vector3d<type>& otherVector) const
{
    return Vector3d<type>(*this)+=otherVector;
}

template<class type>
Vector3d<type>&
Vector3d<type>::operator-=(const Vector3d<type>& otherVector)
{
    for (int i = 0; i < 3; i++)
    {
        int result = this->Vec[i] - otherVector.getVectorIndex(i);
        this->Vec[i] = result;
    }
    return (*this);
}

template<class type>
Vector3d<type>
Vector3d<type>::operator-(const Vector3d<type>& otherVector) const
{
    return Vector3d<type>(*this)-=otherVector;
}

template<class type>
Vector3d<type>
Vector3d<type>::operator/(const type scalar)
{
    for(int i = 0; i < 3; i++)
    {
        this->Vec[i] /= scalar;
    }
    return (*this);
}

template<class type>
Vector3d<type>
Vector3d<type>::operator*(const type scalar)
{
    for(int i = 0; i < 3; i++)
    {
        this->Vec[i] *= scalar;
    }
    return (*this);
}

template<class type>
bool
Vector3d<type>::operator==(const Vector3d<type> &otherVector) const
{
    for(int i = 0; i < 3; i++)
    {
        if( this->Vec[i] != otherVector.Vec[i])
        {
            return false;
        }
    }
    return true;
}

template<class type>
bool
Vector3d<type>::operator!=(const Vector3d<type> &otherVector) const
{
    for(int i = 0; i < 3; i++)
    {
        if( this->Vec[i] != otherVector.Vec[i])
        {
            return true;
        }
    }
    return false;
}

template<class type>
Vector3d<type>
Vector3d<type>::invertVector(void)
{
    for(int i = 0; i < 3; i++)
    {
        int result = Vec[i] * -1;
        this->Vec[i] = result;
    }
    return (*this);
}

template<class type>
type 
Vector3d<type>::getDotProduct(const Vector3d<type>& otherVector)
{
    return  ( (this->Vec[0] * otherVector.Vec[0])   + 
              (this->Vec[1] * otherVector.Vec[1])   + 
              (this->Vec[2] * otherVector.Vec[2]) );
}

template<class type>
type 
Vector3d<type>::getManhattanDistance(const Vector3d<type>& otherVector)
{
    return  ( abs( (this->Vec[0] - otherVector.Vec[0]) )   + 
              abs( (this->Vec[1] - otherVector.Vec[1]) )  + 
              abs( (this->Vec[2] - otherVector.Vec[2]) ) );
}

template<class type>
type
Vector3d<type>::getLength(void)
{
    return std::sqrt( ( (this->Vec[0] * this->Vec[0])   + 
                        (this->Vec[1] * this->Vec[1])   + 
                        (this->Vec[2] * this->Vec[2]) ));
}

template<class type>
Vector3d<type>
Vector3d<type>::normalizeVector(void)
{
    type Length = this->getLength();
    for(int i = 0; i < 3; i++)
    {
        this->Vec[i] /= Length;
    } 
    return (*this);
}

template<class type>
Vector3d<type>
Vector3d<type>::crossProduct(const Vector3d<type>& otherVector)
{
    return Vector3d<type>
    ( (this->Vec[1] * otherVector.Vec[2]) - (this->Vec[2] * otherVector.Vec[1]),
      (this->Vec[0] * otherVector.Vec[2]) - (this->Vec[2] * otherVector.Vec[0]),
      (this->Vec[0] * otherVector.Vec[1]) - (this->Vec[1] * otherVector.Vec[0]) );
}

template<class type>
type
Vector3d<type>::getVectorIndex(int Index) const
{
    return Vec[Index];
}

