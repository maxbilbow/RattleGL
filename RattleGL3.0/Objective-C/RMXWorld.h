//
//  RMXWorld.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXWorld_h
#define RattleGL3_0_RMXWorld_h


#endif

#define W_GRAVITY (0.01/50);
#define W_FRICTION 1.1;




@interface RMXWorld : RMXPhysics {
    RMXMouse* eventHandler;
}
@property NSMutableArray* sprites;
@property NSString* observerName;
@property (readonly) RMXObserver* observer;
@property float dt;
- (RMXObject*)closestObjectTo:(RMXParticle*)sender;
- (void)animate;
- (void)insertSprite:(RMXParticle*)sprite;
- (id)objectWithName:(NSString*)name;
- (void)setObserverWithId:(RMXParticle*)object;
- (void)resetWorld;
- (float)µAt:(RMXParticle*)someBody;
- (float)massDensityAt:(RMXParticle*)someBody;
- (float)normalForceAt:(RMXParticle*)someBody;
- (bool)collisionTest:(RMXParticle*)sender;
- (void)applyGravity:(BOOL)hasGrav;
@end


const RMXWorld *world;

