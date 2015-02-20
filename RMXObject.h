//
//  RMXObject.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 19/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_RMXObject_h
#define OpenGL_2_0_RMXObject_h


#endif




@implementation RMXObject : NSObject
@synthesize name = _name;
- (id)initWithName:(NSString*)name{
    self = [super init];
    _name = name;
    return self;
}
- (void)debug {
    //[rmxDebugger add:RMX_ERROR n:self t:_name];
}
@end

union GLKVector3 {
    struct{
        
    };
    
}RMXVector3;