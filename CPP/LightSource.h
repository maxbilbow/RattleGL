//
//  LightSource.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_LightSource_h
#define OpenGL_2_0_LightSource_h


#endif
#include "ShapeObject.h"

class LightSource : public ShapeObject {
protected:
    GLenum type = GL_POSITION;
    GLenum gl_light = GL_LIGHT0;
    float w;
public:
    LightSource(float x, float y, float z, float w){
        position = GLKVector3Make(x,y,z);
        this->w=w;
    }
    
//    LightSource(GLenum num, GLenum type, GLKVector4 position){
//        this->position = position;
//        this->gl_light = num;
//        this->type = type;
//    }
    
    LightSource(){
        position = GLKVector3Make(50,0,0);
        w=1;
        size = 100;
        isRotating = true;
        temp = false;
    }
    
    
    void shine(void (*light)(GLenum l, GLenum type, const float* pos)){
        light(gl_light, type, GLKVector4MakeWithVector3(position, w).v);
    }
    
        
    void lightUp(float i){
        position.x += i;
        tester.checks[8]+= " Light Y: "+ to_string(position.x);
    }
    void lightSwitch(char i){
        switch (i){
            case '1':
                type = GL_POSITION;
                break;
            case '2':
                type = GL_SPECULAR;
                break;
            case '3':
                type = GL_AMBIENT;
                break;
            case '4':
                type = GL_DIFFUSE;
                break;
            case '5':
                type = GL_AMBIENT_AND_DIFFUSE;
                break;
        }
    }
    
    void setMaterial(){
        glMaterialfv(GL_FRONT,GL_EMISSION, color.v);
    }
    
    void unsetMaterial(){
        glMaterialfv(GL_FRONT, GL_EMISSION,nill);
    }
    
};
LightSource sun = LightSource();