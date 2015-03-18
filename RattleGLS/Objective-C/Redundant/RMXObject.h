//
//  RMXObject.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXObject_h
#define RattleGL3_0_RMXObject_h


#endif

@protocol RMXObjectProtocol
@property RMXObject * parent;
@property RMXWorld * world;
@end

@interface RMXObject : NSObject <RMXObjectProtocol>
@property BOOL isAnimated;
@property (readwrite)RMXVector3 position;
@property (readonly) NSString * name;
@property RMXObject * parent;
@property RMXWorld * world;
//@property (readonly) float altitude, positionX, positionY;
//@property RMXPhysicsBody body;
//@property (readonly) RMXVector3 upVector, rightVector, forwardVector, leftVector;
- (id)initWithName:(NSString*)name parent:(RMXObject*)parent world:(RMXWorld*)world;
- (void)plusAngle:(float)x y:(float)y;
- (void)debug;
@end
