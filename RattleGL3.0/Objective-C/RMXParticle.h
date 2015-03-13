//
//  RMXParticle.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXParticle_h
#define RattleGL3_0_RMXParticle_h


#endif



/*
 
 Particle
 */
@interface RMXParticle : RMXObject  <RMXOrienrationProcessor>
@property (readonly) RMXVector3 eye, center, up;
@property RMXShape * shape;
@property RMXVector3 anchor,itemPosition, rAxis;
@property float rotation, rotationCenterDistance;
@property RMXParticle  * item; //return 1?;
@property (readonly) float weight, ground;
@property (readonly) float upThrust, downForce;
@property float armLength, reach, accelerationRate, speedLimit, squatLevel, rotationSpeed, jumpStrength;
@property BOOL limitSpeed, hasFriction, hasGravity, prepairingToJump, goingUp, isRotating, isLightSource;
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
- (void)push:(RMXVector3)direction;
- (void)plusAngle:(float)theta up:(float)phi;
- (void)prepareToJump;
- (void)toggleGravity;
@end
