//
//  Particle.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Particle_h
#define OpenGL_2_0_Particle_h


#endif
#include "Physics.h"


class SimpleParticle {
    /* ATTRIBUTES
     - Position
     - Velocity
     - (acceloration? Could be an external input)
     - LookAt
     - Up
     - Right
     */
protected:
    GLKVector3 position = GLKVector3Make(0, 0, 0);
    GLKVector3 velocity = GLKVector3Make(0, 0, 0);
    GLKVector3 acceleration = GLKVector3Make(0, 0, 0);
    GLKVector3 forwardVector = GLKVector3Make(0, 0, 1);
    GLKVector3 upVector = GLKVector3Make(0, 1, 0);
    GLKVector3 leftVector = GLKVector3Make(1, 0, 0);
    GLKVector3 forwardV = GLKVector3Make(0, 0, 0);
    GLKVector3 upV = GLKVector3Make(0, 0, 0);
    GLKVector3 leftV = GLKVector3Make(0, 0, 0);
    Physics * physics;
    Physics * externalPhysics;
    Physics localPhysics = Physics();
    //float * dift = &dt;
    
public:
    
   
    SimpleParticle(){
        physics = &localPhysics;
        externalPhysics = new Physics;
    }
    SimpleParticle(Physics & physics){
        externalPhysics = &physics;
        useExternalPhysics();
    }
    GLKVector3 getPosition(){
        return position;
    }
    
    void useExternalPhysics(){
        physics = externalPhysics;
    }
    
    void useLocalPhysics(){
        physics = &localPhysics;
    }
    
    void setPhysics(Physics & ph){
        physics = &ph;
    }
    
    virtual void setPosition(GLKVector3 v){
        position = v;
    }
    
    GLKVector3 getVelocity(){
        return velocity;
    }
    
    virtual void setVelocity(GLKVector3 v){
        velocity = v;
    }
    
    GLKVector3 getAcceleration(){
        return acceleration;
    }
    
    void setAcceleration(GLKVector3 v){
        acceleration = v;
    }
    
    
    GLKVector3 getForwardVector(){
        return forwardVector;
    }
    
    void setForwardVector(GLKVector3 v){
        forwardVector = v;
    }
    
    
    GLKVector3 getUpVector(){
        return upVector;
    }
    
    void setUpVector(GLKVector3 v){
        upVector = v;
    }
    
    
    GLKVector3 getLeftVector(){
        return leftVector;
    }
    
    void setLeftVector(GLKVector3 v){
        leftVector = v;
    }
    
    virtual float getForwardVelocity(){
        return velocity.z;
    }
    
    virtual float getUpVelocity(){
        return velocity.y;
    }
    
    virtual float getLeftVelocity(){
        return velocity.x;
    }
    
    virtual GLKVector3 getEye(){
        return position;
    }
    
    virtual GLKVector3 getCenter(){
        return GLKVector3Add(position,forwardVector);
    }
    
    virtual GLKVector3 getUp(){
        return upVector;
    }

    virtual string toString(){
        return "string values";
    }
    
    virtual void setAnchor(GLKVector3 vector){}
    
    virtual void setView(){}
    
};