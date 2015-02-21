//
//  Particle.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Particle_h
#define OpenGL_2_0_Particle_h


#endif

#include "Particle.h"
//#include "RMXEventProcessor.h"
#include "Mouse.h"


/*
 Provides basic movement attributes to any object
 */
@implementation Observer
    /* ATTRIBUTES 
     - Position
     - Velocity
     - (acceloration? Could be an external input)
     - LookAt
     - Up
     - Right
     */
@synthesize mouse, viewDescription;


    
- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    if (self) {
        mouse = [[Mouse alloc]initWithName:name parent:self world:world];
        //self.origin;
        self.armLength = 2;
        self.reach = self.size+6;
        self.mass = 1.5;
        //self.ground=1;
    }
    [self debug];
    return self;
}
    


bool _itemWasAnimated = false;
    
- (void)grabObject:(Particle*)i
{
    if (self.item == nil && GLKVector3Distance(self.position, i.position) < self.reach) {
        self.item = i;
        self.itemPosition = i.position;
        _itemWasAnimated = self.item.isAnimated;
        [self.item setIsAnimated:false]; //TODO: Make this not necessary
        self.armLength = GLKVector3Distance(self.getCenter, self.itemPosition);
    } else
        [self releaseObject];
}

-(void)releaseObject
{
    if (_itemWasAnimated)
        [self.item setIsAnimated:true];
    self.item = nil;
}

- (float)ground {
    [super ground];
    return [self size];
}

 
- (void)extendArmLength:(float)i
{
    if (self.armLength+i>1)
        self.armLength += i;
        
}

- (GLKMatrix4)makeLookAt:(GLKMatrix4(float eyeX,float eyeY, float eyeZ, float cx,float cy, float cz, float ux,float uy, float uz ))lookAt
{
    return (GLKMatrix4)lookAt(
                              [self getEye].x,   [self getEye].y,     [self getEye].z,
                              [self getCenter].x, [self getCenter].y, [self getCenter].z,
                              [self getUp].x,     [self getUp].y,     [self getUp].z
                              );

}

- (void)makeLookAtGl:(void(double eyeX,double eyeY, double eyeZ, double cx,double cy, double cz, double ux,double uy, double uz ))lookAt
{
     lookAt(
                              [self getEye].x,   [self getEye].y,     [self getEye].z,
                              [self getCenter].x, [self getCenter].y, [self getCenter].z,
                              [self getUp].x,     [self getUp].y,     [self getUp].z
                              );
    
}

- (GLKMatrix4)makePerspective:(GLKMatrix4(float fovyRadians, float aspect, float nearZ, float farZ))make
                            m:(float)m width:(int)width height:(int)height
{//, Number fovyRadians, Number aspect, Number nearZ, Number farZ){
    
    return (GLKMatrix4)make(60*m ,width / height, 1.0, 1000.0);
}
//- (void)setView
//{
//    [rmxDebugger add:RMX_OBSERVER n:self t:@"SetView in Observer not implemented"];
//}


- (void)setMousePos:(int)x y:(int)y{
    [mouse setMousePos:x y:y];
}
- (void)mouse2view:(int)x y:(int)y{
    [mouse mouse2view:x y:y owner:self];
}

- (GLKVector2)getMouse {
    return [mouse getMouse];
}


- (void)toggleFocus {
    [mouse toggleFocus];
}
- (void)centerView:(void(int x, int y))center {
    [mouse centerView:center];
}
- (void)calibrateView:(int)x vert:(int)y {
    [mouse calibrateView:x vert:y];
}
- (bool)hasFocus{
    return [mouse hasFocus];
}

- (void)debug{
    [super debug];
    [rmxDebugger add:RMX_OBSERVER n:self t: self.viewDescription];
}

- (NSString*)viewDescription {
    return [NSString stringWithFormat:@"\n      EYE x%f, y%f, z%f\n   CENTRE x%f, y%f, z%f\n      UP: x%f, y%f, z%f\n",
            [self getEye].x,[self getEye].y,[self getEye].z,
            [self getCenter].x,[self getCenter].y,[self getCenter].z,
            [self getUp].x,[self getUp].y,[self getUp].z];
}


@end
