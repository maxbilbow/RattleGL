//
//  Header.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Header_h
#define OpenGL_2_0_Header_h


#endif

#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif

//#if __APPLE__
#include <TargetConditionals.h>
//#endif
//#if TARGET_IPHONE_SIMULATOR
//// iOS Simulator
//#elif TARGET_OS_IPHONE
//// iOS device
//#elif TARGET_OS_MAC
//// Other kinds of Mac OS
//#else
//// Unsupported platform
//#endif
#import "OpenGL 2.0-Bridging-Header.h"

float _dt;
#if __cplusplus
#include <iostream>
using namespace std;
#endif
#if TARGET_OS_IPHONE
#import <UIKit/UIKit.h>
#endif


#include <GLKit/GLKMatrix4.h>
#import <GLKit/GLKit.h>



#if TARGET_OS_IPHONE
#import <OpenGLES/ES1/gl.h>
#else
#include <GLUT/glut.h>
#endif

#include "RMXMaths.h"

#include "RMXEquations.h"

#include "RMXProtocols.h"
#include "RMXObject.h"

#include "RMXDebugger.h"
#include "RMXMouse.h"

#include "RMXObserver.h"


#include "RMXShapes.h"
#include "RMXShapeObject.h"
#include "RMXLightSource.h"
#include "RMXWorld.h"
#include "RMXArt.h"

#if TARGET_OS_IPHONE
#include "GameViewController.h"
#else
#include "RMXMenu.h"
#include "RMXWindow.h"
#include "RMXMouseProcessor.h"
#include "RMXKeyboardProcessor.h"
#include "RMXDisplayProcessor.h"

#endif



