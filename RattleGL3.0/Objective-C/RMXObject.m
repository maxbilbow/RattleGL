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

#import "RattleGLS-Bridging-Header.h"
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
    _physics = (world != nil) ? world.physics : [RMXPhysics NewWithParent:parent world: (RMXWorld*) self];
    [self reInit];
    return self;
}

- (float)altitude{
    return _body.position.y;
}
/*
- (void)setAltitude:(float)altitude {
    self.body.position.y = altitude;
}
*/
- (float)positionX{
    return _body.position.x;
}

- (float)positionZ{
    return _body.position.z;
}

- (void)reInit {
    self.body = [RMSPhysicsBody New];
    
}
- (void)debug {
    //[rmxDebugger add:RMX_ERROR n:self t:_name];
}

- (RMXVector3)upVector{
   // GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(SCNMatrix4ToGLKMatrix4(body.orientation)),1);
    return SCNVector3Make(_body.orientation.m12,_body.orientation.m22,_body.orientation.m32);
}

- (RMXVector3)rightVector{
   //  GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(SCNMatrix4ToGLKMatrix4(body.orientation)),0);
    return SCNVector3Make(-_body.orientation.m11, -_body.orientation.m21, -_body.orientation.m31);
}

- (RMXVector3)leftVector{
    //GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(SCNMatrix4ToGLKMatrix4(body.orientation)),0);
    return SCNVector3Make(_body.orientation.m11,_body.orientation.m21,_body.orientation.m31);
}

- (RMXVector3)forwardVector{
    //GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(SCNMatrix4ToGLKMatrix4(body.orientation)),2);
    return SCNVector3Make(_body.orientation.m13,_body.orientation.m23,_body.orientation.m33);
}

- (float)distanceTo:(RMXObject*)object {
    return GLKVector3Distance(SCNVector3ToGLKVector3(_body.position),SCNVector3ToGLKVector3(object.body.position));
}
//- (void)animate{}



@end
