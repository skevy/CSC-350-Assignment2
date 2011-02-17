//***************************************************************************//
// Graphics Pad
// 
// Description: This is test platform for my OpenGL based graphics engine
//
//***************************************************************************//

//***************************************************************************//
#include "App.hpp"
//***************************************************************************//

//***************************************************************************//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, char* lpCmdLine, int nCmdShow)			
{
  App::Instance(hInstance);

  if(App::Instance()->Initialize())
    App::Instance()->Run();
  App::Instance()->End();

  return 0;
}
//***************************************************************************//