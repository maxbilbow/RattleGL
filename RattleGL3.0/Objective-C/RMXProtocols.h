//
//  RMXObject.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 19/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//







//#import "RMXDPad.h"
//#import "RMXPointOfView.h"

@protocol RMXPointOfView
- (GLKMatrix4)makeLookAt:(GLKMatrix4(float eyeX,float eyeY, float eyeZ, float cx,float cy, float cz, float ux,float uy, float uz ))lookAt;
- (void)makeLookAtGl:(void(double eyeX,double eyeY, double eyeZ, double cx,double cy, double cz, double ux,double uy, double uz ))lookAt;
@property (readonly) NSString* viewDescription;

@end

@protocol RMXAnyInput

- (void)toggleFocus;
- (void)centerView:(void(int x, int y))center;
- (void)calibrateView:(int)x vert:(int)y;
- (bool)hasFocus;

@end

@protocol RMXMouseOwner <RMXAnyInput>
- (void)setMousePos:(int)x y:(int)y;
- (void)mouse2view:(int)x y:(int)y;
//- (void)setPos:(int)x v:(int)y;
- (GLKVector2)getMouse;
@end

@protocol RMXOrienrationProcessor

//- (void)rotate;
- (void)plusAngle:(float)theta up:(float)phi;
@end

















