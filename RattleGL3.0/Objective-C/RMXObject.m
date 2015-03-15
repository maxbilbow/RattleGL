//
//  RMXObject.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 21/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_RMXObject_h
#define OpenGL_2_0_RMXObject_h


#endif

#import "RattleGLS-Bridging-Header.h"
#import <RattleGL-Swift.h>

@implementation RMXObject

- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world{
    self = [super init];
    _parent = parent;
    _world = world;
    //    if (world != nil && [world isKindOfClass:[RMXWorld class]]){
    //        _uiView = ((RMXWorld*)world).uiView;
    //    } else if (world == nil && [parent isKindOfClass:[UIVideoEditorController class]]) {
    //        _uiView = (UIVideoEditorController*) parent;
    //    }
    _name = name;
//    _physics = nil;
    [self reInit];
    return self;
}
- (void)reInit {
    
}
- (void)debug {
}

- (void)plusAngle:(float)x y:(float)y{
    
}


@end
