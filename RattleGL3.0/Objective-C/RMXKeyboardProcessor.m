//
//  Interface.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//


#import "RattleGLS-Bridging-Header.h"
#import <RattleGL-Swift.h>


struct KeyProcessor {
    char forward, back, left, right, up, down, stop, jump;
    bool update;
    bool keyStates[256], keySpecialStates[246];// = new bool[246];

};


struct KeyProcessor keys;// = KeyProcessor();

void initKeys(){
    keys.forward = 'w';
    keys.back = 's',
    keys.left = 'a',
    keys.right = 'd',
    keys.up = 'e',
    keys.down = 'q',
    keys.stop = 'f',
    keys.jump = 32;
    //bool * keyStates[256], * keySpecialStates[246]
}


void repeatedKeys(){
    
    if (keys.keySpecialStates[GLUT_KEY_UP]) {
        if (keys.keyStates[9])
            return;//[sun lightUp:1];
        else
            [world.observer extendArmLength:1];

    } else if(keys.keySpecialStates[GLUT_KEY_DOWN]) {
        if (keys.keyStates[9]) {
            return;//[sun lightUp:-1];
        } else {
            [world.observer extendArmLength:-1];
        }
    }

}

void movement(float speed, int key){
    //if (keys.keyStates[keys.forward])  [observer accelerateForward:speed];
    if (key == keys.forward) {
        if (!speed)
            [world.observer forwardStop];
        else
            [world.observer accelerateForward:speed];
    }
    
    if (key == keys.back) {
        if (!speed)
            [world.observer forwardStop];
        else
            [world.observer accelerateForward:-speed];
        //TODO
    }
    
    if (key == keys.left) {
        if (!speed)
            [world.observer leftStop];
        else
            [world.observer accelerateLeft:speed];
        //if(test) cout << keys.left << " ";
    }
    
    if (key == keys.right) {
        if (!speed)
             [world.observer leftStop];
        else
            [world.observer accelerateLeft:-speed];
        //if(test) cout << keys.right << " ";
        //TODO
    }
    
    if (key == keys.up) {
        if (!speed)
             [world.observer upStop];
        else
             [world.observer accelerateUp:speed];
        //if(test) cout << keys.up << " ";
        //TODO
    }
    
    if (key == keys.down) {
        if (!speed)
             [world.observer upStop];
        else
             [world.observer accelerateUp:-speed];
        //if(test) cout << keys.down << " ";
        //TODO
    }
    if (key == 32) {
        if (speed==0)
             [world.observer jump];
        else
             [world.observer prepareToJump];
    //TODO
    }

}

void keyDownOperations (int key) {
   
    movement((float)1.0, key);
    
    
//    if (keys.keyStates['=']) {
//        if (keys.keyStates['r'])
//            art.r += 0.05;
//        if (keys.keyStates['g'])
//            art.g += 0.05;
//        if (keys.keyStates['b'])
//            art.b += 0.05;
//        if (keys.keyStates['k'])
//            art.k += 0.05;
//            
//    } else if (keys.keyStates['-']) {
//        if (keys.keyStates['r'])
//            art.r -= 0.05;
//        if (keys.keyStates['g'])
//            art.g -= 0.05;
//        if (keys.keyStates['b'])
//            art.b -= 0.05;
//        if (keys.keyStates['k'])
//            art.k -= 0.05;
//    }
    //if (keys.keySpecialStates[])
    
}

//template <typename Particle>
void keyUpOperations(int key){
    movement((bool)false, key); //Change to Zero if maintaining velocity
    if (key == 'i'){
        NSLog(@"%@",world.observer.viewDescription);//me.toString();
    }
    
    switch (key)
    {
        default:
            if (RMX_DEBUGGING) NSLog(@"%i unassigned",key);
            break;
        case 27:             // ESCAPE key
            //glutSetKeyRepeat(true);
            exit (0);
            break;
        /*case 'l':
            SelectFromMenu(MENU_LIGHTING);
            break;
        case 'p':
            SelectFromMenu(MENU_POLYMODE);
            break;
        case 't':
            SelectFromMenu(MENU_TEXTURING);
            break;*/
        case 'z':
            [world.thisWorld applyGravity:true];
            break;
        case 'Z':
            [world.thisWorld applyGravity:false];
            break;
        case 'm':
             [world.observer toggleFocus];
            NSLog(@"m");
            if ( [world.observer hasFocus]){
                //center();
                glutSetCursor(GLUT_CURSOR_NONE);
               
                [world.observer calibrateView:0 vert:0];// [observer getMouse().x, [observer getMouse().y);
                [world.observer mouse2view:0 y:0];
                //glutWarpPointer(0,0);
                
            }
            else {
                glutSetCursor(GLUT_CURSOR_INHERIT);
            }
            break;
        case 32:
    // [observer stop();
            if (RMX_DEBUGGING) NSLog(@"%i: Space Bar",key);
            break;
        case 9:
            // [observer stop();
            if (RMX_DEBUGGING) NSLog(@"%i: TAB",key);
            break;
        case 'G':
             [world.observer toggleGravity];
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            exit(0);//[sun lightSwitch:key];
            break;
        case 'S':
           // sun.setAnchor(&observer);
            break;
        case 'R':
            [world.thisWorld resetWorld];
            break;
        case 6: //cntrl f
            NSLog(@"ERROR: Toggle Full Screen not working");//[window toggleFullScreen];
            break;
    }
   // keys.keyStates[key] = false;
    
}
void keySpecialDownOperations(int key) {
    if (key == GLUT_KEY_UP) { // If the left arrow key has been pressed
        //me.look(Observer::UP);
        if (RMX_DEBUGGING) NSLog(@"%i:UP Pressed",key);
        //TODO
    }
    
    if (key == GLUT_KEY_DOWN) {
        if (RMX_DEBUGGING) NSLog(@"%i:DOWN Pressed",key);
    }
    
    if (key == GLUT_KEY_LEFT) {
        if (RMX_DEBUGGING) NSLog(@"%i:LEFT Pressed",key);
    }
    
    if (key == GLUT_KEY_RIGHT) {
        if (RMX_DEBUGGING) NSLog(@"%i:RIGHT Pressed",key);
        //TODO
    }
    
    
    // Perform 'a' key operations
    
}


void keySpecialUpOperations(char key) {
    switch (key){
        case GLUT_KEY_LEFT:
           // [rmxDebugger cycle:-1];
            break;
        case GLUT_KEY_RIGHT:
           // [rmxDebugger cycle:1];
            break;
        case GLUT_KEY_UP:
            //[[observer item]lightUp:10];
            break;
        case GLUT_KEY_DOWN:
            //[[observer item]lightUp:-10];
            break;
        case 32:
            // [observer stop();
            //[rmxDebugger add:RMX_KEY_PROCESSOR n:@"KeyProcessor" t:[NSString stringWithFormat:@"%i: SPACE BAR Released",key]];
            break;

    }
}




void keySpecialOperations(void) {
    keys.update=true;
    //keySpecialDownOperations();
}

void RMXkeyPressed (unsigned char key, int x, int y) {
    //char kTemp = key;
    //NSString * tmp = [NSString stringWithFormat:@"%c",key];//&kTemp;
    //[rmxDebugger add:RMX_KEY_PROCESSOR n:@"KeyProcessor" t:[NSString stringWithFormat:@"%c: pressed",key]];
    keys.keyStates[key] = true; // Set the state of the current key to pressed
    keyDownOperations(key);
}

void RMXkeyUp (unsigned char key, int x, int y) {
    //string tmp = to_string(key);
   // [rmxDebugger add:RMX_KEY_PROCESSOR n:@"KeyProcessor" t:[NSString stringWithFormat:@"%c: released",key]];
    keyUpOperations(key);
    keys.keyStates[key] = false; // Set the state of the current key to not pressed
}
void RMXkeySpecial (int key, int x, int y) {
  //  [rmxDebugger add:RMX_KEY_PROCESSOR n:@"KeyProcessor" t:[NSString stringWithFormat:@"%i: pressed (special)",key]];
    keys.keySpecialStates[key] = true; // Set the state of the current key to pressed
    keySpecialDownOperations(key);
}

void RMXkeySpecialUp (int key, int x, int y) {
  //  [rmxDebugger add:RMX_KEY_PROCESSOR n:@"KeyProcessor" t:[NSString stringWithFormat:@"%i: released (special)",key]];
    keySpecialUpOperations(key);
    keys.keySpecialStates[key] = false; // Set the state of the current key to not pressed
    
}
