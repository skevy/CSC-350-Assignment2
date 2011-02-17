//***************************************************************************//
// Random Class Interface
//
// Created: April 14, 2007
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

//***************************************************************************//
namespace HabuTech
{
  template <class T>
  class Random
  {
  private:
  public:
    Random();
    ~Random();

    T Generate();
    T Generate(T tMax);
    T Generate(T tMin, T tMax);
  };
} // End of namespace HabuTech
//***************************************************************************//