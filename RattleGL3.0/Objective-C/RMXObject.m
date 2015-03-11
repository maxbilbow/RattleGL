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

#import "RattleGL-Bridging-Header.h"
#import <RattleGL-Swift.h>

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
//    _physics = nil;
    _physics = (world != nil) ? world.physics : [[RMXPhysics alloc]initWithName:@"Root Node" parent:parent world: (RMXWorld*) self];
    [self reInit];
    return self;
}

- (float)altitude{
    return body.position.y;
}

- (void)setAltitude:(float)altitude {
    body.position.y = altitude;
}

- (float)positionX{
    return body.position.x;
}

- (float)positionZ{
    return body.position.z;
}

- (void)reInit {
    body = RMXPhyisicsBodyMake();
    self.physicsBody = [RMSPhysicsBody New];
    
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

- (float)distanceTo:(RMXObject*)object {
    return GLKVector3Distance(body.position, object->body.position);
}
//- (void)animate{}



@end
