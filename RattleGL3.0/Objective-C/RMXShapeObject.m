//
//  ShapeObject.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//
#import "RattleGLS-Bridging-Header.h"

#import <RattleGL-Swift.h>

@implementation RMXShapeObject

- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    if (self) {
        //vector_float4 color = {0,1, 1, 1};
        //self.color = color;
        self.rotationSpeed = 2;
        self.rAxis = SCNVector3Make(0,0,1);
        self.rotation = 0;
        self.isRotating = false;
        self.r = 0;
        
        
       
    }
    return self;
    
}


- (void)draw {
        glPushMatrix();
    
//        glRotatef(_rotation, _rAxis.x, _rAxis.y, _rAxis.z);
//        
//        glPushMatrix();
//        
        glTranslatef(self.anchor.x,self.anchor.y, self.anchor.z);
        glTranslatef(self.body.position.x,self.body.position.y,self.body.position.z);
    
    [self setMaterial];
    _render(self.body.radius);
    [self unsetMaterial];

        glPopMatrix();
       // glPopMatrix();
    
}



- (void)animate
{
    if (_isRotating) {
        _rotation += self.rotationSpeed/_r;
    //body.position.y += _rotation;
        GLKVector4 temp = RMXSomeCircle(_rotation, _r*2);
        self.body.position = SCNVector3Make(temp.x-_r,temp.y,0);
    }
    [super animate];
    if ([self isKindOfClass:[RMXLightSource class]]) {
        //glEnable(GL_LIGHTING);
        // Render lit geometry.
        
                _shine(_gl_light, _type, GLKVector4MakeWithVector3(SCNVector3ToGLKVector3(self.body.position), _w).v);
        //glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 15.f);
        //glDisable(GL_LIGHTING);

    }//else
    [self draw];
    
}

- (void)setMaterial
{
    //glMaterialfv(GL_FRONT, GL_EMISSION, self.color.v);
    //float color[4] = { self.color[0], self.color[1], self.color[2], self.color[3] };
    RMXGLMaterialfv(GL_FRONT, GL_SPECULAR, self.color);
    RMXGLMaterialfv(GL_FRONT, GL_DIFFUSE, self.color);
}

- (void)unsetMaterial
{
     GLKVector4 nill = GLKVector4Make( 0,0,0,0);
    //glMaterialfv(GL_FRONT, GL_EMISSION,nill);
    RMXGLMaterialfv(GL_FRONT, GL_SPECULAR, nill);
    RMXGLMaterialfv(GL_FRONT, GL_DIFFUSE, nill);
}

- (GLKVector4)getColorfv
{
    //float fv[4] = { _color[0], _color[1], _color[2], _color[3] };
    return _color;
}


- (void)setColorfv:(float*)c
{
    for (int i=0;i<4;++i){
        _color.v[i] = c[i];
    }
}

- (void)debug {
    [super debug];
    //[rmxDebugger add:RMX_OBSERVER n:self t:[self describePosition]];
}

@end