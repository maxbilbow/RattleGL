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

#include "Particle.h"
/*
 Provides basic movement attributes to any object
 */
class Observer : public Particle {
    /* ATTRIBUTES 
     - Position
     - Velocity
     - (acceloration? Could be an external input)
     - LookAt
     - Up
     - Right
     */
protected:
    SimpleParticle * item = & origin;
    GLKVector3 itemPosition = item->getPosition();
    float armLength = 2;
    float reach = 6;
    public:
    
    Observer(){
        floor = 1;
    }
    
        
    string toString(){
        return PointOfView::toString();
    }
    
    void jump(){
        if (hasGravity()&&(isGrounded()))
            accelerateUp(jumpStrength);
    }
    
    
    void grabObject(Particle *item){
        if ((this->item == item)||(GLKVector3Distance(this->getPosition(), item->getPosition())>reach))
            releaseObject();
        else {
            this->item = item;
            itemPosition = item->getPosition();
            armLength = GLKVector3Distance(this->getCenter(), itemPosition);
            
        }
        
    }
    
    void releaseObject(){
        //origin.setPosition(anchor->getCenter());
        this->item = &origin;
    }
    
    void manipulate(){
        //item->setAnchor(this->getPosition());
        item->setPosition(GLKVector3Add(this->getCenter(),GLKVector3MultiplyScalar(getForwardVector(),armLength)));
    }
    
    void extendArmLength(float i){
        if (armLength+i>1)
            armLength += i;
        
    }

    
    
    
};

