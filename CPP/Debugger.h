//
//  WorldConstants.h
//  openglplus
//
//  Created by Max Bilbow on 02/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef openglplus_WorldConstants_h
#define openglplus_WorldConstants_h
#define _INFINITY 99999
#define PI (3.14159265f)

#define U_DEPTH       2
#define U_HORIZONTAL  0
#define U_VERTICAL    1
#define TWIST_AXIS    1
#define NOD_AXIS      0
#define ROLL_AXIS     2
#define U_SPEED       0.05
#define PI_OVER_180 (PI / 180)

#endif
#define RMX_DEPRECATED(from, to) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##from, __MAC_##to, __IPHONE_NA, __IPHONE_NA)


struct WorldConstants {
    static const bool WATCHING = false;
    //static const float PI_OVER_180 = PI/180;
    static bool isWatching(bool local){
        return (WATCHING || local);
    }
    
    
};

namespace WC {
    inline namespace WorldConstants{}
};



using namespace std;


struct RMXDebugger {
    int no_checks = 10;
    int tog = 1;

    //bool * print = new bool[10];
    
    string * checks = new string[no_checks];
    int monitor=0;
    bool debugging = false;
    //GLKVector2 win = new GLKVector2(0,0);
    
    
    template <typename Print>
    void feedback(Print* print){
        for (int i=0;i<sizeof(print);++i)
        if (monitor==i){
            cout << print[i] << endl;
        }
    }
    string lastCheck;
    void feedback(GLKVector2 win){
        //feedback(checks);
        
        if (checks[monitor]!=lastCheck){
            string s = to_string(monitor) + ":: " + checks[monitor] + "\n";//= monitor +":: " + checks[monitor] + "\n";
            
            cout << s;
            if (debugging)
                this->printtext(win,0,0,s);
        }
                
        lastCheck = checks[monitor];
        checks[monitor]="";
    }
    
    void cycle(int dir){
        monitor += dir;
        if(monitor>no_checks)
            monitor = 0;
        if(monitor<0)
            monitor = no_checks-1;
    }
    
    void toScreen(GLKVector2 win, float * color, void* font, char *string)
    {
        glColor4fv(color);
        glRasterPos2f(win.x/2, win.y/2);
        int len, i;
        len = (int)strlen(string);
        for (i = 0; i < len; i++) {
            glutBitmapCharacter(font, string[i]);
        }
        
    }
    
    void toScreen(GLKVector2 win, string string) {
        this->toScreen(win, GLKVector4Make(0,0,0,0).v, GLUT_BITMAP_HELVETICA_10, strdup(string.c_str()));
    }
    
    
    void printtext(GLKVector2 win, int x, int y, string String)
    {
        //(x,y) is from the bottom left of the window
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(0, win.x, 0, win.y, -1.0f, 1.0f);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glPushAttrib(GL_DEPTH_TEST);
        glDisable(GL_DEPTH_TEST);
        glRasterPos2i(x,y);
        for (int i=0; i<String.size(); i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, String[i]);
        }
        glPopAttrib();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
    
};

static RMXDebugger tester = RMXDebugger();





