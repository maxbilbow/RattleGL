//
//  RMXDrawable.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXDrawable_h
#define RattleGL3_0_RMXDrawable_h


#endif

@protocol RMXDrawable <NSObject>
@property  GLKVector4 color;
@property  bool isRotating;
@property  RMXVector3 rAxis;
@property float rotation,  w;
@property int32_t type, gl_light;
@property void (*render)(float);
@property void(*shine)(GLenum, GLenum, const float*);

- (vector_float4)getColorfv;
- (void)setMaterial;
- (void)unsetMaterial;
//- (void)RenderMe;
@end