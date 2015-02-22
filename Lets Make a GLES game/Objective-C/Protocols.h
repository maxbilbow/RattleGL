//
//  RMXObject.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 19/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_RMXObject_h
#define OpenGL_2_0_RMXObject_h


#endif

@class RMXWorld;
@class RMXPhysics;
@class Particle;
@class RMXObject;
@class RMXEventHandler;

@interface RMXDebugger : NSString
@property const bool isDebugging;
#ifdef TARGET_IOS
@property UIViewController * window;
#endif
-(void)add:(int)index n:(id)name t:(NSString*)text;//, ...;
@end

@protocol RMXObject
@property (readonly) NSString * name;
@property RMXObject * parent;
@property RMXWorld * world;
@property RMXPhysics * physics;
@property BOOL isAnimated;
#ifdef TARGET_IOS
@property UIViewController * uiView;
#endif
@property (readonly) RMXVector3 upVector, rightVector, forwardVector, leftVector;
- (id)initWithName:(NSString*)name parent:(RMXObject*)parent world:(RMXWorld*)world;
- (void)debug;
- (void)reInit;
@end

@interface RMXObject : NSObject <RMXObject> {
    @public RMXPhysicsBody body;
}

@end



@interface RMXPhysics : RMXObject
@property float gravity;

@property (readonly) GLKVector3 gVector;
- (RMXVector3)gravityFor:(Particle*)sender;
- (RMXVector3)frictionFor:(Particle*)sender;
- (RMXVector3)normalFor:(Particle*)sender;
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



/*
 
 Particle
 */
@interface Particle : RMXObject  <RMXOrienrationProcessor>
@property (readonly) GLKVector3 eye, center, up;
@property GLKVector3 anchor,itemPosition;
@property RMXObject  * item; //return 1?;
@property (readonly) float weight, ground;
@property float armLength, reach, accelerationRate, speedLimit, squatLevel,rotationSpeed,jumpStrength;
@property BOOL limitSpeed, hasFriction, hasGravity, prepairingToJump, goingUp;
- (void)accelerateForward:(float)velocity;
- (void)accelerateUp:(float)velocity;
- (void)accelerateLeft:(float)velocity;
- (void)forwardStop;
- (void)upStop;
- (void)leftStop;

- (NSString*)describePosition;

- (void)jump;
//- (void)setView;
- (void)debug;
- (void)animate;
- (void)manipulate;
- (bool)isGrounded;
- (void)push:(GLKVector3)direction;
- (void)plusAngle:(float)theta up:(float)phi;
- (void)prepareToJump;



@end


@protocol RMXDrawable <NSObject>
@property  GLKVector4 color;
@property  bool isRotating;
@property  GLKVector3 rAxis;
@property float rotation,  w;
@property GLenum type, gl_light;
@property void (*render)(float);
@property void(*shine)(GLenum, GLenum, const float*);

- (float*)getColorfv;
//- (void)RenderMe;
@end


/*
 Shpes
 */


@interface ShapeObject : Particle <RMXDrawable>


@end

@interface LightSource : ShapeObject

@end

@protocol RMXPointOfView
- (GLKMatrix4)makeLookAt:(GLKMatrix4(float eyeX,float eyeY, float eyeZ, float cx,float cy, float cz, float ux,float uy, float uz ))lookAt;
- (void)makeLookAtGl:(void(double eyeX,double eyeY, double eyeZ, double cx,double cy, double cz, double ux,double uy, double uz ))lookAt;
@property NSString* viewDescription;

@end

@interface RMXDPad : RMXObject
@property UIViewController* owner;
@end

@interface Mouse : RMXObject <RMXMouseOwner>
//@property bool focus;
@property int dx, dy;
@property GLKVector2 pos;
@property RMXDPad* dPad;
@property (getter=hasFocus) bool focus;
- (void)mouse2view:(int)x y:(int)y owner:(id)owner;
@end


@interface Observer : Particle <RMXMouseOwner,RMXPointOfView>
@property Mouse *mouse;
@property (readonly) GLKMatrix4 modelViewMatrix, projectionMatrix;
- (void)debug;
- (void)grabObject:(RMXObject*)i;
@end




/*
 Art draws the world.
 */

@interface RMXArt : RMXObject
//@property float x, y, z, d, r,g, b,k;
+ (RMXWorld*)initializeTestingEnvironment:(id)sender;
+ (void)randomObjects:(RMXWorld*)sender;
+ (void)drawAxis:(float**)colors world:(RMXWorld*)world;
+ (GLKVector4)rColor;
@end



@interface RMXWorld : RMXPhysics {
    Mouse* eventHandler;
}
@property NSMutableArray* sprites;
@property NSString* observerName;
@property float dt;
- (RMXObject*)closestObjectTo:(Particle*)sender;
- (void)animate;
- (void)insertSprite:(Particle*)sprite;
- (id)objectWithName:(NSString*)name;
- (void)setObserverWithId:(Particle*)object;
- (void)resetWorld;
- (float)µAt:(Particle*)someBody;
- (float)massDensityAt:(Particle*)someBody;
- (float)normalForceAt:(Particle*)someBody;
- (bool)collisionTest:(Particle*)sender;
@end






