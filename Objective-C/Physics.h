//
//  Physics.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//






@implementation RMXPhysics



@synthesize gravity = _gravity, friction = _friction;//, hasFriction = _hasFriction, hasGravity = _hasGravity;
- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    if (self) {
        _gravity = 0.005;//U_GRAVITY;
        _friction = 0.1;
        self.upVector = GLKVector3Make(0,1,0);
        NSLog(@"init Physics");
    }
    return self;
}


- (void)addGravity:(float) g
{
    _gravity += g;
    if (_gravity<0)
        _gravity = 0;
    [rmxDebugger add:RMX_PHYSICS n:self t:[NSString stringWithFormat:@" / Gravity: %f", _gravity]];
}

- (void)applyGravityTo:(Particle*)particle{
    
//    float dist = (particle.position.y - self.ground);
//    double hh = exp2f(dist)/100;
//    float scaler = ( hh > 10 ) ? 10 : 1 + hh;
//    float g = self.physics.gravity * _mass * _hasGravity / scaler;
    
    self.upVector = GLKVector3MultiplyScalar(self.upVector, -_gravity);
    [particle setVelocity:GLKVector3Add(particle.velocity, self.upVector)];
}
- (GLKVector3)gVector:(BOOL)hasGravity {
    return GLKVector3MultiplyScalar(self.upVector,(hasGravity)?-_gravity:0);
}

- (void)addFriction:(float)f
{
    _friction += f;
    if (_friction<0)
        _friction = 0;
    [rmxDebugger add:RMX_PHYSICS n:self t:[NSString stringWithFormat:@" / Friction: %f",_friction]];
}

- (void)debug {
    [rmxDebugger add:RMX_PHYSICS n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}
    
@end;