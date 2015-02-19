//
//  Physics.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Physics_h
#define OpenGL_2_0_Physics_h
#endif

#define GRAVITY (0.01/50);
#define FRICTION 1.1;


class Physics {
    const float _g = GRAVITY;
    const float _f = FRICTION;
protected:
    float gravity = _g;
    const float * U_GRAVITY;
    const float * U_FRICTION;
    float friction = _f;
public:
    Physics(){
        U_GRAVITY = &_g;
        U_FRICTION = &_f;
    }
    
    float getGravity(){
       // float gpf = gravity/50;
        return gravity;
    }
    
    void toggleGravity(){
        gravity = (gravity == *U_GRAVITY) ? 0 : *U_GRAVITY;
    }
    
    void addGravity(float g){
        gravity += g;
        if (gravity<0)
            gravity = 0;
        tester.checks[7] += " / Gravity: " + to_string(gravity);
    }
    
    float getFriction(){
        return friction;
    }
    
    void toggleFriction(){
        friction = (friction == *U_FRICTION) ? 0 : *U_FRICTION;
    }
    
    void addFriction(float f){
        friction += f;
        if (friction<0)
            friction = 0;
        tester.checks[7] += " / Friction: " + to_string(friction);
    }
    
    
};