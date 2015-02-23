//
//  LightSource.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_LightSource_h
#define OpenGL_2_0_LightSource_h


#endif
#include "ShapeObject.h"


@implementation LightSource


    
- (id)initWithName:(NSString*)name parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    if (self) {
        body.position = GLKVector3Make(50,0,0);
       // self.ground = -_INFINITY;
        self.hasGravity = 0;
        self.w=1;
        body.radius = 100;
        self.isRotating = true;
#ifdef MAC_OS_X
        self.type = GL_POSITION;
        self.gl_light = GL_LIGHT0;
#endif
    }
    return self;
}


    

    
        
- (void)lightUp:(float)i
{
    body.position = GLKVector3Make(body.position.x + i,body.position.y,body.position.z);
    [rmxDebugger add:RMX_LIGHT n:self.name t:[NSString stringWithFormat:@" Light Y: %f", body.position.x]];
}
- (void)lightSwitch:(char)i
{
#ifdef MAC_OS_X

        switch (i){
            case '1':
                self.type = GL_POSITION;
                break;
            case '2':
                self.type = GL_SPECULAR;
                break;
            case '3':
                self.type = GL_AMBIENT;
                break;
            case '4':
                self.type = GL_DIFFUSE;
                break;
            case '5':
                self.type = GL_AMBIENT_AND_DIFFUSE;
                break;
        }
#endif
}
    
- (void)setMaterial{
#ifdef MAC_OS_X

    glMaterialfv(GL_FRONT,GL_EMISSION, self.color.v);
#endif
    [super setMaterial];
}
    
- (void)unsetMaterial{
#ifdef MAC_OS_X

    glMaterialfv(GL_FRONT, GL_EMISSION,nill);
#endif
    [super unsetMaterial];
}

- (void)debug {
    [rmxDebugger add:RMX_LIGHT n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}


@end


