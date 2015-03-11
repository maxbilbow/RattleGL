//
//  Use this file to import your target's public headers that you would like to expose to Swift.
//

#ifndef OpenGL_2_0_Header_h
#define OpenGL_2_0_Header_h


#endif


//#import <TargetConditionals.h>
@import Foundation;
@import GLUT;
@import GLKit;
@import OpenGL;



#ifdef _WIN32
#	include <windows.h>
#else
#	include <sys/time.h>
#endif

//Swift
@class RMSPhysicsBody, RMXWorld, Main;
//Objc
@class RMXObject, RMXArt, RMXDebugger, RMXPhysics, RMXLightSource, RMXObserver, RMXMouse, RMXShapeObject, RMXParticle, RMXDPad, RMXMouseProcessor;


//
//#import <GLKit/GLKMatrix4.h>
//#import <GLKit/GLKit.h>

//#import "RattleGL3-0-Swift.h"
#import "RMXMaths.h"
#import "RMXEquations.h"
#import "RMXShapes.h"
#import "RMXObject.h"
#import "RMXProtocols.h"


#import "RMXDebugger.h"
#import "RMXMouse.h"

#import "RMXPhysics.h"
#import "RMXParticle.h"
#import "RMXObserver.h"

#import "RMXDrawable.h"
#import "RMXShapeObject.h"
#import "RMXLightSource.h"
//#import "RMXWorld.h"
#import "RMXArt.h"

//desktop below

//#import "RMXMenu.h"
#import "RMXWindow.h"
#import "RMXMouseProcessor.h"
#import "RMXKeyboardProcessor.h"
#import "RMXDisplayProcessor.h"
#import "run.h"
