
//
//  RMXObserver.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXObserver_h
#define RattleGL3_0_RMXObserver_h


#endif

@interface RMXObserver : RMXParticle <RMXMouseOwner,RMXPointOfView>
@property RMXMouse *mouse;
@property (readonly) RMXMatrix4 modelViewMatrix, projectionMatrix;
- (void)debug;
- (void)grabObject:(RMXObject*)i;
- (void)throwItem:(float)strength;
- (void)extendArmLength:(float)i;
@end

//RMXObserver* observer;// = * Observer();