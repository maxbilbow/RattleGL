//
//  ActionProcessor.h
//  OpenGL 3.0
//
//  Created by Max Bilbow on 14/02/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef OpenGL_3_0_ActionProcessor_h
#define OpenGL_3_0_ActionProcessor_h


#endif
//#include "Observer.h"

@interface ActionProcessor : NSObject
@property bool focus;
@property int dx, dy;
@property GLKVector2 pos;
@property NSString* name;
- (id)init:(NSString*)name;

- (void)toggleFocus;
- (bool)hasFocus;

GLKVector2 getPos();
void setPos(int h, int v);


GLKVector2 getMouse();
void center(void (*center)(int x, int y));

void setMousePos(int x, int y);
- (GLKVector2)mouse2view:(int)x y:(int)y;

void calibrateMouse(int x, int y);

@end




@implementation ActionProcessor

bool focus;
int dx, dy;
GLKVector2 pos;
NSString* name;

- (id)init:(NSString*)name
{
    self = [super init];
    if (self) {
        self.name = name;
        focus = false;
        dx = 0;
        dy = 0;
        pos = GLKVector2Make(0,0);
    }
    return self;
    
    
}
- (void)toggleFocus
{
    focus = !focus;
}

- (bool)hasFocus
{
    return focus;
}

GLKVector2 getPos(){
    return pos;
}

void setPos(int h, int v){
    pos.x=h;
    pos.y=v;
}

void rotate(){};




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
- (GLKVector2)mouse2view:(int)x y:(int)y
{
    //dx = dy = 0;
    
    
    int DeltaX, DeltaY;// =
    
    
    //CGGetLastMouseDelta(&DeltaX, &DeltaY);
    //        pos.x += DeltaX;
    //        pos.y += DeltaY;
    //cout<< "  dx " << "|" << DeltaX << "|" << DeltaY << endl;
    [rmxDebugger add:3 n:self.name t:[NSString stringWithFormat:@"Mousie diffX: %i, diffY: %i", DeltaX, DeltaY]];
    
    
    //DeltaX -= dx; DeltaY -= dy;
    //cout<< "  dx " << "|" << DeltaX << "|" << DeltaY << endl;
    int dir = focus ? 1 : -1;
    
    float theta = (float)(DeltaX)*dir;
    float phi = (float)(DeltaY)*dir;// / 20.0f;
    
    return GLKVector2Make(theta,phi);
    // cout<< "  Mouse Pos: " << "|" << pos.x << "|" << pos.y << endl;
    
    
}

void calibrateMouse(int x, int y){//GLKVector2 pos){
   // CGGetLastMouseDelta(&dx, &dy);
    //        dx += x - CGDisplayPixelsWide(0)/2;
    //        dy += y - CGDisplayPixelsHigh(0)/2;
    //setMousePos(pos.x-dx, pos.y-dy);
   // cout<< "  CALABRATING " << "|" << dx << "|" << dy << endl;
}

@end
