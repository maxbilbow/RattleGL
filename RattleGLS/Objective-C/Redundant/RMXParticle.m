//
//  Particle.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#import "RattleGLS-Bridging-Header.h"
#import <RattleGL-Swift.h>
@implementation RMXParticle

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
    
    self.shape = [RMXShape Shape:self world:self.world render: nil];
    _hasGravity = TRUE;
    _hasFriction = TRUE;
   
    _accelerationRate = 0.4;
    _speedLimit = 1.0;
    _limitSpeed = false;
    _anchor = SCNVector3Make(0,0,0);

    _rotationSpeed = -0.1;
    _jumpStrength = 1;
    _item = nil;
    _itemPosition = self.center;
    _squatLevel = 0;
    _goingUp = false;
//    if (self.body.position.y < self.ground) {
//        self.body.position.y = self.body.radius;
//    }
    self.isAnimated = true;
    
    self.rAxis = SCNVector3Make(0,0,1);
    self.rotation = 0;
    self.isRotating = false;
    self.rotationCenterDistance = 0;
}

- (float)ground {
    return self.body.radius - _squatLevel;
}
    


    
- (bool)isZero:(GLKVector3)v
{
    return ((v.x==0)&&(v.y==0)&&(v.z==0));
}
    
- (float)weight{
    return self.body.mass * self.physics.gravity;
}

-(void)animate
{
    if(self.isAnimated) {
    
        
        
        [self jumpTest];
        [self accelerate];
        [self manipulate];
    }
    
    if (_isRotating) {
        self.rotation += self.rotationSpeed/self.rotationCenterDistance;
        GLKVector4 temp = RMXSomeCircle(self.rotation, self.rotationCenterDistance * 2);
        self.body.position = SCNVector3Make(temp.x-self.rotationCenterDistance,temp.y,0);
    }
    [self.shape draw];
    
    
}

- (void)jumpTest{
    if (_prepairingToJump || _goingUp || _squatLevel != 0){// || _squatLevel > 0){
        float i = self.body.radius / 200;
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
    RMXVector3 g = (_hasGravity) ? [self.physics gravityFor:self] : RMXVector3Zero();
    RMXVector3 n = (_hasGravity) ? [self.physics normalFor:self] : RMXVector3Zero();
    RMXVector3 f = [self.physics frictionFor:self];// : GLKVector3Make(1,1,1);
    RMXVector3 d = [self.physics dragFor:self];// : GLKVector3Make(1,1,1);
    

//#if TARGET_OS_IPHONE
//    self.body.velocity = GLKVector3DivideScalar(self.body.velocity, 1 );
//#else
    self.body.velocity = RMXVector3DivideScalar(self.body.velocity, 1 + [self.world µAt:self] + d.x );
    
    
    RMXVector3 forces = SCNVector3Make(
                                       (g.x + /* d.x + f.x +*/ n.x),
                                       (g.y +/* d.y + f.y +*/ n.y),//+body.acceleration.y,
                                       (g.z +/* d.z + f.z +*/ n.z)
                                 );
    
//    self.body.forces.x += g.x + n.x;
//    self.body.forces.y += g.y + n.y;
//    self.body.forces.z += g.z + n.z;
    
    
    self.body.forces = RMXVector3Add(forces,RMXMatrix4MultiplyVector3( RMXMatrix4Transpose(self.body.orientation),self.body.acceleration));
    self.body.velocity = RMXVector3Add(self.body.velocity,self.body.forces);
   
    
    
    [self.world collisionTest:self];

    [self applyLimits];
    self.body.position = RMXVector3Add(self.body.position,self.body.velocity);
    
    
    
    if([self.name isEqual:@"Main Observer"]) {
        if (RMX_DEBUGGING) NSLog(@"\n gv %f , %f, %f\n nv %f , %f, %f\n fv %f , %f, %f\n Dv %f , %f, %f"
                                             ,g.x,g.y,g.z
                                             ,n.x,n.y,n.z
                                             ,f.x,f.y,f.z
                                 ,d.x,d.y,d.z);
        if (RMX_DEBUGGING) NSLog(@"\n FORCE: %f, %f, %f\n Accel: %f, %f, %f\n Veloc: %f, %f, %f\n Posit: %f, %f, %f",
                                             self.body.forces.x,self.body.forces.y,self.body.forces.z,
                                             self.body.acceleration.x,self.body.acceleration.y,self.body.acceleration.z,
                                             self.body.velocity.x, self.body.velocity.y,self.body.velocity.z,
                                 self.body.position.x, self.body.position.y, self.body.position.z );
    }

}



- (void)applyLimits
{
    //body.acceleration.y -= [self gravity];
    //Need to calculate this
    /*
    if (_limitSpeed){
            if (self.body.velocity.x > _speedLimit){
                self.body.velocity.x = _speedLimit;
            } else if (self.body.velocity.x < -_speedLimit){
                self.body.velocity.x = -_speedLimit;
            }
        if (self.body.velocity.y > _speedLimit){
            self.body.velocity.y = _speedLimit;
        } else if (self.body.velocity.y < -_speedLimit){
            self.body.velocity.y = -_speedLimit;
        }
        if (self.body.velocity.z > _speedLimit){
            self.body.velocity.z = _speedLimit;
        } else if (self.body.velocity.z < -_speedLimit){
            self.body.velocity.z = -_speedLimit;
        }
    } */
}


-(void)manipulate
{
    
    if ( _item == nil ) return;
    _item.body.position = RMXVector3Add(self.center,
                                    RMXVector3MultiplyScalar(self.forwardVector,_armLength+_item.body.radius));
    //NSLog(@"manipulating: %@:\n%@",((RMXParticle*)_item).name,((RMXParticle*)_item).describePosition);
}

- (void)stop
{
   self.body.velocity = SCNVector3Make(0,0,0);
}

- (void)plusAngle:(float)theta up:(float)phi
{
    //body.position.z += theta; return;
    theta *= -_rotationSpeed*PI_OVER_180;
    phi *= _rotationSpeed*PI_OVER_180;
    
    
//    float lim = cos(0);
    
    self.body.theta += theta;
    self.body.phi += phi;
//    if (self.body.angles.phi + phi > lim){
//        phi = 0;
//        self.body.angles.phi = lim;
//    }else if (self.body.angles.phi + phi < -lim) {
//        phi = 0;
//        self.body.angles.phi = -lim;
//    }
//    NSLog(@"Theta: %f, Phi: %f",body.angles.theta,body.angles.phi);
    
    
    
    self.body.orientation = SCNMatrix4Rotate(self.body.orientation, theta, 0, 1, 0);
    self.body.orientation = SCNMatrix4Rotate(self.body.orientation, phi, self.body.leftVector.x, self.body.leftVector.y, self.body.leftVector.z);
    
    //[rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"Theta: %f, Phi: %f",self.body.theta,self.body.phi ]];
   
}





- (float)subtractToZero:(float)a b:(float)b{
    return (a < b) ? 0.0 : a - b;
}

    
- (bool)isGrounded{
    return (self.body.position.y <= self.body.radius);
}
    
- (void)push:(RMXVector3)direction
{
    self.body.velocity = RMXVector3Add(self.body.velocity, direction);
}

- (float)upThrust {
    return self.body.velocity.y;
}

- (float)downForce {
    return self.body.forces.y;
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
        //NSLog(@"Jump!");
        float y = self.weight*_jumpStrength * self.body.radius / _squatLevel;
        self.body.acceleration = RMXVector3Add(self.body.acceleration, SCNVector3Make(0,y,0));
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



- (RMXVector3)eye
{
    return self.body.position;
}

- (RMXVector3)center
{
    return RMXVector3Add(self.body.position,self.forwardVector);
}

- (RMXVector3)up
{
    //vector_float3 up = { 0,1,0};// self.body.orientation.m21,body.orientation.m22,body.orientation.m23 };
    //GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(self.body.orientation),1);
    return SCNVector3Make(0,1,0);
}
- (void)accelerateForward:(float)v
{
    float z = v * _accelerationRate;
    self.body.acceleration = SCNVector3Make(0,0,z);
    
}

- (void)accelerateUp:(float)v
{
    float y = v * _accelerationRate;
    self.body.acceleration = SCNVector3Make(0,y,0);// * !self.hasGravity;
    //  accelerate();
    //       accelerate(GLKVector3Make(0,velocity*accelerationRate,0));
}

- (void)accelerateLeft:(float)v
{
    float x = v * _accelerationRate;

    self.body.acceleration = SCNVector3Make(x,0,0);
    //accelerate();//accelerate(GLKVector3Make(velocity*accelerationRate,0,0));
}


- (void)forwardStop
{
    RMXVector3 v = self.body.acceleration;
    self.body.acceleration = SCNVector3Make(v.x, v.y, 0);
}

- (void)upStop
{
    RMXVector3 v = self.body.acceleration;
    self.body.acceleration = SCNVector3Make(v.x, 0, v.z);// -velocity.y;
}

- (void)leftStop
{
    RMXVector3 v = self.body.acceleration;
    self.body.acceleration = SCNVector3Make(0, v.y, v.z);// -velocity.x;
}




- (NSString*)describePosition {
    RMXVector3 drag = [self.physics dragFor:self];
    return [NSString stringWithFormat:@"\n   Pos: %f, %f, %f (%p)\n   Vel: %f, %f, %f (%p)\n   Acc: %f, %f, %f (%p)\n   µ: %f, %f, %f\n   g: %f, %f, %f\n  dF: %f, %f, %f\n  hasG: %i, hasF: %i, µ: %f", self.body.position.x,self.body.position.y,self.body.position.z,self.body,
            self.body.velocity.x,self.body.velocity.y,self.body.velocity.z,self.body
            ,self.body.acceleration.x,self.body.acceleration.y,self.body.acceleration.z,self.body,
            [self.physics frictionFor:self].x,[self.physics frictionFor:self].y,[self.physics frictionFor:self].z,
            [self.physics gravityFor:self].x,[self.physics gravityFor:self].y,[self.physics gravityFor:self].z,
            drag.x,drag.y,drag.z
            ,_hasGravity,_hasFriction, self.absFriction];
        
        //[rmxDebugger add:RMX_PARTICLE n:self t:[NSString stringWithFormat:@"%@",_name]];
        //[rmxDebugger add:RMX_PARTICLE n:_name t:[NSString stringWithFormat:@"%@ POSITION: %p | PX: %f, PY: %f, PZ: %f",_name,[self pMem],[self position].x,[self position].y,[self position].z ]];
}

- (void)debug {
    [super debug];
   // [rmxDebugger add:RMX_PARTICLE n:self t:[self describePosition]];
}
- (float)absFriction{
    RMXVector3 µ = [self.physics frictionFor:self];
    
    return RMXGetSpeed(µ);
}

- (BOOL)isLightSource {
    return (_shape != nil && _shape.isLight);
}
@end


