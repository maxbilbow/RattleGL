//
//  main.m
//  OpenGL 2.1 (OC)
//
//  Created by Max Bilbow on 15/02/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#import "RattleGLS-Bridging-Header.h"
#import <RattleGL-Swift.h>
#define TEXTURE_ID_CUBE 1
void InitGraphics(void)
{
//    int width, height;
//    int nComponents;
//    void* pTextureImage;
    
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    // Create texture for cube; load marble texture from file and bind it
    //pTextureImage = read_texture("marble.rgb", &width, &height, &nComponents);
    glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
    
    glGenerateMipmap(GL_MAP1_NORMAL);
//    gluBuild2DMipmaps(GL_TEXTURE_2D,     // texture to specify
//                      GL_RGBA,           // internal texture storage format
//                      width,             // texture width
//                      height,            // texture height
//                      GL_RGBA,           // pixel format
//                      GL_UNSIGNED_BYTE,	// color component format
//                      pTextureImage);    // pointer to texture image
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR_MIPMAP_LINEAR);
    glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}


int run(int argc, char * argv[])
{
    //main = [Main new];
   // world = [RMXArt initializeTestingEnvironment];
    glutInit(&argc, argv);
    initKeys();

    //    window = [[RMXWindow alloc]initWithMethods:glutInitWindowSize
//                                               disp:glutDisplayFunc rs:glutReshapeFunc
//                                               kp:glutKeyboardFunc ku:glutKeyboardUpFunc ks:glutSpecialFunc ksu:glutSpecialUpFunc
//                                               mf:glutMouseFunc mF:glutMotionFunc pmf:glutPassiveMotionFunc
//                                               iF:glutIdleFunc];
    
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    
    if (RMX_FULL_SCREEN){//&&glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)){
        glutEnterGameMode();
    }else {
        NSLog(@"Game Mode Not Possibe, Exit: %i",glutGameModeGet(GLUT_GAME_MODE_POSSIBLE));
        //window.create(glutCreateWindow);
        //[window create:glutCreateWindow];
        glutInitWindowPosition(100,100);
        glutInitWindowSize(1280,750);
        glutCreateWindow("Window");
    }
    
    //Setup Display:
    //[window display:display rs:reshape];
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    // Register callbacks:
    //[window keyboard:RMXkeyPressed up:RMXkeyUp sp:RMXkeySpecial spU:RMXkeySpecialUp];
    glutKeyboardFunc(RMXkeyPressed);
    glutKeyboardUpFunc(RMXkeyUp);
    glutSpecialFunc(RMXkeySpecial);
    glutSpecialUpFunc(RMXkeySpecialUp);
    
    //Mouse Callbacks:
    //[window mouse:MouseButton m:MouseMotion pm:mouseFree];
   
    glutMouseFunc(MouseButton);
    glutMotionFunc(MouseMotion);
    glutPassiveMotionFunc(mouseFree);
    
    //Animation
    // [window idle:AnimateScene];
    glutIdleFunc(AnimateScene);
    
    // Create our popup menu
    //BuildPopupMenu();
    InitGraphics();
    //glutAttachMenu (GLUT_RIGHT_BUTTON);
    // Get the initial time, for use by animation

    //gettimeofday (&last_idle_time, NULL);

    
    //[mouse center];
    
    if (RMX_FULL_SCREEN) {
        [world.observer toggleFocus];
        glutSetCursor(GLUT_CURSOR_NONE);
        [world.observer calibrateView:0 vert:0];//observer->getMouse().x,observer->getMouse().y);
        [world.observer mouse2view:0 y:0];
    }
    glutMainLoop ();
    return 0;
}


void debug(){
//    [world.observer.item debug];
//    [world.observer debug];
    //[rmxDebugger feedback];
};



