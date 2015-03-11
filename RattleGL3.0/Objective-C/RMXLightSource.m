//
//  LightSource.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.

#import "RattleGL-Bridging-Header.h"
#import <RattleGL-Swift.h>
@implementation RMXLightSource
    
- (id)initWithName:(NSString*)name parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    if (self) {
         //body.position = GLKVector3Make(1000,0,1000);
        self.hasGravity = 0;
        self.w=1;
        self.physicsBody.radius = 50;
        self.isRotating = true;
        self.r = 1000;

        self.type = GL_POSITION;
        self.gl_light = GL_LIGHT0;

        
        
    }
    return self;
}

- (void)animate{
    [super animate];
}
    

    
        
- (void)lightUp:(float)i
{
    body.position = GLKVector3Make(body.position.x + i,body.position.y,body.position.z);
    [rmxDebugger add:RMX_LIGHT n:self.name t:[NSString stringWithFormat:@" Light Y: %f", body.position.x]];
}
- (void)lightSwitch:(char)i
{

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

}
    
- (void)setMaterial{

    glMaterialfv(GL_FRONT,GL_EMISSION, self.color.v);

    [super setMaterial];
}
    
- (void)unsetMaterial{

    glMaterialfv(GL_FRONT, GL_EMISSION,nillVector);

    [super unsetMaterial];
}

- (void)debug {
    [rmxDebugger add:RMX_LIGHT n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}


@end


