//
//  Perspective.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//



#import "RattleGL-Bridging-Header.h"
#import <RattleGL-Swift.h>


void AnimateScene(void)
{
    //animate();
    [world animate];
    if (world == nil) exit(1);

    //[sun drawWith:DrawSphere];
    DrawFog();
    //[art animate];
   // getDt();
    glutPostRedisplay();
}

void reshape (int width, int height) {
    [window setSize:width h:height]; //glutGet(GLUT_WINDOW_WIDTH);
   // window.height = height;// glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, [window width], [window height]);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (float)[window width] / [window height], window.nearPlane, window.farPlane);
    //GLKMatrix4MakePerspective(65*PI_OVER_180 ,(float)window.width / window.height, window.nearPlane, window.farPlane);
    glMatrixMode(GL_MODELVIEW);
}

bool alt = true;
void display (void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(art.r,art.g,art.b,art.k);
    [rmxDebugger add:RMX_DISPLAY_PROCESSOR n:@"DisplayProcessor" t:[NSString stringWithFormat:@"r%f, g%f, b%f, k%f",art.r,art.g,art.b,art.k]];
    glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
    [observer makeLookAtGl:gluLookAt];
  
    
    repeatedKeys();
    AnimateScene();
       // Make sure changes appear onscreen
    glutSwapBuffers();
    glFlush();
    debug();
    //tester.checks[1] = observer->toString();
   
    
}



