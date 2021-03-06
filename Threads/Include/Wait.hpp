//***************************************************************************//
// Sleep Method Interface
//
// Created: Jun 23, 2008
// By: Jeremy M Miller (info@bluehabu.com)
//
// Copyright (c) 2005-2008 Jeremy M Miller.  
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu Technologies(tm).
//
// Usage of HabuThreads is subject to the appropriate license agreement.
//                                  
//***************************************************************************//

#ifndef HABU_THREADS_WAIT_HPP
#define HABU_THREADS_WAIT_HPP

//***************************************************************************//
namespace HabuTech
{
  /// This method will block while waiting for the passed in amount of time to
  /// expire.
  /// \param [in] ulTime
  /// This parameter this is amount of time this method will block. This 
  /// parameters units are in milliseconds.
  void _cdecl Wait(unsigned long ulTime);
} // End of namespace HabuThread
//***************************************************************************//

#endif HABU_THREADS_WAIT_HPP