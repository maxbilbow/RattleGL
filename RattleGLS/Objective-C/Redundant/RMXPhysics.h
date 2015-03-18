//
//  RMXPhysics.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXPhysics_h
#define RattleGL3_0_RMXPhysics_h


#endif


@interface RMXPhysics : RMXObject
@property float gravity;

@property (readonly) RMXVector3 gVector;
- (RMXVector3)gravityFor:(RMXParticle*)sender;
- (RMXVector3)frictionFor:(RMXParticle*)sender;
- (RMXVector3)normalFor:(RMXParticle*)sender;
- (RMXVector3)dragFor:(RMXParticle*)sender;
@end



