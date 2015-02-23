//
//  Interface.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Interface_h
#define OpenGL_2_0_Interface_h


#endif

//#include "RattleGLI.h"
//void init();
//template <typename Particle>
class Window {
protected:
    int id;
    GLKVector2 size = GLKVector2();
    float fViewDistance = 3 * VIEWING_DISTANCE_MIN;
    float nearPlane = 1;
    float farPlane = 1000;
    bool fullscreen = false;
    //template <typename Number>
    const char * title = "Rattle X Window";
    

    void
    //Display
    (*initWindowSize)(int width, int height),
    //(*initDisplayMode)(unsigned int mode),
    (*displayFunc)(void (*func)(void)),
    (*reshapeFunc)(void (*func)(int width, int height)),
    //Keyboard
    (*keyPressed)(void (*func)(unsigned char key, int x, int y)),
    (*keyUp)(void (*func)(unsigned char key, int x, int y)),
    (*keySpecial)(void (*func)(int key, int x, int y)),
    (*keySpecialUp)(void (*func)(int key, int x, int y)),
    //Mouse
    (*mouseFunc)(void (*func)(int button, int state, int x, int y)),
    (*motionFunc)(void (*func)(int x, int y)),
    (*passiveMotionFunc)(void (*func)(int x, int y)),
    //Other
    (*idleFunc)(void (*func)(void));
   // (*initalise)(void);
    

    
public:
    Window() {
        size.y = 600;
        size.x = 600;
    }
    
    
    int getWidth(){
        return size.x;
    }
    int getHeight(){
        return size.y;
    }
    
    GLKVector2 getSize(){
        return size;
    }
    
    void setSize(int width, int height){
        size.x = width;
        size.y = height;
    }
    
    float getNearPlane(){
        return nearPlane;
    }
    
    float getFarPlane(){
        return farPlane;
    }
    bool isFullscreen(){
        return fullscreen;
    }
    
    float getFViewDistance() {
        return fViewDistance;
    }

    void setFViewDistance(float fViewDistance){
        this->fViewDistance = fViewDistance;
    }
    //Glut Init
    void init(
              //Display
              void (*initWindowSize)(int width, int height),
              //void (*initDisplayMode)(unsigned int mode),
              void (*displayFunc)(void (*func)(void)),
              void (*reshapeFunc)(void (*func)(int width, int height)),
              //Keyboard
              void (*keyPressed)(void (*func)(unsigned char key, int x, int y)),
              void (*keyUp)(void (*func)(unsigned char key, int x, int y)),
              void (*keySpecial)(void (*func)(int key, int x, int y)),
              void (*keySpecialUp)(void (*func)(int key, int x, int y)),
              //Mouse
              void (*mouseFunc)(void (*func)(int button, int state, int x, int y)),
              void (*motionFunc)(void (*func)(int x, int y)),
              void (*passiveMotionFunc)(void (*func)(int x, int y)),
              //Other
              void (*idleFunc)(void (*func)(void))//,
             // void (*init)(void)
           ) {
        //Set Display
        this->initWindowSize = initWindowSize;
        //this->initDisplayMode = initDisplayMode;
        this->displayFunc = displayFunc;
        this->reshapeFunc = reshapeFunc;
        //Set Keyboard
        this->keyPressed = keyPressed;
        this->keyUp = keyUp;
        this->keySpecial = keySpecial;
        this->keySpecialUp = keySpecialUp;
        //Set Mouse
        this->mouseFunc = mouseFunc;
        this->motionFunc = motionFunc;
        this->passiveMotionFunc = passiveMotionFunc;
        //Other
        this->idleFunc = idleFunc;
        
        
        //this->initDisplayMode(
        //init();
        
    }
    
    void toggleFullScreen(){
        if (fullscreen) {
            glutLeaveGameMode();
            glutInitWindowSize (getWidth(), getHeight());
            //glutInitWindowPosition (100, 100);
            create(glutCreateWindow);
            //EXIT GAME MODE
            
            fullscreen = false;
        } else {
            glutDestroyWindow(id);
            id = glutEnterGameMode();
            glutPostRedisplay();
            fullscreen = true;
        }
        
    }
    
    void create(int (createWindow)(const char * s)){
        initWindowSize(getWidth(),getHeight());
        id = createWindow(title);
    }
    
    
    void display (void (*display)(void),void (*reshape)(int width, int height)){
        displayFunc(display);
        reshapeFunc(reshape);
    }

    
   
    
    void keyboard(
                  void (*pressed)(unsigned char key, int x, int y),
                  void (*up)(unsigned char key, int x, int y),
                  void (*special)(int key, int x, int y),
                  void (*specialUp)(int key, int x, int y)
                  ){
        keyPressed(pressed);
        keyUp(up);
        keySpecial(special);
        keySpecialUp(specialUp);
        
    }

    
    void mouse(
               void (*mouse)(int button, int state, int x, int y),
               void (*motion)(int x, int y),
               void (*passiveMotion)(int x, int y)
               ) {
        mouseFunc(mouse);
        motionFunc(motion);
        passiveMotionFunc(passiveMotion);
    }

    void idle (void (*func)(void)){
        idleFunc(func);
    }

};

Window window = Window();

Observer * observer;// = * Observer();




