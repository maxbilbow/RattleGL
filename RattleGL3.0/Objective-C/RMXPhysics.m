//
//  Physics.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//



#import "RattleGLS-Bridging-Header.h"
#import <RattleGL-Swift.h>

@implementation RMXPhysics

- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    if (self) {
        _gravity = 0.098;//U_GRAVITY;
        NSLog(@"init Physics");
    }
    return self;
}


- (void)applyGravityTo:(RMXParticle*)particle{
    NSLog(@"Probably should delete this: (void)applyGravityTo:(RMXParticle*)particle");
    exit(0);
   
}
- (RMXVector3)gVector:(BOOL)hasGravity {
    return RMXVector3MultiplyScalar(self.upVector,(hasGravity)?-_gravity:0);
}



- (void)debug {
    //[rmxDebugger add:RMX_PHYSICS n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}



- (RMXVector3)gravityFor:(RMXParticle*)sender {
    return RMXVector3MultiplyScalar(self.upVector,-sender.weight);
}



- (RMXVector3)dragFor:(RMXParticle*)sender{
    float dragC = sender.body.dragC;
    float rho = 0.005 * [self.world massDensityAt:sender];
    float u = RMXGetSpeed(sender.body.velocity);// RMXScaler3FromMatrix3(body.vMatrix);
    float area = sender.body.dragArea;//PI * sender->body.radius * sender->body.radius;
    RMXVector3 v;
    //for (int i = 0;i<3;++i){
        v.x = 0.5 * rho * u*u * dragC * area;
   // }
    
    return v;
}

- (RMXVector3)frictionFor:(RMXParticle*)sender {
    float µ = [self.world µAt:sender];
    
    return SCNVector3Make(µ, µ, µ);//TODO
    
    //return RMXMatrix3MultiplyScalarAndSpeed(sender.body.vMatrix,µ); //RMXVector3Add4(GLKVector3Make(0,0,0),µX,µY,µZ);
}

- (RMXVector3)normalFor:(RMXParticle*)sender{
    float normal = [self.world normalForceAt:sender];
    return RMXVector3MultiplyScalar(self.upVector,normal);// : GLKVector3Make(0,0,0);
}

@end;