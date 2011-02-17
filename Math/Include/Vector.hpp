//***************************************************************************//
// Vector Class Interface
//
// Created: April 3, 2007
// By: Jeremy M Miller
//
// Copyright (c) 2007 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
// PROPRIETARY 
// Creative Commons Licensees are subject to the license found at
// http://creativecommons.org/licenses/by-nc-nd/3.0/
// Other licensing options may be available. Contact info@bluehabu.com.
//***************************************************************************//

#ifndef HABU_MATH_VECTOR_HPP
#define HABU_MATH_VECTOR_HPP

#include "Point.hpp"

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  template <class T, unsigned char  D> class Matrix;
  //*************************************************************************//

  //*************************************************************************//
  template <class T, unsigned char  D>
  class Vector : public Point<T, D>
  {
  private:
  public:
    Vector()  {}
    ~Vector() { Point::~Point(); } // Calling base class's destructor since base 
                                   // class's destructor is not virtual for 
                                   // performance reasons.

    void Cross(const Vector<T, D>& rVector1, const Vector<T, D>& rVector2);
   
    T Dot(const Vector<T,D>& rInput) const;

    T Magnitude() const;
    void Normalize();


    T operator()(unsigned char ucIndex) const
    {
      assert(ucIndex < D);

      if(ucIndex < D)
        return mtaComponent[ucIndex];
      return mtaComponent[D - 1];
    }

    T& operator[](unsigned char ucIndex)
    {
      assert(ucIndex < D);

      if(ucIndex < D)
        return mtaComponent[ucIndex];
      return mtaComponent[D - 1];
    }

    Vector<T,D> operator+(const Vector<T,D>& rhs) const;
    Vector<T,D> operator-(const Vector<T,D>& rhs) const;
    Vector<T,D> operator*(const T& rhs) const
    {

      Vector<T,D> tTempVector;
      for(unsigned char i = 0; i < D; i++)
      {
        tTempVector[i] = mtaComponent[i] * rhs;
      }
      return tTempVector;
    }
    Vector<T,D> operator/(const T& rhs) const
    {
      Vector<T,D> tTempVector;
      for(unsigned char i = 0; i < D; i++)
      {
        tTempVector[i] = mtaComponent[i] / rhs;
      }
      return tTempVector;
    }

    void Transform(Matrix<T,D>& rMatrix);
    void Clear()
    {
      for(unsigned char i = 0; i < D; i++)
      {
        mtaComponent[i] = 0.0;
      }
    }
  }; // End of class Vector
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_MATH_VECTOR_HPP