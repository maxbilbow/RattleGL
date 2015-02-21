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

@interface RMXDebugger : NSString
@property const bool isDebugging;

-(void)add:(int)index n:(id)name t:(NSString*)text;//, ...;
@end


@interface RMXObject : NSObject
@property (readonly) NSString * name;
@property RMXObject * parent;
@property (readonly) RMXWorld * world;
@property RMXPhysics * physics;
@property GLKVector3 forwardVector, upVector, leftVector;
@property float radius;
- (id)initWithName:(NSString*)name parent:(RMXObject*)parent world:(RMXWorld*)world;
- (void)debug;
@end
@interface RMXPhysics : RMXObject
@property float gravity, friction;
@property (readonly) GLKVector3 gVector;
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
- (void)rotateAroundVerticle:(float)theta;
- (void)rotateAroundHorizontal:(float)phi;
- (void)plusAngle:(float)theta up:(float)phi;
@end



/*
 
 Particle
 */
@interface Particle : RMXObject  <RMXOrienrationProcessor>
@property (readonly) GLKVector3 eye, center, up;
@property GLKVector3 anchor,itemPosition;
@property Particle  * item;
@property float size, armLength, reach; //return 1?;
@property GLKVector3 position, velocity,acceleration, forwardV, upV, leftV;
@property float accelerationRate, speedLimit, squatLevel,rotationSpeed,jumpStrength, mass;
@property BOOL limitSpeed, hasFriction, hasGravity, prepairingToJump, goingUp, isAnimated;
- (void)calculateVelocity:(GLKVector3)acceleration;

- (void)calculatePosition:(GLKVector3)v;
- (void)accelerateForward:(float)velocity;
- (void)accelerateUp:(float)velocity;
- (void)accelerateLeft:(float)velocity;
- (void)forwardStop;
- (void)upStop;
- (void)leftStop;

- (NSString*)describePosition;
- (float)ground;

- (void)jump;
//- (void)setView;
- (void)debug;
- (void)animate;
- (void)manipulate;
- (bool)translate;
- (void)addGravity:(float)g;
- (bool)isGrounded;
- (void)push:(GLKVector3)direction;
- (void)plusAngle:(float)theta up:(float)phi;
- (void)prepareToJump;


@end



/*
 Shpes
 */


@interface ShapeObject : Particle
@property float rotation;
@property  GLKVector4 color;// = GLKVector4Make(1,1, 1, 10);
@property  bool isRotating;
@property  GLKVector3 rAxis;
- (float*)getColorfv;
@end


@protocol RMXPointOfView
- (GLKMatrix4)makeLookAt:(GLKMatrix4(float eyeX,float eyeY, float eyeZ, float cx,float cy, float cz, float ux,float uy, float uz ))lookAt;
- (void)makeLookAtGl:(void(double eyeX,double eyeY, double eyeZ, double cx,double cy, double cz, double ux,double uy, double uz ))lookAt;
@property NSString* viewDescription;
@end

@interface Mouse : RMXObject <RMXMouseOwner>
//@property bool focus;
@property int dx, dy;
@property GLKVector2 pos;
@property (getter=hasFocus) bool focus;
- (void)mouse2view:(int)x y:(int)y owner:(id)owner;
@end


@interface Observer : Particle <RMXMouseOwner,RMXPointOfView>
@property Mouse *mouse;
- (void)debug;
@end

@interface LightSource : ShapeObject
@property float w;
@end


/*
 Art draws the world.
 */

@interface Art : RMXObject
@property float x, y, z, d, r,g, b,k;
@property ShapeObject * sh, * sh2, * sh3, *sh4;
@end

@interface RMXWorld : RMXObject
@property NSMutableArray* sprites;
@property NSString* observerName;
@property float dt;
- (id)closestObject;
- (void)animate;
- (void)insertSprite:(Particle*)sprite;
- (id)objectWithName:(NSString*)name;
- (void)setObserverWithId:(Particle*)object;
@end

@implementation RMXObject : NSObject
@synthesize name = _name, parent = _parent, world = _world, physics = _physics, radius = _radius, forwardVector = _forwardVector, upVector = _upVector, leftVector = _leftVector;
- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world{
    self = [super init];
    _parent = parent;
    _world = world;
    _physics = (world != nil || parent!=nil) ? world.physics : [[RMXPhysics alloc]initWithName:@"Root Node" parent:self world:nil];
    _forwardVector = GLKVector3Make(0, 0, 1);
    _upVector = GLKVector3Make(0, 1, 0);
    _leftVector = GLKVector3Make(1, 0, 0);
    _name = name;
    _radius = 0;
    return self;
}
- (void)debug {
    //[rmxDebugger add:RMX_ERROR n:self t:_name];
}
@end



