//***************************************************************************//
// HabuGraphics Base Class Implementation
//
// Created Jan 01, 2005
// By: Jeremy M Miller
//
// Copyright (c) 2005-2010  Jeremy M Miller.  All rights reserved.
// This source code module, and all information, data, and algorithms
// associated with it, are part of BlueHabu technology (tm).
//
//***************************************************************************//

// System Includes
#include <assert.h>

// 3rd Party Includes
#include <GL\glew.h> // Must be called before GL.h

// Platform Includes
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

// Local Includes
#include "Graphics.hpp"

GLfloat Zmin    = 0.100000f;
GLfloat Zmax    = 100.0f;
GLfloat FOV     = 49.1343395f;
extern float fDT;

//DEFINES
#define CLEAR_COLOR 0xFFEEEEEE

namespace Victor {
    
    HDC       Graphics::smhDeviceContext = NULL;
    HGLRC     Graphics::smhRenderingContext = NULL;
    HWND      Graphics::smhWindow = NULL;
    HINSTANCE Graphics::smhInstance = NULL;

    // Constructor
    Graphics::Graphics(bool bWindowed, string filename) {
        this->scene = new Scene("monkey", filename);
        this->mulWindowHeight      = DEFAULT_WINDOW_HEIGHT;
        this->mulWindowWidth       = DEFAULT_WINDOW_WIDTH;
    }

    // Destructor
    Graphics::~Graphics() {
    
    }

    long Graphics::Initialize(HWND hWindow, unsigned long ulWidth, unsigned long ulHeight) {
        // Create a data member to hold the result of this method. In this method's
        // case it will hold any error codes. By default set to 1 to signal no error. 
        long lResultCode = 1;

        smhWindow = hWindow;

        static	PIXELFORMATDESCRIPTOR pfd= {			// pfd Tells Windows How We Want Things To Be
            sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
            1,											// Version Number
            PFD_DRAW_TO_WINDOW |						// Format Must Support Window
            PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
            PFD_DOUBLEBUFFER,							// Must Support Double Buffering
            PFD_TYPE_RGBA,								// Request An RGBA Format
            32,										    // Select Our Color Depth
            0, 0, 0, 0, 0, 0,							// Color Bits Ignored
            0,											// No Alpha Buffer
            0,											// Shift Bit Ignored
            0,											// No Accumulation Buffer
            0, 0, 0, 0,									// Accumulation Bits Ignored
            16,											// 16Bit Z-Buffer (Depth Buffer)  
            0,											// No Stencil Buffer
            0,											// No Auxiliary Buffer
            PFD_MAIN_PLANE,								// Main Drawing Layer
            0,											// Reserved
            0, 0, 0										// Layer Masks Ignored
        };

        GLuint PixelFormat;
        if(!(smhDeviceContext = GetDC(hWindow))) {
            lResultCode = -1;
            smhDeviceContext = NULL;
        }
        
        // Did Windows Find A Matching Pixel Format?
        if(lResultCode > 0 && !(PixelFormat = ChoosePixelFormat(smhDeviceContext, &pfd))) {
            lResultCode = -1;
        }

        // Are We Able To Set The Pixel Format?
        if(lResultCode > 0 && !SetPixelFormat(smhDeviceContext, PixelFormat, &pfd)) {
            lResultCode = -1;
        }

        // Are We Able To Get A Rendering Context?
        if(lResultCode > 0 && !(smhRenderingContext = wglCreateContext(smhDeviceContext))) {
            lResultCode = -1;
        }
        
        // Try To Activate The Rendering Context
        if(lResultCode > 0 && !wglMakeCurrent(smhDeviceContext, smhRenderingContext)) {			
            lResultCode = -1;
        }

        // Check Required Extensions
        GLenum err = glewInit();
        if(err == GLEW_OK) {
            glewGetString(GLEW_VERSION);
            if(GLEW_ARB_vertex_buffer_object) {
                glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
                glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
                glClearDepth(1.0f);									// Depth Buffer Setup
                glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
                //glEnable ( GL_LIGHTING ) ;
                glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
                glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
                glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            } else {
                lResultCode = -1;
            }
        } else {
            glewGetErrorString(err);
            lResultCode = -1;
        }

        //Init viewport and perspective
        glViewport(0,0,DEFAULT_WINDOW_WIDTH,DEFAULT_WINDOW_HEIGHT);
        this->scene->setAspectRatio((float)DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT);
        this->scene->load();

        return lResultCode;
    } // End of long Graphics::Initialize(HWND hWindow)	

    long Graphics::Uninitialize() {
        long lReturnCode = 1;
        if(smhRenderingContext) {											// Do We Have A Rendering Context?
            if(!wglMakeCurrent(NULL,NULL)) {			            		// Are We Able To Release The DC And RC Contexts?
                MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
                lReturnCode = -1;
            }
            if(!wglDeleteContext(smhRenderingContext)) {			    	// Are We Able To Delete The RC?
                MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
                lReturnCode = -1;
            }
            smhRenderingContext = NULL;										// Set RC To NULL
        }
        if(smhDeviceContext && !ReleaseDC(smhWindow, smhDeviceContext)) {	// Are We Able To Release The DC
            MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
            smhDeviceContext = NULL;										// Set DC To NULL
            lReturnCode = -1;
        }

        return lReturnCode;
    } // End of long Graphics::Uninitialize()

    void Graphics::WindowDimensions(unsigned long ulWidth, unsigned long ulHeight) {
        this->mulWindowWidth  = ulWidth;
        this->mulWindowHeight = ulHeight;
    }

    unsigned long Graphics::WindowWidth() const {
        return this->mulWindowWidth;
    }

    unsigned long Graphics::WindowHeight() const {
        return this->mulWindowHeight;
    }
    
    Scene* Graphics::getActiveScene() {
        return this->scene;
    }

    // Base::RenderScene() clears the depth and color buffer and starts
    // rendering the scene
    int Graphics::Render(float fDT) {
        static float runtimesec=0.0f;
        float syncfpsrate= 1.0f/60.0f;
        runtimesec+=fDT;

	    if(runtimesec>syncfpsrate){
	        
            this->scene->render(); //Render the scene

        	//adjust our runtimesec. Remember that by doing this, we tighten
        	//the sync and make overflow impossible.
    	    runtimesec-=syncfpsrate;

	    }//big sync if statement ends
        return 0;
    }
    
    // Base::SwapBuffers 
    void Graphics::SwapBuffer() {
        SwapBuffers(smhDeviceContext);
    }   
}
