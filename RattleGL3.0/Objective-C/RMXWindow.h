//
//  RMXWindow.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXWindow_h
#define RattleGL3_0_RMXWindow_h


#endif

#define VIEWING_DISTANCE_MIN  3.0

@interface RMXWindow :  RMXObject
@property float fViewDistance, nearPlane, farPlane;
@property int winID;
@property (getter = isFullscreen) bool fullscreen;
@property GLKVector2 size;
@property const char * title;
@property (readonly) float width,height;

@property void
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

- (id)initWithMethods:
//Display
(void(int width, int height))initWindowSize
//void (*initDisplayMode)(unsigned int mode),
                 disp:(void(void (*func)(void)))displayFunc
                   rs:(void(void (*func)(int width, int height)))reshapeFunc
//Keyboard
                   kp:(void(void (*func)(unsigned char key, int x, int y)))keyPressed
                   ku:(void(void (*func)(unsigned char key, int x, int y)))keyUp
                   ks:(void(void (*func)(int key, int x, int y)))keySpecial
                  ksu:(void(void (*func)(int key, int x, int y)))keySpecialUp
//Mouse
                   mf:(void(void (*func)(int button, int state, int x, int y)))mouseFunc
                   mF:(void(void (*func)(int x, int y)))motionFunc
                  pmf:(void(void (*func)(int x, int y)))passiveMotionFunc
//Other
                   iF:(void(void (*func)(void)))idleFunc;

- (void)toggleFullScreen RMX_DEPRECATED(10_0, 10_9);
- (void)create:(int(const char * s))createWindow;
- (void)display:(void(void))display rs:(void(int width, int height))reshape;
- (void)keyboard:(void(unsigned char key, int x, int y))pressed
              up:(void(unsigned char key, int x, int y))up
              sp:(void(int key, int x, int y))special
             spU:(void(int key, int x, int y))specialUp;

- (void)mouse:(void(int button, int state, int x, int y))mouse
            m:(void(int x, int y))motion
           pm:(void(int x, int y))passiveMotion;

- (void)idle:(void (void))func;
- (void)setSize:(int)width h:(int)height;
@end


//RMXWindow * window;// = RMXWindow;