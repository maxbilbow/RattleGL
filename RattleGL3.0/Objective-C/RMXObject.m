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

#import "RattleGL3.0-Bridging-Header.h"

@implementation RMXObject

- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world{
    self = [super init];
    _parent = parent;
    _world = world;
//    if (world != nil && [world isKindOfClass:[RMXWorld class]]){
//        _uiView = ((RMXWorld*)world).uiView;
//    } else if (world == nil && [parent isKindOfClass:[UIVideoEditorController class]]) {
//        _uiView = (UIVideoEditorController*) parent;
//    }
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
    GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(body.orientation),1);
    return GLKVector3Make(v.x,v.y,v.z);
}

- (RMXVector3)rightVector{
    GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(body.orientation),0);
    return GLKVector3Negate(GLKVector3Make(v.x,v.y,v.z));
}

- (RMXVector3)leftVector{
    GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(body.orientation),0);
    return GLKVector3Make(v.x,v.y,v.z);
}

- (RMXVector3)forwardVector{
    GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(body.orientation),2);
    return GLKVector3Make(v.x,v.y,v.z);
}
@end


