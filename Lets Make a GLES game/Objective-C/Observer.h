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
       // mouse = [[RMXEventHandler alloc]initWithName:name parent:self world:world];
        //self.ground=1;
    }
    [self debug];
    return self;
}
    
- (void)reInit {
    [super reInit];
    
    //self.origin;
    self.armLength = 6;
    self.reach = 8;
    body = RMXPhyisicsBodyMake(0.5,10);
    body.position = GLKVector3Make(0,0,-0.4);
    body.dragC = 0.1;
    body.dragArea = PI * body.radius;
    //body.dragC = 2;
}

bool _itemWasAnimated = false;
    
- (void)grabObject:(RMXObject*)i
{
    
    if (self.item == nil && GLKVector3Distance(body.position, i->body.position) < self.reach) {
        self.item = i;
        self.itemPosition = i->body.position;
        _itemWasAnimated = self.item.isAnimated;
        //[self.item setIsAnimated:false]; //TODO: Make this not necessary
        self.armLength = GLKVector3Distance(self.center, self.itemPosition);
    } else
        [self releaseObject];
   // NSLog(@"Grabbing: %@:\n%@",((Particle*)self.item).name,((Particle*)self.item).describePosition);
}

-(void)releaseObject
{
    if (_itemWasAnimated)
        [self.item setIsAnimated:true];
    self.item = nil;
}

- (float)ground {
    return [super ground];
}

 
- (void)extendArmLength:(float)i
{
    if (self.armLength+i>1)
        self.armLength += i;
        
}

- (GLKMatrix4)makeLookAt:(GLKMatrix4(float eyeX,float eyeY, float eyeZ, float cx,float cy, float cz, float ux,float uy, float uz ))lookAt
{
    return (GLKMatrix4)lookAt(
                              [self eye].x,   [self eye].y,     [self eye].z,
                              [self center].x, [self center].y, [self center].z,
                              [self up].x,     [self up].y,     [self up].z
                              );

}

- (void)makeLookAtGl:(void(double eyeX,double eyeY, double eyeZ, double cx,double cy, double cz, double ux,double uy, double uz ))lookAt
{
     lookAt(
                              [self eye].x,   [self eye].y,     [self eye].z,
                              [self center].x, [self center].y, [self center].z,
                              [self up].x,     [self up].y,     [self up].z
                              );
    
}

- (GLKMatrix4)makePerspective:(GLKMatrix4(float fovyRadians, float aspect, float nearZ, float farZ))make
                            m:(float)m width:(int)width height:(int)height
{//, Number fovyRadians, Number aspect, Number nearZ, Number farZ){
    
    return (GLKMatrix4)make(60*m ,width / height, 1.0, 1000.0);
}



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
//    [super debug];
    [rmxDebugger add:RMX_OBSERVER n:self t: self.describePosition];
    [rmxDebugger add:RMX_OBSERVER n:self t: self.viewDescription];
}

- (NSString*)viewDescription {
    return [NSString stringWithFormat:@"\n      EYE x%f, y%f, z%f\n   CENTRE x%f, y%f, z%f\n      UP: x%f, y%f, z%f\n",
            [self eye].x,[self eye].y,[self eye].z,
            [self center].x,[self center].y,[self center].z,
            [self up].x,[self up].y,[self up].z];
}


- (GLKMatrix4)modelViewMatrix {
    
    GLKMatrix4 m = GLKMatrix4TranslateWithVector3(body.orientation, body.velocity);
//    (
//                                             GLKVector4MakeWithVector3(self.eye, 0),
//                                             GLKVector4MakeWithVector3(self.center, 0),
//                                             GLKVector4MakeWithVector3(self.up, 0),
//                                             GLKVector4MakeWithVector3(GLKVector3Make(0,0,0), 1)
//                                             );
    return m;
}

- (GLKMatrix4)projectionMatrix {
    float aspect = fabsf(self.uiView.view.bounds.size.width / self.uiView.view.bounds.size.height);
    return GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0f), aspect, 0.1f, 100.0f);
}


@end
