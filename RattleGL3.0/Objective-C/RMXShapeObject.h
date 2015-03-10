//
//  RMXShapeObject.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXShapeObject_h
#define RattleGL3_0_RMXShapeObject_h


#endif

@interface RMXShapeObject : RMXParticle <RMXDrawable>

@property  GLKVector4 color;
@property  bool isRotating;
@property  GLKVector3 rAxis;
@property float rotation,  w;
@property GLenum type, gl_light;
@property void (*render)(float);
@property void(*shine)(GLenum, GLenum, const float*);

@end
