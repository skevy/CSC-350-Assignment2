//***************************************************************************//
// Device Class Interface
//
// Created Sept 27, 2006
// By: Jeremy M Miller
//
// Copyright (c) 2006 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of Habu technology (tm).
//                 PROPRIETARY AND CONFIDENTIAL
//***************************************************************************//

#ifndef HABU_INPUT_DEVICE_HPP
#define HABU_INPUT_DEVICE_HPP

//***************************************************************************//
#include "HabuInput.hpp"
//***************************************************************************//

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  // This class is the base class for all input devices
  class Device
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Device();
    virtual ~Device();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // All input devices need these methods. The implemenation of the devices
    // in Devices.cpp currently does nothing
    virtual bool Initialize(IDirectInput8* pDirectInput, HWND hMainWindow);
    virtual bool Uninitalize();

    virtual void Poll();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  }; // End of class Device
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_INPUT_DEVICE_HPP