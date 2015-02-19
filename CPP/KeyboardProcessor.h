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

struct KeyProcessor {
    
    struct {
        bool* keyStates, *keySpecialStates;
        char forward, back, left, right, up, down, stop, jump;
        bool update;
    };
    KeyProcessor(){
        forward = 'w';
        back = 's';
        left = 'a';
        right = 'd';
        up = 'e';
        down = 'q';
        stop = 'f';
        jump = 32;
        keyStates = new bool[256];
        keySpecialStates = new bool[246];
        update = true;
        glutSetKeyRepeat(false);
    }
    ~KeyProcessor(){
       //// glutSetKeyRepeat(true);
    }
    
};

KeyProcessor keys = KeyProcessor();



void repeatedKeys(){
    
    if (keys.keySpecialStates[GLUT_KEY_UP])
        if (keys.keyStates[9])
            sun.lightUp(1);
        else
            observer->extendArmLength(1);

    else if(keys.keySpecialStates[GLUT_KEY_DOWN])
        if (keys.keyStates[9])
            sun.lightUp(-1);
        else
            observer->extendArmLength(-1);
}

void movement(float speed, int key){
    bool test = false;
    //if (keys.keyStates[keys.forward]) observer->accelerateForward(speed);
    if (key == keys.forward) {
        if (!speed)
            observer->forwardStop();
        else
            observer->accelerateForward(speed);
        if(test) cout << keys.forward << " ";
        //TODO
    }
    
    if (key == keys.back) {
        if (!speed)
            observer->forwardStop();
        else
            observer->accelerateForward(-speed);
        if(test) cout << keys.back << " ";
        //TODO
    }
    
    if (key == keys.left) {
        if (!speed)
            observer->leftStop();
        else
            observer->accelerateLeft(speed);
        if(test) cout << keys.left << " ";
    }
    
    if (key == keys.right) {
        if (!speed)
            observer->leftStop();
        else
            observer->accelerateLeft(-speed);
        if(test) cout << keys.right << " ";
        //TODO
    }
    
    if (key == keys.up) {
        if (!speed)
            observer->upStop();
        else
            observer->accelerateUp(speed);
        if(test) cout << keys.up << " ";
        //TODO
    }
    
    if (key == keys.down) {
        if (!speed)
            observer->upStop();
        else
            observer->accelerateUp(-speed);
        if(test) cout << keys.down << " ";
        //TODO
    }
    if (key == 32) {
        if (speed==0)
            observer->upStop();
        else
            observer->jump();
    //TODO
    }

}

void keyDownOperations (int key) {
    bool test = true;
    movement((float)1.0, key);
    if(key =='y') {
        tester.checks[7] += " unassigned";
    }
    if (key =='z') {
        tester.checks[7] += " unassigned";
    }
    if (key =='x') {
        tester.checks[7] += " unassigned";
    }
    
    if (keys.keyStates['=']) {
        if (keys.keyStates['r'])
            art.r += 0.05;
        if (keys.keyStates['g'])
            art.g += 0.05;
        if (keys.keyStates['b'])
            art.b += 0.05;
        if (keys.keyStates['k'])
            art.k += 0.05;
        if (keys.keyStates['G'])
            observer->addGravity(0.1);
        if (keys.keyStates['f'])
            observer->addFriction(0.01);
            
    } else if (keys.keyStates['-']) {
        if (keys.keyStates['r'])
            art.r -= 0.05;
        if (keys.keyStates['g'])
            art.g -= 0.05;
        if (keys.keyStates['b'])
            art.b -= 0.05;
        if (keys.keyStates['k'])
            art.k -= 0.05;
        if (keys.keyStates['G'])
            observer->addGravity(-0.1);
        if (keys.keyStates['f'])
            observer->addFriction(-0.01);
    }
    //if (keys.keySpecialStates[])
    
}

//template <typename Particle>
void keyUpOperations(int key){
    movement((bool)false, key); //Change to Zero if maintaining velocity
    if (key == 'i'){
        cout << "Getting info: (todo)\n";//me.toString();
        cout << observer->toString();
    }
    
    switch (key)
    {
        default:
            tester.checks[7] += " not assigned";
            break;
        case 27:             // ESCAPE key
            //glutSetKeyRepeat(true);
            exit (0);
            break;
        case 'l':
            SelectFromMenu(MENU_LIGHTING);
            break;
        case 'p':
            SelectFromMenu(MENU_POLYMODE);
            break;
        case 't':
            SelectFromMenu(MENU_TEXTURING);
            break;
        case 'm':
            observer->toggleFocus();
            if (observer->hasFocus()){
                //center();
                glutSetCursor(GLUT_CURSOR_NONE);
               
                observer->calibrateMouse(0,0);//observer->getMouse().x,observer->getMouse().y);
                observer->mouse2view(0, 0);
                //glutWarpPointer(0,0);
                
            }
            else {
                glutSetCursor(GLUT_CURSOR_INHERIT);
            }
            break;
        case 32:
    //observer->stop();
            tester.checks[7] += " space bar";
            break;
        case 9:
            //observer->stop();
            tester.checks[7] += " TAB";
            break;
        case 'G':
            observer->toggleGravity();
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
            sun.lightSwitch(key);
            break;
        case 'S':
           // sun.setAnchor(&observer);
            break;
        case 6: //cntrl f
            window.toggleFullScreen();
    }
   // keys.keyStates[key] = false;
    
}
void keySpecialDownOperations(int key) {
    if (key == GLUT_KEY_UP) { // If the left arrow key has been pressed
        //me.look(Observer::UP);
        tester.checks[7] += "up pressed";
        //TODO
    }
    
    if (key == GLUT_KEY_DOWN) {
        //me.look(Observer::DOWN);
        tester.checks[7] += "down pressed";
        //TODO
    }
    
    if (key == GLUT_KEY_LEFT) {
        //me.look(Observer::LEFT);
        tester.checks[7] += "left pressed";
        //TODO
    }
    
    if (key == GLUT_KEY_RIGHT) {
        //me.look(Observer::RIGHT);
        tester.checks[7] += " right pressed";
        //TODO
    }
    
    
    // Perform 'a' key operations
    
}


void keySpecialUpOperations(char key) {
    switch (key){
        case GLUT_KEY_LEFT:
            tester.cycle(-1);
            break;
        case GLUT_KEY_RIGHT:
            tester.cycle(1);
            break;
//        case GLUT_KEY_UP:
//            sun.lightUp(10);
//            break;
//        case GLUT_KEY_DOWN:
//            sun.lightUp(-10);
//            break;
        case 32:
            //observer->stop();
            tester.checks[7] += ": space bar";
            break;

    }
}




void keySpecialOperations(void) {
    keys.update=true;
    //keySpecialDownOperations();
}

void keyPressed (unsigned char key, int x, int y) {
    //char kTemp = key;
    string tmp = to_string(key);//&kTemp;
    tester.checks[7] += tmp + " (down) :";
    keys.keyStates[key] = true; // Set the state of the current key to pressed
    keyDownOperations(key);
}

void keyUp (unsigned char key, int x, int y) {
    string tmp = to_string(key);
    tester.checks[7] += tmp + " (up) :";
    keyUpOperations(key);
    keys.keyStates[key] = false; // Set the state of the current key to not pressed
}
void keySpecial (int key, int x, int y) {
    tester.checks[7] += to_string(key) + " (down special) :";
    keys.keySpecialStates[key] = true; // Set the state of the current key to pressed
    keySpecialDownOperations(key);
}

void keySpecialUp (int key, int x, int y) {
    tester.checks[7] += to_string(key) + " (up special) :";
    keySpecialUpOperations(key);
    keys.keySpecialStates[key] = false; // Set the state of the current key to not pressed
    std::cout << key << std::endl;
    
}
