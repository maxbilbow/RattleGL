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
#include "TargetConditionals.h"
//#if TARGET_IPHONE_SIMULATOR
//// iOS Simulator
//#elif TARGET_OS_IPHONE
//// iOS device
//#elif TARGET_OS_MAC
//// Other kinds of Mac OS
//#else
//// Unsupported platform
//#endif


float _dt;
#ifdef __cplusplus
#include <iostream>
using namespace std;
#endif
#ifdef TARGET_IOS_IPHONE
#import <UIKit/UIKit.h>
#endif


#include <GLKit/GLKMatrix4.h>
#import <GLKit/GLKit.h>

#if TARGET_OS_X
#include <GLUT/glut.h>
#endif

#if TARGET_IOS_IPHONE
#import <OpenGLES/ES1/gl.h>
#endif

#include "RMXMaths.h"

#include "RMXEquations.h"

#include "Protocols.h"
#include "RMXObject.h"

#include "RMXDebugger.h"
#include "Mouse.h"

#include "Observer.h"

#include "World.h"
#include "Art.h"

#if TARGET_IOS_IPHONE
#include "GameViewController.h"
#endif



#if TARGER_OS_X

#include "Window.h"
#include "MouseProcessor.h"
#include "KeyboardProcessor.h"
#include "DisplayProcessor.h"

#endif



