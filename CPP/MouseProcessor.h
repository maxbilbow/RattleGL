//
//  MouseProcessor.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_MouseProcessor_h
#define OpenGL_2_0_MouseProcessor_h



#endif


//CGPoint warpPoint = CGPointMake(window.width, window.height);
//CGWarpMouseCursorPosition(warpPoint);
//CGAssociateMouseAndMouseCursorPosition(true);
#define RX_MOUSE_INVERT (-1)
#define RX_MOUSE_STANDARD 1

#define MARGIN 0

void center(){
//
    bool center = false;//observer->hasFocus();
    int x = center ? window.getWidth()/2 :observer->getMouse().x;
    int y = center ? window.getHeight()/2 :observer->getMouse().y;
    CGWarpMouseCursorPosition(CGPointMake(x + glutGet(GLUT_WINDOW_X), y + glutGet(GLUT_WINDOW_Y) ));
  //  pos.x = glutGet(GLUT_WINDOW_X)/2;
  //  pos.y = glutGet(GLUT_WINDOW_Y)/2;
    
}


void MouseButton(int button, int state, int x, int y)
{
    // Respond to mouse button presses.
    // If button1 pressed, mark this state so we know in motion function.
    if ((button == GLUT_LEFT_BUTTON)&&(state==GLUT_UP))
        observer->grabObject(world.closestObject());//&art.sh);
    if ((button == GLUT_LEFT_BUTTON)&&(state==GLUT_DOWN))
        observer->calibrateMouse(x,y);
    if (button == GLUT_LEFT_BUTTON)
    {

        g_bButton1Down = (state == GLUT_DOWN) ? TRUE : FALSE;
        g_yClick = y - 3 * window.getFViewDistance();
        //art.sh.setAnchor(&observer);
    }
}




void MouseMotion(int x, int y)
{
    if (!observer->hasFocus()) {
        observer->mouse2view(x,y);
    }
    else {
        observer->setMousePos(x, y);
        //observer->calibrateMouse(x,y);
    }
    tester.checks[5] = "MouseMotion: " + to_string(x) + " | "+ to_string(y);
    // If button1 pressed, zoom in/out if mouse is moved up/down.
    if (g_bButton1Down)
    {
        window.setFViewDistance( (y - g_yClick) / 3.0 );
        if (window.getFViewDistance() < VIEWING_DISTANCE_MIN)
            window.setFViewDistance(VIEWING_DISTANCE_MIN);
        glutPostRedisplay();
    }
    
    
}


void mouseFree(int x, int y){
    if (observer->hasFocus()) {
        observer->mouse2view(x,y);// mouse.setView(observer,x,y);
        //observer->center();
        center();

    }
    else
        observer->setMousePos(x, y);
    
    //glutWarpPointer(window.getWidth()/2, window.getHeight()/2);
   
}
