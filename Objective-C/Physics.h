//
//  Physics.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//




@interface Physics : RMXObject
@property float gravity, friction;
@end

@implementation Physics



@synthesize gravity = _gravity, friction = _friction;//, hasFriction = _hasFriction, hasGravity = _hasGravity;
- (id)initWithName:(NSString*)name
{
    
    self = [super initWithName:name];
    if (self) {
        _gravity = 0.0005;//U_GRAVITY;
        _friction = 0.1;
        NSLog(@"init Physics");
    }
    return self;
}


- (void)addGravity:(float) g
{
    _gravity += g;
    if (_gravity<0)
        _gravity = 0;
    [rmxDebugger add:RMX_PHYSICS n:self t:[NSString stringWithFormat:@" / Gravity: %f", _gravity]];
}


    
- (void)addFriction:(float)f
{
    _friction += f;
    if (_friction<0)
        _friction = 0;
    [rmxDebugger add:RMX_PHYSICS n:self t:[NSString stringWithFormat:@" / Friction: %f",_friction]];
}

- (void)debug {
    [rmxDebugger add:RMX_PHYSICS n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}
    
@end;