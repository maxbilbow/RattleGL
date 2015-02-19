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

#include "SimpleParticle.h"
#include "PointOfView.h"
#include "Mouse.h"

/*
 Provides basic movement attributes to any object
 */
class Particle : public SimpleParticle , public PointOfView, public Mouse{
    /* ATTRIBUTES 
     - Position
     - Velocity
     - (acceloration? Could be an external input)
     - LookAt
     - Up
     - Right
     */
protected:
    float accelerationRate = 0.01;
    float speedLimit = 0.20;
    bool limitSpeed = true;
    bool drift = false;
    //bool forward = false;
    float floor = 0;
    SimpleParticle origin = SimpleParticle();
    GLKVector3 anchor = GLKVector3Make(0,0,0);
    float rotationSpeed = -0.1;
    float jumpStrength = 2.0;
    //GLKVector2 mousePos = GLKVector2();
    //float theta = 0, phi = 0;
    
public:
//    Particle(){
//        anchor = &physics.origin;
//    }
    bool isDrift(){
        return !drift;
    }
    
    void setPosition(GLKVector3 v){
        if (v.y < floor)
            v.y = floor;
        position = v;
    }
    
    bool checkLimits (GLKVector3 dV){
        return true;
    }
    
    bool isZero(GLKVector3 v){
        return ((v.x==0)&&(v.y==0)&&(v.z==0));
    }
    
   
    bool translate(){
        if (isZero(getVelocity()))
            return false;
        else
            setPosition(GLKVector3Add(getPosition(),getVelocity()));
        return true;
    }
    
    void animate(){
        accelerate();
       
        leftVector = GLKVector3CrossProduct(getForwardVector(), getUpVector());
        translate();
        manipulate();
//        if(!isZero(getVelocity())) {
//            cout << "Velocity is "<< getVelocity().z << endl;
//        }
        
       
    }

    virtual void manipulate(){}
    
    //MOVEMENT
    
    void stop() {
        setVelocity(GLKVector3Make(0,0,0));
        //setRotationalVelocity(GLKVector3Make(0,0,0));
    }
    
//    void accelerateForward(){
//        forward = !forward;
//    }
    
    void accelerateForward(float velocity){
        acceleration.z = velocity * accelerationRate;
      //  accelerate();//GLKVector3Make(0,0,velocity*accelerationRate));
    }
    
    void accelerateUp(float velocity){
        acceleration.y = velocity * accelerationRate;
      //  accelerate();
 //       accelerate(GLKVector3Make(0,velocity*accelerationRate,0));
    }
    
    void accelerateLeft(float velocity){
        acceleration.x = velocity * accelerationRate;
        //accelerate();//accelerate(GLKVector3Make(velocity*accelerationRate,0,0));
    }

    
    
    void forwardStop(){
        if (!drift) {
            acceleration.z = 0;
//            if(getForwardVelocity()>0)
//                acceleration.z = -physics.friction;
//            else if (getForwardVelocity()<0)
//                acceleration.z = physics.friction;
//            else
//                acceleration.z = 0;//-velocity.z;
        }
    }
    
    void upStop(){
        if (!drift) {
            acceleration.y = 0;// -velocity.y;
            //accelerate();
        }
    }
    
    void leftStop(){
        if (!drift) {
            acceleration.x = 0;// -velocity.x;
            //accelerate();
        }
        
    }
    
    
    void accelerate(){
        //acceleration.z =
        acceleration.y -= physics->getGravity();
        setVelocity(acceleration); //Need to calculate this
        
        if (limitSpeed){
            for (int i=0;i<3;++i)
                if (getVelocity().v[i] > speedLimit){
                    //cout << "acc = " << velocity().z << endl;
                    velocity.v[i] = speedLimit;
                } else if (getVelocity().v[i] < -speedLimit){
                    //cout << "acc = " << getAcceleration().z << endl;
                    velocity.v[i] = -speedLimit;
                }
            
        }
        
        //setRelativeVelocity(<#GLKVector3 v#>)
        tester.checks[6] = "accZ: "+ to_string(acceleration.z)
        + ", velZ: " + to_string(velocity.z);
        
        
    }

    void setAngle(float theta, float phi)RMX_DEPRECATED(10_0, 10_9){
        theta = -theta*PI_OVER_180;
        phi = phi*PI_OVER_180;
        forwardVector.z = cos(theta);// * sin(phi);
        forwardVector.x = sin(theta);
        GLKVector3Normalize(forwardVector);
    }
    
//    void setAngle(){
//        theta = -theta*PI_OVER_180;
//        phi = phi*PI_OVER_180;
//        forwardVector.z = cos(theta);// * sin(phi);
//        forwardVector.x = sin(theta);
//        GLKVector3Normalize(forwardVector);
//    }
//    void rotate(float theta, float phi){
//        this->theta *= theta*PI_OVER_180*rotationSpeed;
//        this->phi *= PI_OVER_180*rotationSpeed;
//        rotateAroundVerticle(theta);
//        rotateAroundHorizontal(phi);
//        tester.checks[2] = "plusAngle: THETA " + to_string(theta) +", PHY: " + to_string(phi);
//    }
//    
    
    
    void plusAngle(float theta, float phi){
        theta *= PI_OVER_180*rotationSpeed;
        phi *= PI_OVER_180*rotationSpeed;
        rotateAroundVerticle(theta);
        rotateAroundHorizontal(phi);
        tester.checks[2] = "plusAngle: THETA " + to_string(theta) +", PHY: " + to_string(phi);
    }
    
    void rotateAroundVerticle(float theta){
        GLKMatrix4 rm = GLKMatrix4MakeRotation(theta, upVector.x, upVector.y, upVector.z);
        //GLKMatrix4RotateWithVector3(GLKMatrix4MakeYRotation(theta), theta, getUpVector());
        forwardVector = GLKMatrix4MultiplyVector3WithTranslation(rm, forwardVector);
        //leftVector = GLKMatrix4MultiplyVector3WithTranslation(rm, leftVector);
    }
    
    void rotateAroundHorizontal(float phi){
        // leftVector = GLKVector3CrossProduct(getForwardVector(), getUpVector()); // Set the Right Vector
        GLKMatrix4 rm = GLKMatrix4MakeRotation(phi, leftVector.x, leftVector.y, leftVector.z);
        
        //upVector = GLKMatrix4MultiplyVector3WithTranslation(rm, upVector);
        forwardVector = GLKMatrix4MultiplyVector3WithTranslation(rm, forwardVector);
        
    }
    
    void setVelocity(GLKVector3 acceleration){
        float forward = acceleration.z;
        float left = -acceleration.x;
        float up = acceleration.y;
        
        forwardV = GLKVector3MultiplyScalar(forwardVector, forward);
        //forwardV = GLKVector3DivideScalar(forwardV, physics.friction);
        upV = GLKVector3MultiplyScalar(upVector, up);
        leftV = GLKVector3MultiplyScalar(leftVector, left);
        // GLKVector3 tm = GLKVector3Project(acceleration, forwardVector);
        //GLKVector3 tm
        
        velocity = GLKVector3Add(velocity,GLKVector3Add(forwardV,leftV));
        velocity = GLKVector3DivideScalar(velocity,physics->getFriction());
        velocity = GLKVector3Add(upV,velocity);
        
    }

    

    void addGravity(float g){
        physics->addGravity(g);
    }
    
    void addFriction(float f){
        physics->addFriction(f);
    }
    
    void toggleGravity() {
        physics->toggleGravity();
    }
    
    bool hasGravity(){
        return (physics->getGravity() > 0);
    }
    
    bool isGrounded(){
        return (position.y == floor);
    }
    
    void push(GLKVector3 direction){
        velocity = GLKVector3Add(velocity, direction);
    }
    
    void setAnchor(GLKVector3 anchor){
        this->anchor = anchor;
    }
    
//    void unsetAnchor(){
//        origin.setPosition(anchor->getCenter());
//        this->anchor = &origin;
//    }
    
    GLKVector3 getAnchor(){
        return anchor;
    }
    
    GLKVector3 getEye(){
        return getPosition();
    }
    
    GLKVector3 getCenter(){
        return GLKVector3Add(getPosition(),getForwardVector());
    }
    
    GLKVector3 getUp(){
        return getUpVector();
    }

    string toString(){
        string s = "Camera Attributes: ";
        s +=
        "\n      POS: " + to_string(getEye().x) + ", " + to_string(getEye().y) + ", " + to_string(getEye().z);
        return s;
    }
   
    
    
  //  extern void APIENTRY setAngle(float theta,float phi) OPENGL_DEPRECATED(10_0, 10_9);
//    void setDirection(int x, int y, bool hasFocus){
//        
//        int DeltaX = x-mousePos.x, DeltaY = y-mousePos.y;
//        //CGGetLastMouseDelta(&DeltaX, &DeltaY);
//        
//        tester.checks[3] = "Mousie diffX: " + to_string(DeltaX) + " diffY: " + to_string(DeltaY);
//        //cout<< "  Mouse Pos: " << "|" << mouse.mousePos.x << "|" << mouse.mousePos.y << endl;
//        
//        
//        int dir = hasFocus ? 1 : -1;
//        
//        float theta = (float)DeltaX*dir;
//        float phi = (float)DeltaY*dir;
//        //setAngle((float)DeltaX*dir,(float)DeltaY*dir);// / 20.0f;
//        
//        this->rotate(theta,phi);
//        
//        
//        
//        if (hasFocus) {
//            //glutWarpPointer(window.width/2, window.height/2);
//            center();
//            // alt = !alt;
//        } else {
//            mousePos->x = x;
//            mousePos->y = y;
//        } }
    

    float getRotationSpeed(){
        return rotationSpeed;
    }
    
    
    
};


