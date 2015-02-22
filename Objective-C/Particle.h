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
@synthesize anchor = _anchor, item = _item, itemPosition = _itemPosition, armLength = _armLength, reach = _reach, accelerationRate = _accelerationRate, speedLimit = _speedLimit,rotationSpeed = _rotationSpeed,jumpStrength = _jumpStrength,limitSpeed = _limitSpeed, hasFriction = _hasFriction, hasGravity = _hasGravity, eye, center, up, goingUp = _goingUp;

bool ignoreNextjump = false;
- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    if (self) {
        [self reInit];
    } else {
        NSLog(@"%@ Not Initialised!",self);
        exit(0);
    }
    return self;
}

- (void)reInit {
    [super reInit];
    _hasGravity = TRUE;
    _hasFriction = TRUE;
    _accelerationRate = 0.1;
    _speedLimit = 0.20;
    _limitSpeed = false;
    _anchor = GLKVector3Make(0,0,0);
    _rotationSpeed = -0.1;
    _jumpStrength = 0.5;
    _item = nil;
    _itemPosition = self.getCenter;
    _squatLevel = 0;
    _goingUp = false;
    self.isAnimated = true;
}

- (float)ground {
    return body.radius - _squatLevel;
}
    


    
- (bool)isZero:(GLKVector3)v
{
    return ((v.x==0)&&(v.y==0)&&(v.z==0));
}
    
- (float)weight{
    return body.mass * self.physics.gravity;
}

-(void)animate
{
    if(!self.isAnimated) return;
    
    [self jumpTest];
    [self accelerate];
    [self manipulate];
}

- (void)jumpTest{
    if (_prepairingToJump || _goingUp || _squatLevel != 0){// || _squatLevel > 0){
        float i = body.radius / 200;
        if (_prepairingToJump){
            _squatLevel += i;
            if (_squatLevel >= self.ground/4-i) {
                [self jump];
                ignoreNextjump = true;
            }
        } else if (_squatLevel != 0 || _goingUp ){
            //if (_goingUp) {
            _squatLevel -= i*4;
            if (_squatLevel <= 0) {
                _squatLevel = 0;
                _goingUp = false;
                [self upStop];
            }
        }
    }
}



//float total, previousUV, previousLV = 0;


- (void)accelerate
{
    //GLKVector3 upThrust = GLKVector3Make( 0,0,0 );
    GLKVector3 g = (_hasGravity) ? [self.physics gravityFor:self] : GLKVector3Make(0,0,0);
    GLKVector3 n = (_hasGravity) ? [self.physics normalFor:self] : GLKVector3Make(0,0,0);
    GLKVector3 f = [self.physics frictionFor:self];
    GLKVector3 d = [self.physics dragFor:self];
    
    body.velocity = GLKVector3DivideScalar(body.velocity, 1 + [self.world µAt:self] + d.x);
    
    
    //GLKVector3 acceleration = GLKVector3Make(body.acceleration.x,0,body.acceleration.y);
    
    GLKVector3 forces = GLKVector3Make(
                                       (g.x + /* d.x + f.x +*/ n.x),
                                       (g.y +/* d.y + f.y +*/ n.y),//+body.acceleration.y,
                                       (g.z +/* d.z + f.z +*/ n.z)
                                 );
  //  GLKVector3 acceleration = GLKVector3Make(body.acceleration.x,body.acceleration.y,body.acceleration.z); //upward movement should be in the world updirection.
    
    //body.vMatrix = GLKMatrix3ScaleWithVector3(body.vMatrix,body.acceleration);
    
    body.forces.x += g.x + n.x;
    body.forces.y += g.y + n.y;
    body.forces.z += g.z + n.z;
    

    body.forces = GLKVector3Add(forces,GLKMatrix3MultiplyVector3( GLKMatrix3Transpose(body.orientation),body.acceleration));
    body.velocity = GLKVector3Add(body.velocity,body.forces);
//    body.velocity.x /= (1+d.x);
//    body.velocity.y /= (1+d.y);// + body.acceleration.y;
//    body.velocity.z /= (1+d.z);
    
    
    [self applyLimits];
    //if (!RMXVector3IsZero(body.velocity))
        body.position = GLKVector3Add(body.position,body.velocity);
    
    [self.world collisionTest:self];
    
    if([self.name isEqual:@"Main Observer"]) {
        [rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"\n gv %f , %f, %f\n nv %f , %f, %f\n fv %f , %f, %f\n Dv %f , %f, %f"
                                             ,g.x,g.y,g.z
                                             ,n.x,n.y,n.z
                                             ,f.x,f.y,f.z
                                             ,d.x,d.y,d.z]];
        [rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"\n FORCE: %f, %f, %f\n Accel: %f, %f, %f\n Veloc: %f, %f, %f\n Posit: %f, %f, %f",
                                             body.forces.x,body.forces.y,body.forces.z,
                                             body.acceleration.x,body.acceleration.y,body.acceleration.z,
                                             body.velocity.x, body.velocity.y,body.velocity.z,
                                             body.position.x, body.position.y, body.position.z ]];
    }

}



- (void)applyLimits
{
    //body.acceleration.y -= [self gravity];
    //Need to calculate this
    
    if (_limitSpeed){
        for (int i=0;i<3;++i)
            if (body.velocity.v[i] > _speedLimit){
                body.velocity.v[i] = _speedLimit;
            } else if (body.velocity.v[i] < -_speedLimit){
                body.velocity.v[i] = -_speedLimit;
            }
    }
}


-(void)manipulate
{
    
    if ( _item == nil ) return;
    _item->body.position = GLKVector3Add([self getCenter],
                                    GLKVector3MultiplyScalar(self.forwardVector,_armLength));
}

- (void)stop
{
   body.velocity = GLKVector3Make(0,0,0);
}

- (void)plusAngle:(float)theta up:(float)phi
{
    
    theta *= -_rotationSpeed*PI_OVER_180;
    phi *= _rotationSpeed*PI_OVER_180;
    
    
//    float lim = cos(0);
    
    body.angles.theta += theta;
    body.angles.phi += phi;
//    if (body.angles.phi + phi > lim){
//        phi = 0;
//        body.angles.phi = lim;
//    }else if (body.angles.phi + phi < -lim) {
//        phi = 0;
//        body.angles.phi = -lim;
//    }
    NSLog(@"Theta: %f, Phi: %f",body.angles.theta,body.angles.phi);
    
    
    
    body.orientation = GLKMatrix3RotateWithVector3(body.orientation, theta, GLKVector3Make(0,1,0));
    body.orientation = GLKMatrix3RotateWithVector3(body.orientation, phi, GLKMatrix3GetRow(body.orientation,0));
    
    [rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"Theta: %f, Phi: %f",theta,phi ]];
   // NSLog(@"Theta: %f, Phi: %f",theta,phi);
    /*
    //try this instead:
    GLKMatrix4 rm = GLKMatrix4MakeRotation(theta, upVector.x, upVector.y, upVector.z);
    forwardVector = GLKMatrix4MultiplyVector3WithTranslation(rm, upForwardVector);
    // and this
    GLKMatrix4 rm = GLKMatrix4MakeRotation(phi, self.upVector.x, self.upVector.y, self.upVector.z);
    self.forwardVector = GLKMatrix4MultiplyVector3WithTranslation(rm, [self forwardVector]);
    */
}





- (float)subtractToZero:(float)a b:(float)b{
    return (a < b) ? 0.0 : a - b;
}

    
- (bool)isGrounded{
    return (body.position.y <= body.radius);
}
    
- (void)push:(GLKVector3)direction
{
    body.velocity = GLKVector3Add(body.velocity, direction);
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
    else if (self.hasGravity&&_prepairingToJump && !_goingUp) {
        //_upV = GLKVector3Add(_upV, _jumpStrength*20);
        NSLog(@"Jump!");
        body.acceleration.y += _squatLevel + _accelerationRate + self.weight;// -_squatLevel * _jumpStrength;
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



- (GLKVector3)getEye
{
    return body.position;
}

- (GLKVector3)getCenter
{
    return GLKVector3Add(body.position,GLKMatrix3GetRow(body.orientation,2));
}

- (GLKVector3)getUp
{
    return GLKMatrix3GetRow(body.orientation,1);
}
- (void)accelerateForward:(float)v
{
    body.acceleration.z = v * _accelerationRate;
    
}

- (void)accelerateUp:(float)v
{
    body.acceleration.y = v * _accelerationRate;
    //  accelerate();
    //       accelerate(GLKVector3Make(0,velocity*accelerationRate,0));
}

- (void)accelerateLeft:(float)v
{
    body.acceleration.x = v * _accelerationRate;
    //accelerate();//accelerate(GLKVector3Make(velocity*accelerationRate,0,0));
}


- (void)forwardStop
{
    body.acceleration.z = 0;
}

- (void)upStop
{
    body.acceleration.y = 0;// -velocity.y;
}

- (void)leftStop
{
    body.acceleration.x = 0;// -velocity.x;
}




- (NSString*)describePosition {
    GLKVector3 drag = [self.physics dragFor:self];
    return [NSString stringWithFormat:@"\n   Pos: %f, %f, %f (%p)\n   Vel: %f, %f, %f (%p)\n   Acc: %f, %f, %f (%p)\n   µ: %f, %f, %f\n   g: %f, %f, %f\n  dF: %f, %f, %f\n  hasG: %i, hasF: %i, µ: %f", body.position.x,body.position.y,body.position.z,&body.position,
            body.velocity.x,body.velocity.y,body.velocity.z,&body.velocity
            ,body.acceleration.x,body.acceleration.y,body.acceleration.z,&body.acceleration,
            [self.physics frictionFor:self].x,[self.physics frictionFor:self].y,[self.physics frictionFor:self].z,
            [self.physics gravityFor:self].x,[self.physics gravityFor:self].y,[self.physics gravityFor:self].z,
            drag.x,drag.y,drag.z
            ,_hasGravity,_hasFriction, self.absFriction];
        
        //[rmxDebugger add:RMX_PARTICLE n:self t:[NSString stringWithFormat:@"%@",_name]];
        //[rmxDebugger add:RMX_PARTICLE n:_name t:[NSString stringWithFormat:@"%@ POSITION: %p | PX: %f, PY: %f, PZ: %f",_name,[self pMem],[self position].x,[self position].y,[self position].z ]];
}

- (void)debug {
    [super debug];
    [rmxDebugger add:RMX_PARTICLE n:self t:[self describePosition]];
}
- (float)absFriction{
    GLKVector3 µ = [self.physics frictionFor:self];
    
    return RMXGetSpeed(µ);
}

@end


