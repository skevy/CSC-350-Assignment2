

#ifndef VICTOR_GRAPHICS_HPP
#define VICTOR_GRAPHICS_HPP

//***************************************************************************//
#define DEFAULT_WINDOW_WIDTH  800
#define DEFAULT_WINDOW_HEIGHT 600
//***************************************************************************//

//***************************************************************************//
// System Includes
#include <assert.h>
#include <vector>
#include <string>

//***************************************************************************//
// Platform Includes
#include <windows.h>
//***************************************************************************//

#include "Scenes\Scene.hpp"

//***************************************************************************//
namespace Victor
{
  //*************************************************************************//
  class Graphics
  {
  private:
    //***********************************************************************//

    Scene *scene;

    //-----------------------------------------------------------------------//
    static HDC       smhDeviceContext;
    static HGLRC     smhRenderingContext;
    static HWND      smhWindow;
    static HINSTANCE smhInstance;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long mulWindowWidth;
    unsigned long mulWindowHeight;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    // This member is used to store the index to the current adapter being used.
    unsigned long mulAdapter;
    //-----------------------------------------------------------------------//

    //***********************************************************************//
  public:
    //***********************************************************************//
    //-----------------------------------------------------------------------//
    Graphics(bool bWindowed, string filename);
    ~Graphics();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    unsigned long GetNumberOfAdapters();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    long Initialize(HWND hWindow, unsigned long ulWidth = DEFAULT_WINDOW_WIDTH, unsigned long ulHeight = DEFAULT_WINDOW_HEIGHT);
    static long Uninitialize();
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void WindowDimensions(unsigned long ulWidth, unsigned long ulHeight);
    unsigned long WindowWidth() const;
    unsigned long WindowHeight() const;

    void  NearClipPlane(float fNear);
    float NearClipPlane() const;
    
    void  FarClipPlane(float fFar);
    float FarClipPlane() const;
    
    void  FieldOfVeiw(float fDegrees);
    float FieldOfView() const;
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    void SetBackBufferSize(unsigned long ulWidth, unsigned long ulHeight);
    //-----------------------------------------------------------------------//

    //-----------------------------------------------------------------------//
    Scene* getActiveScene();

    int Render(float fDT);


    void SwapBuffer();
    //-----------------------------------------------------------------------//
    //***********************************************************************//
  };
  //*************************************************************************//
}
//***************************************************************************//

#endif VICTOR_GRAPHICS_HPP
