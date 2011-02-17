//***************************************************************************//
// Matrix Class Interface
//
// Created: April 6, 2007
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

#ifndef HABU_MATH_MATRIX_HPP
#define HABU_MATH_MATRIX_HPP

#include "Vector.hpp"

//#define LEFT_HAND

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  template <class T, unsigned char D>
  class Matrix
  {
  private:
    //***********************************************************************//
    Vector<T, D> mtMatrix[D];
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Matrix() { this->Identity(); }
    ~Matrix() {}
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // TODO Implement See Page 86 in Linear Algebra Book
    T Determinate() const;

    void Identity();
    void Zero();

    // TODO Test these
    void RotateAboutX(T& rtAngle);
    void RotateAboutY(T& rtAngle);
    void RotateAboutZ(T& rtAngle);
    void RotateAboutAxis(Vector<T, D>& rtAxis, T& rtAngle);

    // TODO Test these
    void Translate(T& rtX, T& rtY, T& rtZ);
    void Translate(Vector<T, D>& rtVector);

    // TODO Implement
    void Transpose();

    void Perspective(T tVerticalFOV, T tAspect, T tNearClipPlane, T tFarClipPlane); 

    void ColumnMajor(T pArray[D * D]) const;
    void RowMajor(T pArray[D * D]) const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    T operator()(unsigned char ucRow, unsigned char ucColumn) const;
    Vector<T, D>& operator[](unsigned char ucRow);
    Matrix<T, D> operator*(const Matrix<T, D>& rhs) const;  // Matrix Multiplication
    Matrix<T, D> operator*(const T& rhs) const;             // Scalar Multiplication
    Matrix<T, D> operator+(const Matrix<T, D>& rhs) const;  // Matrix Addition
    Matrix<T, D> operator-(const Matrix<T, D>& rhs) const;  // Matrix Subtraction
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Matrix
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_MATH_MATRIX_HPP