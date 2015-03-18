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


#import "RattleGLS-Bridging-Header.h"
#import <RattleGL-Swift.h>
/*
 Provides basic movement attributes to any object
 */
@implementation RMXObserver
    /* ATTRIBUTES 
     - Position
     - Velocity
     - (acceloration? Could be an external input)
     - LookAt
     - Up
     - Right
     */


    
- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    if (self) {
       _mouse = [[RMXMouse alloc]initWithName:name parent:self world:world];
        //self.ground=1;
    }
    [self debug];
    return self;
}
    
- (void)reInit {
    [super reInit];
    
    //self.origin;
    self.armLength = 8;
    self.reach = 10;
    self.body.mass = 9;
    self.body.radius = 10;
    self.body.position = SCNVector3Make(0,0,-0.4);
    self.body.position = SCNVector3Make(20,self.body.radius,20);
    
    //self.body.position[2] = -0.4;
    //    body.position = GLKVector3Make(-10,body.radius,-10);
    self.jumpStrength = 1;
}

bool _itemWasAnimated = false;
    
- (void)grabObject:(RMXObject*)i
{
    
    if (self.item == nil && GLKVector3Distance(SCNVector3ToGLKVector3(self.body.position), SCNVector3ToGLKVector3(i.body.position)) < self.reach+i.body.radius) {
        self.item = i;
        self.itemPosition = i.body.position;
        _itemWasAnimated = self.item.isAnimated;
        //[self.item setIsAnimated:false]; //TODO: Make this not necessary
        self.armLength = GLKVector3Distance(GLKVector3Make(self.center[0],self.center[1],self.center[2]), SCNVector3ToGLKVector3(self.itemPosition));
    } else
        [self releaseObject];
}

-(void)releaseObject
{
    if (_itemWasAnimated)
        [self.item setIsAnimated:true];
    if ([self.item isKindOfClass:[RMXParticle class]]) {
       ((RMXParticle*) self.item).hasGravity = true;
        ((RMXParticle*) self.item).isAnimated = true;
    }
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
                              self.eye[0],      self.eye[1],    self.eye[2],
                              self.center[0],   self.center[1], self.center[2],
                              self.up[0],       self.up[1],     self.up[2]
                              );

}

- (void)makeLookAtGl:(void(double eyeX,double eyeY, double eyeZ, double cx,double cy, double cz, double ux,double uy, double uz ))lookAt
{
     lookAt(
            self.eye[0],      self.eye[1],    self.eye[2],
            self.center[0],   self.center[1], self.center[2],
            self.up[0],       self.up[1],     self.up[2]
                              );
    
}

- (GLKMatrix4)makePerspective:(GLKMatrix4(float fovyRadians, float aspect, float nearZ, float farZ))make
                            m:(float)m width:(int)width height:(int)height
{//, Number fovyRadians, Number aspect, Number nearZ, Number farZ){
    
    return (GLKMatrix4)make(60*m ,width / height, 1.0, 1000.0);
}



- (void)setMousePos:(int)x y:(int)y{
    [_mouse setMousePos:x y:y];
}
- (void)mouse2view:(int)x y:(int)y{
    [_mouse mouse2view:x y:y owner:self];
}

- (GLKVector2)getMouse {
    return [_mouse getMouse];
}


- (void)toggleFocus {
    [_mouse toggleFocus];
}
- (void)centerView:(void(int x, int y))center {
    [_mouse centerView:center];
}
- (void)calibrateView:(int)x vert:(int)y {
    [_mouse calibrateView:x vert:y];
}
- (bool)hasFocus{
    return [_mouse hasFocus];
}

- (void)debug{
//    [super debug];
//    [rmxDebugger add:RMX_OBSERVER n:self t: self.describePosition];
//    [rmxDebugger add:RMX_OBSERVER n:self t: self.viewDescription];
}

- (NSString*)viewDescription {
    return [NSString stringWithFormat:@"\n      EYE x%f, y%f, z%f\n   CENTRE x%f, y%f, z%f\n      UP: x%f, y%f, z%f\n",
            self.eye[0],self.eye[1],self.eye[2],
            self.center[0],self.center[1],self.center[2],
            self.up[0],self.up[1],self.up[2]];
}


- (RMXMatrix4)modelViewMatrix {
    
    SCNMatrix4 m = SCNMatrix4Translate(self.body.orientation, self.body.velocity.x, self.body.velocity.y, self.body.velocity.z);
//    (
//                                             GLKVector4MakeWithVector3(self.eye, 0),
//                                             GLKVector4MakeWithVector3(self.center, 0),
//                                             GLKVector4MakeWithVector3(self.up, 0),
//                                             GLKVector4MakeWithVector3(GLKVector3Make(0,0,0), 1)
//                                             );
    return m;
}

- (RMXMatrix4)projectionMatrix {
//
//    float aspect = fabsf(self.uiView.view.bounds.size.width / self.uiView.view.bounds.size.height);
//    return GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0f), aspect, 0.1f, 100.0f);
//#else
    return SCNMatrix4Identity;
}

- (void)throwItem:(float)strength
{
    if (self.item == nil)return;
    
    self.item.body.velocity = RMXVector3Add3(self.body.velocity,RMXVector3MultiplyScalar(self.forwardVector,strength),RMXVector3Zero());
    self.item.isAnimated = true;
    self.item = nil;
}

@end
