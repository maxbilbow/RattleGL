//
//  Particle.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#include "Physics.h"
//#include "Mouse.h"



/*
 Provides basic movement attributes to any object
 */
@implementation Particle
@synthesize anchor = _anchor, item = _item, itemPosition = _itemPosition, armLength = _armLength, reach = _reach, position = _position, velocity = _velocity ,acceleration = _acceleration, forwardV = _forwardV, upV = _upV, leftV = _leftV, accelerationRate = _accelerationRate, speedLimit = _speedLimit,rotationSpeed = _rotationSpeed,jumpStrength = _jumpStrength,limitSpeed = _limitSpeed, mass = _mass, hasFriction = _hasFriction, hasGravity = _hasGravity, eye, center, up, goingUp = _goingUp, size =_size, isAnimated = _isAnimated;

bool ignoreNextjump = false;
- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    if (self) {
        _position = GLKVector3Make(0, 0, 0);
        _velocity = GLKVector3Make(0, 0, 0);
        _acceleration = GLKVector3Make(0, 0, 0);
        _forwardV = GLKVector3Make(0, 0, 0);
        _upV = GLKVector3Make(0, 0, 0);
        _leftV = GLKVector3Make(0, 0, 0);
        _hasGravity = 1;
        _hasFriction = 1;
        _accelerationRate = 0.02;
        _speedLimit = 0.20;
        _limitSpeed = true;
        _size = 10;
        _anchor = GLKVector3Make(0,0,0);
        _rotationSpeed = -0.1;
        _jumpStrength = 1.0;
        _item = nil;
        _itemPosition = self.getCenter;
        _squatLevel = 0;
        _goingUp = false;
        _mass = 1;
        _isAnimated = true;
    
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
//    if (v.y < [self ground] - _squatLevel)
//        v.y = [self ground] - _squatLevel;
    _position = v;
}
    

    
- (bool)isZero:(GLKVector3)v
{
    return ((v.x==0)&&(v.y==0)&&(v.z==0));
}
    
   

-(void)animate
{
    if(!_isAnimated) return;
    if (_prepairingToJump || _goingUp || _squatLevel != 0){// || _squatLevel > 0){
        float i = 0.05;
        if (_prepairingToJump){
            _squatLevel += i;
            if (_squatLevel >= self.ground/4-i) {
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
    self.leftVector = GLKVector3CrossProduct(self.forwardVector,self.upVector);
    [self translate];
        //[rmxDebugger add:RMX_PA n:self t:@"no movement!"];
    [self manipulate];
}

- (bool)translate
{
    if ([self isZero:[self velocity]])
        return false;
    else
        [self calculatePosition:GLKVector3Add(self.position,self.velocity)];
    return true;
}



- (void)calculateVelocity
{
    GLKVector3 upThrust = GLKVector3Make( 0,0,0 );//self.isGrounded ? GLKVector3MultiplyScalar(self.physics.upVector,-1) : GLKVector3Make(0,0,0);
    
    float forwardS = _acceleration.z - self.gravity * (self.physics.upVector.z + upThrust.z );
    float leftS = -_acceleration.x  - self.gravity * (self.physics.upVector.x + upThrust.x);
    float upS = _acceleration.y - self.gravity * (self.physics.upVector.y + upThrust.y);
    
    
    _forwardV = GLKVector3MultiplyScalar(self.forwardVector, forwardS);

    if (isGrounded) {
        upThrust = _velocity; //divide out forward and left vectors
        upThrust =            //Negate the remainng up vector
                                //negate the downward volocity so to remove it.
            _upV = GLKVector3MultiplyScalar(self.upVector,)
    }
    _upV = GLKVector3MultiplyScalar(self.upVector, upS);
    _leftV = GLKVector3MultiplyScalar(self.leftVector, leftS);
    
    _velocity = GLKVector3Add(_velocity,_forwardV);
    _velocity = GLKVector3Add(_velocity,_leftV);
    _velocity = GLKVector3Add(_velocity,_upV);
    _velocity = GLKVector3DivideScalar(_velocity,[self friction]);
    [rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"_upV: %f, %f, %f",_upV.x, _upV.y, _upV.z ]];

}


- (void)accelerate
{
    //_acceleration.y -= [self gravity];
    [self calculateVelocity]; //Need to calculate this
    
    if (_limitSpeed){
        for (int i=0;i<3;++i)
            if ([self velocity].v[i] > _speedLimit){
                [self velocity].v[i] = _speedLimit;
            } else if ([self velocity].v[i] < -_speedLimit){
                [self velocity].v[i] = -_speedLimit;
            }
    }
}


-(void)manipulate
{
    
    if ( _item == nil ) return;
    //item->setAnchor(this->getPosition());
    [_item calculatePosition:GLKVector3Add([self getCenter],
                                    GLKVector3MultiplyScalar(self.forwardVector,_armLength))];
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
    self.forwardVector = GLKMatrix4MultiplyVector3WithTranslation(rm, [self forwardVector]);
}

-(void)rotateAroundHorizontal:(float)phi
{
    GLKMatrix4 rm = GLKMatrix4MakeRotation(phi, [self leftVector].x, [self leftVector].y, [self leftVector].z);
    self.forwardVector = GLKMatrix4MultiplyVector3WithTranslation(rm, [self forwardVector]);
    
}



- (float)subtractToZero:(float)a b:(float)b{
    return (a < b) ? 0.0 : a - b;
}

- (void)addGravity:(float)g
{
    [self.physics addGravity:g];
}
    

- (double)gravity {
    float dist = (_position.y - self.ground);
    double hh = exp2f(dist)/100;
    float scaler = ( hh > 10 ) ? 10 : 1 + hh;
    return self.physics.gravity;// * _mass * _hasGravity / scaler;
}

- (double)friction {

    float dist = (_position.y - self.ground);
    double hh = exp2f(dist)/100;
    float scaler = ( hh > 10 ) ? 10 : 1 + hh;
    
    return 1;//[self isGrounded] ? 1 + self.physics.friction * _hasFriction :  1 + self.physics.friction * _hasFriction / scaler;
}

    
- (bool)isGrounded{
    const float lim = self.ground ;
    return (_position.y <= lim );
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
        [self accelerateUp: _jumpStrength * (_squatLevel)];
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
    return self.leftVector;
}


- (GLKVector3)getEye
{
    return _position;
}

- (GLKVector3)getCenter
{
    return GLKVector3Add(_position,self.forwardVector);
}

- (GLKVector3)getUp
{
    return self.upVector;
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


