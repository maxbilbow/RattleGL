//
//  Mouse.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 31/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//


#import "RattleGLS-Bridging-Header.h"
@class RMXParticle;
@implementation RMXMouse

- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    _focus = false;
    _dx = 0;
    _dy = 0;
    _pos = GLKVector2Make(0,0);
    
    return self;
}


- (void)toggleFocus
{
    _focus = !_focus;
}

    
    
- (GLKVector2)getMouse
{

    return _pos;
}

- (void)centerView:(void(int x, int y))center
{
    center(_pos.x,_pos.y);
}
- (void)setMousePos:(int)x y:(int)y
{
    _pos.x = x;// + dx;
    _pos.y = y;//;
}

- (void)mouse2view:(int)x y:(int)y
{
        //dx = dy = 0;
        
        
        int DeltaX, DeltaY;// =
    
    CGGetLastMouseDelta(&DeltaX, &DeltaY);
    
    
   // [rmxDebugger add:RMX_MOUSE n:self t:[NSString stringWithFormat:@"Mousie diffX: %i, diffY: %i",DeltaX, DeltaY]];
       
        int dir = _focus ? 1 : -1;
        
        float theta = (float)(DeltaX)*dir;
        float phi = (float)(DeltaY)*dir;// / 20.0f;
    
    [self.parent plusAngle:theta y:phi];
        
    }
    
- (void)calibrateView:(int)x vert:(int)y
{
    CGGetLastMouseDelta(&_dx, &_dy);
}

- (void)debug {
    //[rmxDebugger add:RMX_MOUSE n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}
@end