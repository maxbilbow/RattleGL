//
//  RMXObject.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 21/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_RMXObject_h
#define OpenGL_2_0_RMXObject_h


#endif

@implementation RMXObject : NSObject
@synthesize name = _name, parent = _parent, world = _world, physics = _physics, isAnimated = _isAnimated;
- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world{
    self = [super init];
    _parent = parent;
    _world = world;
    _name = name;
    _physics = (world != nil) ? world.physics : [[RMXPhysics alloc]initWithName:@"Root Node" parent:parent world: [self isKindOfClass:[RMXWorld class]] ? (RMXWorld*) self : nil];
    [self reInit];
        return self;
}

- (void)reInit {
    body = RMXPhyisicsBodyMake(1, 1);
}
- (void)debug {
    //[rmxDebugger add:RMX_ERROR n:self t:_name];
}

- (RMXVector3)upVector{
    return GLKMatrix3GetRow(body.orientation,1);
}

- (RMXVector3)rightVector{
    return GLKVector3Negate(GLKMatrix3GetRow(body.orientation,0));
}

- (RMXVector3)leftVector{
    return GLKMatrix3GetRow(body.orientation,0);
}

- (RMXVector3)forwardVector{
    return GLKMatrix3GetRow(body.orientation,2);
}
@end


