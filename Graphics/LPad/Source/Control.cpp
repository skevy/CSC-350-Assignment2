//***************************************************************************//
// Control Object Implementation
//
// Created May 21, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2007 Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//
//***************************************************************************//

#include "Control.hpp"

//***************************************************************************//
Control::Control()
{
}
//***************************************************************************//

//***************************************************************************//
Control::~Control()
{
}
//***************************************************************************//

ControlSignalType Control::Update(Camera* cam, float time) {
    //Keyboard
    if(Input::Instance()->GetKeyboard()->KeyDown(HIK_A) && 
      !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
    {
		cam->strafe(-2.f * time);
    }
    if(Input::Instance()->GetKeyboard()->KeyDown(HIK_W) && 
      !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
    {
	    cam->advance(-2.f * time);
    }
    if(Input::Instance()->GetKeyboard()->KeyDown(HIK_S) && 
      !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
    {
        cam->advance(2.f * time);
    }
    if(Input::Instance()->GetKeyboard()->KeyDown(HIK_D) && 
      !Input::Instance()->GetKeyboard()->KeyDown(HIK_RSHIFT))
    {
	    cam->strafe(2.f * time);
    }
    
    //Mouse
    cam->relativeYaw((Input::Instance()->GetMouse()->Direct_DX()) * -0.0005f);
    cam->relativePitch((Input::Instance()->GetMouse()->Direct_DY()) * -0.0005f);
    
    Input::Instance()->Poll();

    return END_CONTROL_SIGNAL;
}