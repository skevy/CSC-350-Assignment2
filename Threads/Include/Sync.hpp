//***************************************************************************//
// Sync Class Interface
//
// Created: Oct 6, 2008
// By: Jeremy M Miller (info@bluehabu.com)
//
// Copyright (c) 2008 Jeremy M Miller.  
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu Technologies(tm).
//
// Usage of HabuThreads is subject to the appropriate license agreement.
//                 
//***************************************************************************//

#ifndef HABU_THREADS_SYNC_HPP
#define HABU_THREADS_SYNC_HPP

//***************************************************************************//
namespace HabuTech
{
  //*************************************************************************//
  /// \brief Sync is very simple base class that holds a handle to used by 
  /// derived classes.  This handle is required by other 
  /// synchronization mechanisms.
  class Sync
  {
  private:
    //***********************************************************************//
    //***********************************************************************//
  protected:
    //***********************************************************************//
    // This pointer will point to the OS dependent synchronization object.
    // This is also called a "handle" to the synchronization object buy some
    // operating systems. This library will follow that convention.
    void* mvpSyncObject;
    //***********************************************************************//
  public:
    //***********************************************************************//
    Sync();
    virtual ~Sync();

    /// This method provides public read only access to the synchronization objects
    /// handle.
    /// \return
    /// This method will return the handle to the synchronization handle.
    void* _cdecl Handle() const;
    //***********************************************************************//
  }; // End of class Sync
  //*************************************************************************//
} // End of namespace HabuTech
//***************************************************************************//

#endif HABU_THREADS_SYNC_HPP