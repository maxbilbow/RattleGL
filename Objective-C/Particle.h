//
//  Particle.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#include "Physics.h"
//#include "Mouse.h"


@interface Particle : RMXObject  <RMXOrienrationProcessor>
@property (readonly) GLKVector3 eye, center, up;
@property GLKVector3 anchor,itemPosition;
@property Particle  * item;
@property float size, armLength, reach; //return 1?;
@property (readonly) GLKVector3 position, velocity,acceleration, forwardVector, upVector, leftVector, forwardV, upV, leftV;
@property (readonly) Physics * physics;
@property float accelerationRate, speedLimit, squatLevel,rotationSpeed,jumpStrength, mass;
@property BOOL limitSpeed, hasFriction, hasGravity, prepairingToJump, goingUp;
- (id)initWithName:(NSString*)name;
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
 Provides basic movement attributes to any object
 */
@implementation Particle
@synthesize anchor = _anchor, item = _item, itemPosition = _itemPosition, armLength = _armLength, reach = _reach, position = _position, velocity = _velocity ,acceleration = _acceleration, forwardVector = _forwardVector, upVector = _upVector, leftVector = _leftVector, forwardV = _forwardV, upV = _upV, leftV = _leftV, physics = _physics, accelerationRate = _accelerationRate, speedLimit = _speedLimit,rotationSpeed = _rotationSpeed,jumpStrength = _jumpStrength,limitSpeed = _limitSpeed, mass = _mass, hasFriction = _hasFriction, hasGravity = _hasGravity, eye, center, up, goingUp = _goingUp, size =_size;

bool ignoreNextjump = false;
- (id)initWithName:(NSString*)name
{
    self = [super initWithName:name];
    if (self) {
        _position = GLKVector3Make(0, 0, 0);
        
        _velocity = GLKVector3Make(0, 0, 0);
        _acceleration = GLKVector3Make(0, 0, 0);
        _forwardVector = GLKVector3Make(0, 0, 1);
        _upVector = GLKVector3Make(0, 1, 0);
        _leftVector = GLKVector3Make(1, 0, 0);
        _forwardV = GLKVector3Make(0, 0, 0);
        _upV = GLKVector3Make(0, 0, 0);
        _leftV = GLKVector3Make(0, 0, 0);
        _physics = [[Physics alloc] initWithName:name];
        _hasGravity = 1;
        _hasFriction = 1;
        _accelerationRate = 0.01;
        _speedLimit = 0.20;
        _limitSpeed = 1;
        _size = 10;
        _anchor = GLKVector3Make(0,0,0);
        _rotationSpeed = -0.1;
        _jumpStrength = 2.0;
        _item = nil;
        _itemPosition = self.getCenter;
        _squatLevel = 0;
        _goingUp = false;
        _mass = 1;
    
    } else {
        NSLog(@"%@ Not Initialised!",self);
        exit(0);
    }
    return self;
    
}

- (float)ground {
    return _size / 2;
}
    
- (void)calculatePosition:(GLKVector3)v
{
    if (v.y < [self ground] - _squatLevel)
        v.y = [self ground] - _squatLevel;
    _position = v;
    //[rmxDebugger add:1 n:_name t:[NSString stringWithFormat:@"x: %f, y: %f, z: %f, GROUND: %f",position.x,position.y,position.z,ground]];
}
    
- (bool)checkLimits:(GLKVector3)dV
{
    [rmxDebugger add:RMX_ERROR n:self t:@"Check Limits in Particle should be overriten"];
    return true;
}
    
- (bool)isZero:(GLKVector3)v
{
    return ((v.x==0)&&(v.y==0)&&(v.z==0));
}
    
   
- (bool)translate
{
    if ([self isZero:[self velocity]])
        return false;
    else
        [self calculatePosition:GLKVector3Add([self position],[self velocity])];
    return true;
}
    
-(void)animate
{
//    [super animate];
    if (_prepairingToJump || _goingUp || _squatLevel != 0){// || _squatLevel > 0){
        float i = 0.005;
        if (_prepairingToJump){
            _squatLevel += i;
            if (_squatLevel >= self.ground-i) {
                [self jump];
                ignoreNextjump = true;
            }
        } else if (_squatLevel != 0 || _goingUp ){
        //if (_goingUp) {
            _squatLevel -= i;
            if (_squatLevel <= 0) {
                _squatLevel = 0;
                _goingUp = false;
            }
        }
    }
        
    
            
    [self accelerate];
    _leftVector = GLKVector3CrossProduct(_forwardVector,_upVector);
    [self translate];
        //[rmxDebugger add:RMX_PA n:self t:@"no movement!"];
    [self manipulate];
}

-(void)manipulate
{
    
    if ( _item == nil ) return;
    //item->setAnchor(this->getPosition());
    [_item calculatePosition:GLKVector3Add([self getCenter],
                                    GLKVector3MultiplyScalar(_forwardVector,_armLength))];
}

- (void)stop
{
   _velocity = GLKVector3Make(0,0,0);
        //setRotationalVelocity(GLKVector3Make(0,0,0));
}

- (void)plusAngle:(float)theta up:(float)phi
{
    theta *= PI_OVER_180*_rotationSpeed;
    phi *= PI_OVER_180*_rotationSpeed;
    [self rotateAroundVerticle:theta];
    [self rotateAroundHorizontal:phi];
    //[rmxDebugger add:2 n:_name t:[NSString stringWithFormat:@"plusAngle: THETA %f, PHY: %f",theta,phi]];
}
    
-(void)rotateAroundVerticle:(float)theta
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(theta, [self upVector].x, [self upVector].y, [self upVector].z);
        //GLKMatrix4RotateWithVector3(GLKMatrix4MakeYRotation(theta), theta, getUpVector());
    _forwardVector = GLKMatrix4MultiplyVector3WithTranslation(rm, [self forwardVector]);
        //leftVector = GLKMatrix4MultiplyVector3WithTranslation(rm, leftVector);
    //free(rm);
}

-(void)rotateAroundHorizontal:(float)phi
{
    // leftVector = GLKVector3CrossProduct(getForwardVector(), getUpVector()); // Set the Right Vector
    GLKMatrix4 rm = GLKMatrix4MakeRotation(phi, [self leftVector].x, [self leftVector].y, [self leftVector].z);
    //upVector = GLKMatrix4MultiplyVector3WithTranslation(rm, upVector);
    _forwardVector = GLKMatrix4MultiplyVector3WithTranslation(rm, [self forwardVector]);
    
}

- (void)calculateVelocity:(GLKVector3)acceleration
{
    float forwardS = acceleration.z;
    float leftS = -acceleration.x;
    float upS = acceleration.y;
    _forwardV = GLKVector3MultiplyScalar(_forwardVector, forwardS);
    
    _upV = GLKVector3MultiplyScalar(_upVector, upS);
    _leftV = GLKVector3MultiplyScalar(_leftVector, leftS);
    
    _velocity = GLKVector3Add(_velocity,GLKVector3Add(_forwardV,_leftV)); // NSLog(@"%@",self.describePosition);
    _velocity = GLKVector3DivideScalar(_velocity,[self friction]); //NSLog(@"%@",self.describePosition);
    _velocity = GLKVector3Add(_upV,_velocity);// NSLog(@"%@",self.describePosition);
    
}

- (float)subtractToZero:(float)a b:(float)b{
    return (a < b) ? 0.0 : a - b;
}

- (void)addGravity:(float)g
{
    [_physics addGravity:g];
}
    

- (float)gravity {
    float dist = (_position.y - self.ground);
    double hh = exp2f(dist)/100;
    float scaler = ( hh > 10 ) ? 10 : 1 + hh;
    return _physics.gravity * _mass * _hasGravity / scaler;
}

- (float)friction {

    float dist = (_position.y - self.ground);
    double hh = exp2f(dist)/100;
    float scaler = ( hh > 10 ) ? 10 : 1 + hh;
    return [self isGrounded] ? 1 + self.physics.friction * _hasFriction :  1 + self.physics.friction * _hasFriction / scaler;
}

    
- (bool)isGrounded{
    const float lim = self.ground + 1.0;
    return (_position.y < lim );
}
    
- (void)push:(GLKVector3)direction
{
    _velocity = GLKVector3Add([self velocity], direction);
}

-(void)prepareToJump{
    _prepairingToJump = true;
}

- (void)jump
{
    if (ignoreNextjump) {
        ignoreNextjump = false;
        _goingUp = false;
        _prepairingToJump = false;
        return;
    }
    else if ([self hasGravity]&&_prepairingToJump && !_goingUp) {
        //_upV = GLKVector3Add(_upV, _jumpStrength*20);
        [self accelerateUp: _jumpStrength * (_squatLevel+1)];
        _goingUp = true;
        _prepairingToJump = false;
    }
   
}



- (void)toggleGravity
{
    _hasGravity = !_hasGravity;
}

- (void)toggleFriction
{
    _hasFriction = !_hasFriction;
}


- (GLKVector3)getLeftVector
{
    return _leftVector;
}


- (GLKVector3)getEye
{
    return _position;
}

- (GLKVector3)getCenter
{
    return GLKVector3Add(_position,_forwardVector);
}

- (GLKVector3)getUp
{
    return _upVector;
}
- (void)accelerateForward:(float)v
{
    _acceleration.z = v * _accelerationRate;
    
}

- (void)accelerateUp:(float)v
{
    _acceleration.y = v * _accelerationRate;
    //  accelerate();
    //       accelerate(GLKVector3Make(0,velocity*accelerationRate,0));
}

- (void)accelerateLeft:(float)v
{
    _acceleration.x = v * _accelerationRate;
    //accelerate();//accelerate(GLKVector3Make(velocity*accelerationRate,0,0));
}


- (void)forwardStop
{
    _acceleration.z = 0;
}

- (void)upStop
{
    _acceleration.y = 0;// -velocity.y;
}

- (void)leftStop
{
    _acceleration.x = 0;// -velocity.x;
}


- (void)accelerate
{
    _acceleration.y -= [self gravity];
    [self calculateVelocity:_acceleration]; //Need to calculate this
    
    if (_limitSpeed){
        for (int i=0;i<3;++i)
            if ([self velocity].v[i] > _speedLimit){
                //[rmxDebugger add:RMX_SIMPLE_PARTICLE n:_name t:[NSString stringWithFormat:@"speed%i = %f",i,[self velocity].v[i]]];
                [self velocity].v[i] = _speedLimit;
            } else if ([self velocity].v[i] < -_speedLimit){
                //[rmxDebugger add:RMX_SIMPLE_PARTICLE n:_name t:[NSString stringWithFormat:@"speed%i = %f",i,[self velocity].v[i]]];
                [self velocity].v[i] = -_speedLimit;
            } //else
        //[rmxDebugger add:RMX_SIMPLE_PARTICLE n:_name t:[NSString stringWithFormat:@"speed%i OK: %f",i,[self velocity].v[i]]];
    }
    
    
    [rmxDebugger add:RMX_ERROR n:@"Shapes" t:[NSString stringWithFormat:@"%@: VELY: %f, MEMY: %p",self.name,[self velocity].y,&_velocity]];
    
    
}

- (NSString*)describePosition {
    return [NSString stringWithFormat:@"\nPos: %f, %f, %f (%p)\nVel: %f, %f, %f (%p)\nAcc: %f, %f, %f (%p)\n", _position.x,_position.y,_position.z,&_position,_velocity.x,_velocity.y,_velocity.z,&_velocity,_acceleration.x,_acceleration.y,_acceleration.z,&_acceleration ];
        
        //[rmxDebugger add:RMX_PARTICLE n:self t:[NSString stringWithFormat:@"%@",_name]];
        //[rmxDebugger add:RMX_PARTICLE n:_name t:[NSString stringWithFormat:@"%@ POSITION: %p | PX: %f, PY: %f, PZ: %f",_name,[self pMem],[self position].x,[self position].y,[self position].z ]];
}

- (void)debug {
    [super debug];
    [rmxDebugger add:RMX_PARTICLE n:self t:[self describePosition]];
}


@end


