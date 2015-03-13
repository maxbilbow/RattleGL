//
//  cStuff.h
//  RattleGL
//
//  Created by Max Bilbow on 11/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef __RattleGL__cStuff__
#define __RattleGL__cStuff__


#endif /* defined(__RattleGL__cStuff__) */

void RMXMakeLookAtGL(void (* lookAt)(double eyeX, double eyeY, double eyez,
                                     double centerX, double centerY, double centerZ,
                                     double upX, double upY, double upZ),double eyeX, double eyeY, double eyez,
                     double centerX, double centerY, double centerZ,
                     double upX, double upY, double upZ);

void RMXGLMaterialfv(int32_t a,int32_t b, GLKVector4 color);
void RMXGLTranslate(RMXVector3 v);
void RMXGLShine(int a, int b, GLKVector4 color);
void RMXGLRender(void (*render)(float),float size);