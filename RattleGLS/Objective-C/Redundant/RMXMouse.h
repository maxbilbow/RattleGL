//
//  RMXMouse.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXMouse_h
#define RattleGL3_0_RMXMouse_h


#endif

@interface RMXMouse <RMXMouseOwner>
//@property bool focus;
@property RMXObject * parent;
@property RMXWorld * world;
@property int dx, dy;
@property GLKVector2 pos;
@property RMXDPad* dPad;
@property (getter=hasFocus) bool focus;
- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world;
- (void)mouse2view:(int)x y:(int)y;
@end
