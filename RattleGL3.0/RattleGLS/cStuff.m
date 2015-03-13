//
//  cStuff.c
//  RattleGL
//
//  Created by Max Bilbow on 11/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#import <GLUT/GLUT.h>
#import <GLKit/GLKit.h>
#import <SceneKit/SceneKit.h>
#import "RMXMaths.h"
#include "cStuff.h"


void RMXMakeLookAtGL(void (* lookAt)(double eyeX, double eyeY, double eyez,
                                     double centerX, double centerY, double centerZ,
                                     double upX, double upY, double upZ),double eyeX, double eyeY, double eyez,
                     double centerX, double centerY, double centerZ,
                     double upX, double upY, double upZ) {
    lookAt(eyeX,eyeY,eyez,
           centerX,centerY,centerZ,
           upX,upY,upZ);
    
}

void RMXGLMaterialfv(int32_t a,int32_t b, GLKVector4 color){
    glMaterialfv(a,b,color.v);
}

void RMXGLTranslate(RMXVector3 v){
    glTranslatef(v.x, v.y, v.z);
}

void RMXGLShine(int32_t a, int32_t b, GLKVector4 color) {
    glLightfv(a, b, color.v);
}

void RMXGLRender(void (*render)(float),float size) {
    render(size);
}