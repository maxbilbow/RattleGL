//
//  Mouse.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 31/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Mouse_h
#define OpenGL_2_0_Mouse_h


#endif

class Mouse {
    bool onUpperEdge = false;
    bool onLowerEdge = false;
    bool onLeftEdge = false;
    bool onRightEdge = false;
    bool focus = false;
    int dx = 0, dy = 0;
    //  bool inverted;
    GLKVector2 pos = GLKVector2();
protected:
    //int theta, phi;
    
public:
    void toggleFocus(){
        focus = !focus;
    }
    bool hasFocus(){
        return focus;
    }
    
private:
    GLKVector2 getPos(){
        return pos;
    }

    void setPos(int h, int v){
        pos.x=h;
        pos.y=v;
    }
//    void center(){
//        pos.x = glutGet(GLUT_WINDOW_X)/2;
//        pos.y = glutGet(GLUT_WINDOW_Y)/2;
//        CGWarpMouseCursorPosition(CGPointMake(pos.x + glutGet(GLUT_WINDOW_X), pos.y + glutGet(GLUT_WINDOW_Y)));
//        
//    }
    
public:
    virtual void rotate(){};
    virtual float getRotationSpeed(){ return 1; }
    virtual void rotateAroundVerticle(float theta){}
    virtual void rotateAroundHorizontal(float phi){}
    //virtual void setAngles(float theta, float phi);
    virtual void plusAngle(float theta, float phi){}
    
    //virtual void rotate(float theta, float phi){}
//        this->theta = theta*PI_OVER_180*getRotationSpeed();
//        this->phi = phi*PI_OVER_180*getRotationSpeed();
//        rotateAroundVerticle(theta);
//        rotateAroundHorizontal(phi);
//        tester.checks[2] = "plusAngle: THETA " + to_string(theta) +", PHY: " + to_string(phi);
//    }
    
    
   
    
    
    GLKVector2 getMouse(){
        //GLKVector2 pos = { this->pos.x - dx,this->pos.y - dy};
        return pos;
    }
    
    void center(void (*center)(int x, int y)){
        center(pos.x,pos.y);
    }
    
    void setMousePos(int x, int y){
        pos.x = x;// + dx;
        pos.y = y;//;
    }
    void mouse2view(int x, int y){
        //dx = dy = 0;
        
        
        int DeltaX, DeltaY;// =
        
        
        CGGetLastMouseDelta(&DeltaX, &DeltaY);
//        pos.x += DeltaX;
//        pos.y += DeltaY;
        cout<< "  dx " << "|" << DeltaX << "|" << DeltaY << endl;
        tester.checks[3] = "Mousie diffX: " + to_string(DeltaX) + " diffY: " + to_string(DeltaY);
       
        
        //DeltaX -= dx; DeltaY -= dy;
        cout<< "  dx " << "|" << DeltaX << "|" << DeltaY << endl;
        int dir = focus ? 1 : -1;
        
        float theta = (float)(DeltaX)*dir;
        float phi = (float)(DeltaY)*dir;// / 20.0f;
        
        plusAngle(theta,phi);
         cout<< "  Mouse Pos: " << "|" << pos.x << "|" << pos.y << endl;
        
        
    }
    
    void calibrateMouse(int x, int y){//GLKVector2 pos){
        CGGetLastMouseDelta(&dx, &dy);
//        dx += x - CGDisplayPixelsWide(0)/2;
//        dy += y - CGDisplayPixelsHigh(0)/2;
        //setMousePos(pos.x-dx, pos.y-dy);
        cout<< "  CALABRATING " << "|" << dx << "|" << dy << endl;
    }
};