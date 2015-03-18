//
//  Perspective.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//



#import "RattleGLS-Bridging-Header.h"
#import <RattleGL-Swift.h>

//@class RMXGLProxy;
void AnimateScene(void)
{
    //animate();
    [world.thisWorld animate];
    if (world.thisWorld == nil) exit(1);

    //[sun drawWith:DrawSphere];
    DrawFog();
    //[art animate];
   // getDt();
    glutPostRedisplay();
}

void reshape (int width, int height) {
    //[window setSize:width h:height]; //glutGet(GLUT_WINDOW_WIDTH);
   // window.height = height;// glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (float) width / height, 1, world.thisWorld.body.radius*2);
    //GLKMatrix4MakePerspective(65*PI_OVER_180 ,(float)window.width / window.height, window.nearPlane, window.farPlane);
    glMatrixMode(GL_MODELVIEW);
}

bool alt = true;

void display (void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor(art.r,art.g,art.b,art.k);
    glClearColor(0.8f, 0.85f, 1.8f, 0.0f);
    //[rmxDebugger add:RMX_DISPLAY_PROCESSOR n:@"DisplayProcessor" t:[NSString stringWithFormat:@"r%f, g%f, b%f, k%f",art.r,art.g,art.b,art.k]];
    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
    [world.observer.camera makeLookAtGl:gluLookAt];
  
    
    repeatedKeys();
    AnimateScene();
       // Make sure changes appear onscreen
    glutSwapBuffers();
    glFlush();
    debug();
    //tester.checks[1] = observer->toString();
    //NSLog([world.observer viewDescription]);
   
    
}



