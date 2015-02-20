//
//  Art.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 23/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Art_h
#define OpenGL_2_0_Art_h

//#define _INFINITY 9999
#endif

#include "Shapes.h"
#include "LightSource.h"

@interface Art : RMXObject
@property GLfloat x, y, z, d, r,g, b,k;
@property ShapeObject * sh, * sh2, * sh3, *sh4;
@end

void RenderObjects(void);


@implementation Art

@synthesize sh, sh2, sh3, sh4,  x, y, z, d, r,g, b,k;

float colorBronzeDiff[4] = { 0.8, 0.6, 0.0, 1.0 };
float colorBronzeSpec[4] = { 1.0, 1.0, 0.4, 1.0 };
float colorBlue[4]       = { 0.0, 0.2, 1.0, 1.0 };
float colorNone[4]       = { 0.0, 0.0, 0.0, 0.0 };
float red[4]             = { 1.0, 0.0, 0.0, 1.0 };
float green[4]           = { 0.0, 0.0, 1.0, 1.0 };
float yellow[4]          = { 1.0, 0.0, 1.0, 1.0 };

    GLfloat x, y, z, d, r,g, b,k;
    enum{
        XY,
        XZ,
        YX,
        YZ,
        ZX,
        ZY
    };
    
- (id)initWithName:(NSString *)name
{
    self = [super initWithName:name];
    
    if (self) {
        self.x = 0;//45.0f;
        self.y = (GLfloat)250/(GLfloat)250;
        self.z = 0.1f;
        self.d = 100.0f;
        self.r = 0.5f;
        self.g = 0.2f;
        self.b = 0.2f;
        self.k = 0.0f;
    }

//    self.sh = [[ShapeObject alloc]initWithName:@"Shape1"];
//    self.sh2 = [[ShapeObject alloc]initWithName:@"Shape2"];
//    self.sh3 = [[ShapeObject alloc]initWithName:@"Shape3"];
//    self.sh4 = [[ShapeObject alloc]initWithName:@"Shape4"];
//
//    
//    //sh = &world.getShapes()[World::Objects::BOX1];
//    [sh calculatePosition:GLKVector3Make(6,0,0)];
//    [sh setColor:GLKVector4MakeWithArray(yellow)];
//    self.sh.rAxis = GLKVector3Make(0,1,0);
//    
//    
//    //sh2 = &world.getShapes()[1];
//    [sh2 calculatePosition:GLKVector3Make(-3,0,0)];
//    [sh2 setColor:GLKVector4MakeWithArray(red)];
//    self.sh2.rAxis = GLKVector3Make(0,1,0);
//    
//    //sh3 = &world.getShapes()[2];
//    [sh3 calculatePosition:GLKVector3Make(3,0,0)];
//    [sh3 setColor:GLKVector4MakeWithArray(colorBlue)];
//    self.sh3.rAxis = GLKVector3Make(0,1,0);
//    
//    [sh4 calculatePosition:GLKVector3Make(0,0,-3)];
//    [sh4 setColor:GLKVector4MakeWithArray(green)];
//    self.sh4.rAxis = GLKVector3Make(0,1,0);
//    
//    [world insertSprite: self.sh];
//    [world insertSprite: self.sh2];
//    [world insertSprite: self.sh3];
//    [world insertSprite: self.sh4];
    
    sun = [[LightSource alloc]initWithName:@"SUN"];
    [world insertSprite: sun];
    
    [self randomObjects];
    
    return self;
    
    
}

- (void)drawThings
{
    for (ShapeObject* sprite in [world sprites]){
        if ([sprite class]==[ShapeObject class]) {
            glMaterialfv(GL_FRONT, GL_SPECULAR, [sprite getColorfv]);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, [sprite getColorfv]);
            glPushMatrix();
            //glTranslatef(3, 0, 0);
            [sprite draw:DrawCubeWithTextureCoords];
            glPopMatrix();
            glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, colorNone);
        }
    }
}



- (void)randomObjects
{
    //int max =100, min = -100;
    BOOL gravity = true;
    
    for(int i=0;i<1000;++i){
        float X = i;//rand() % max + min;
        float Y = i;
        float Z = contours(X,Y);
        //float randPos[3] = {(rand() % (max + min))-max/2, (rand() % max), (rand() % (max + min))-max/2};
        float randPos[3] = { X, Y, Z };
        gravity = !gravity;
        ShapeObject * shape;
        if((rand() % 1000 == 1)) {
            shape = [[LightSource alloc]initWithName:[NSString stringWithFormat:@"Sun: %i",i ]];
        }
        else {
            shape = [[ShapeObject alloc]initWithName:[NSString stringWithFormat:@"Shape: %i",i ]];
        }
        [shape setHasGravity: gravity];
        [shape setSize:(rand() % 10 + 1)/10];
        [shape calculatePosition:GLKVector3MakeWithArray(randPos)];
        [shape setColor:GLKVector4MakeWithArray([self rColor])];
       // shape.rAxis = GLKVector3Make((rand() % 100)/10,(rand() % 100)/10,(rand() % 100)/10);
        
        [world insertSprite:shape];
        //free(&shape);

    }
}

float contours(float x, float y){
    return ((x*x +3*y*y) / 0.1 * 50*50 ) + (x*x +5*y*y)*exp2f(1-50*50)/2;
}
- (float*)rColor {
    float randomColor[4] = { (rand() % 100)/10 ,(rand() % 100)/10,(rand() % 100)/10, 1.0 };
    return randomColor;
}
- (void)drawPlane
{
    glPushMatrix();
    glColor4fv(colorBlue);
    
    glTranslatef(0, -1, 0);
    glBegin(GL_QUADS);
    glVertex3f( -_INFINITY,-0.001, -_INFINITY);
    glVertex3f( -_INFINITY,-0.001,_INFINITY);
    glVertex3f(_INFINITY,-0.001,_INFINITY);
    glVertex3f(_INFINITY,-0.001, -_INFINITY);
    glEnd();
    glColor4fv(colorNone);
    glPopMatrix();

    
//        glBegin(GL_LINES);
//        for(int i=0;i<=10;i++) {
//            if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
//            glVertex3f(i,0,0);
//            glVertex3f(i,0,10);
//            if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
//            glVertex3f(0,0,i);
//            glVertex3f(10,0,i);
//        };
//        glEnd();
    }
    
- (void)animate
{
    // We don't use bias in the shader, but instead we draw back faces,
    // which are already separated from the front faces by a small distance
    // (if your geometry is made this way)
    glCullFace(GL_FRONT);
    glClearColor(r, g, b, y);
    
    [self drawThings];
    
    glPushMatrix();
    
    RenderObjects();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GLKVector4Make(0.8,0.8,0.8,1).v);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
    [self drawPlane];
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorNone);
    
   
    glPopMatrix();
    
        }
- (void)debug {
    [rmxDebugger add:RMX_ART n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}


@end

//Particle pCube = Particle();
void RenderObjects(void)
{
    
    glMatrixMode(GL_MODELVIEW);
    
    glPushMatrix();
    // Main object (cube) ... transform to its coordinates, and render
    glRotatef(15, 1, 0, 0);
    glRotatef(45, 0, 1, 0);
    glRotatef(g_fTeapotAngle, 0, 0, 1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBlue);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
    glColor4fv(colorBlue);
    glBindTexture(GL_TEXTURE_2D, TEXTURE_ID_CUBE);
    DrawCubeWithTextureCoords(1.0);
    // Child object (teapot) ... relative transform, and render
    glPushMatrix();
    glTranslatef(2, 0, 0);
    glRotatef(g_fTeapotAngle2, 1, 1, 0);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, colorBronzeDiff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, colorBronzeSpec);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
    glColor4fv(colorBronzeDiff);
    glBindTexture(GL_TEXTURE_2D, 0);
    glutSolidTeapot(0.3);
    glPopMatrix();
    glPopMatrix();
    
    
}


static const Art *art;// = Art();


