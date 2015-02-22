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



void RenderObjects(void);


@implementation Art

@synthesize sh, sh2, sh3, sh4,  x, y, z, d, r,g, b,k;

float colorBronzeDiff[4]  = { 0.8, 0.6, 0.0, 1.0 };
float colorBronzeSpec[4]  = { 1.0, 1.0, 0.4, 1.0 };
float colorBlue[4]        = { 0.0, 0.0, 1.0, 1.0 };
float colorNone[4]        = { 0.0, 0.0, 0.0, 0.0 };
float colorRed[4]         = { 1.0, 0.0, 0.0, 1.0 };
float colorGreen[4]       = { 0.0, 1.0, 0.0, 1.0 };
float colorYellow[4]      = { 1.0, 0.0, 1.0, 1.0 };

- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    
    if (self) {
        self.x = 0;//45.0f;
        self.y = (GLfloat)250/(GLfloat)250;
        self.z = 0.1f;
        self.d = 100.0f;
        self.r = 0.8f;
        self.g = 0.85f;
        self.b = 1.8f;
        self.k = 0.0f;
        
    }
    
    LightSource * sun = [[LightSource alloc]initWithName:@"SUN" parent:world world:world];
    //[sun setRAxis:GLKVector3Make(0, 0, 1)];
    sun->body.radius = 100;
    [world insertSprite: sun];
    
    
    float* axisColors[3] = {colorBlue , colorRed , colorGreen};
    [self drawAxis:axisColors];
    [sun setRender: DrawSphere];
    [sun setShine:glLightfv];
    //[self randomObjects];
    
    return self;
    
    
}
//
//- (void)drawThings
//{
//    for (ShapeObject* sprite in [world sprites]){
//        if ([sprite class]==[ShapeObject class]) {
//            glMaterialfv(GL_FRONT, GL_SPECULAR, [sprite getColorfv]);
//            glMaterialfv(GL_FRONT, GL_DIFFUSE, [sprite getColorfv]);
//            glPushMatrix();
//            //glTranslatef(3, 0, 0);
//            [sprite draw];//:DrawCubeWithTextureCoords];
//            glPopMatrix();
//            glMaterialfv(GL_FRONT, GL_SPECULAR, colorNone);
//            glMaterialfv(GL_FRONT, GL_DIFFUSE, colorNone);
//        }
//    }
//}

- (void)drawAxis:(float**)colors {//xCol y:(float*)yCol z:(float*)zCol{
    BOOL gravity = false;
    double noOfShapes = self.world->body.radius / 4;
    float axis[3][3];
    double limit = self.parent->body.radius / noOfShapes;
    int test = 0;
    for (int j=0;j<3;++j) {
        int count = 0;
        for(int i=-self.parent->body.radius;i<self.parent->body.radius;++i) {
            if (count<limit) {
                ++count;
            } else {
                count = 0;
                axis[j][j] = i;
                ShapeObject * shape = [[ShapeObject alloc]initWithName:[NSString stringWithFormat:@"Shape: %i",i ] parent:self.parent world:self.world];
                [shape setHasGravity: gravity];
                [shape setRender:DrawCubeWithTextureCoords];
                shape->body.radius = limit;
                shape->body.position = GLKVector3MakeWithArray(axis[j]);
                [shape setColor:GLKVector4MakeWithArray(colors[j])];
                [shape setIsAnimated:false];
                [world insertSprite:shape];
                test++;
            }
        }
    }
    [rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"axis shapes: %i, radius: %f",test,self.parent->body.radius ]];
}

- (void)randomObjects
{
    //int max =100, min = -100;
    BOOL gravity = true;
    double noOfShapes = 360;
    for(int i=0;i<noOfShapes;++i) {
        GLKVector4 points = point_on_circle ( self.parent->body.radius, i* 360/noOfShapes, 0 );
        complex double X = points.x;
        complex double Y = points.y;
        complex double Z = points.z;
        //float randPos[3] = {(rand() % (max + min))-max/2, (rand() % max), (rand() % (max + min))-max/2};
        float randPos[3] = { X, Y, Z };
        gravity = !gravity;
        ShapeObject * shape;
        if((rand() % 1000 == 1)) {
            shape = [[LightSource alloc]initWithName:[NSString stringWithFormat:@"Sun: %i",i ] parent:self.parent world:self.world];
        }
        else {
            shape = [[ShapeObject alloc]initWithName:[NSString stringWithFormat:@"Shape: %i",i ] parent:self.parent world:self.world];
        }
        [shape setHasGravity: gravity];
        shape->body.radius = (rand() % 5 + 4);
        shape->body.position = GLKVector3MakeWithArray(randPos);
        [shape setColor:GLKVector4MakeWithArray([self rColor].v)];
       // shape.rAxis = GLKVector3Make((rand() % 100)/10,(rand() % 100)/10,(rand() % 100)/10);
        
        [world insertSprite:shape];
        //free(&shape);

    }
}


- (GLKVector4)rColor {
    //float rCol[4];
    GLKVector4 rCol;
    //rCol.x = (rand() % 100)/10;
    for (int i = 0; i<3; ++i)
        rCol.v[i] = (rand() % 100)/10;
    
    rCol.v[3] = 1.0;//{ ( ,(rand() % 100)/10,(rand() % 100)/10, 1.0 };
    //if (rCol.v[2] == rCol.z) NSLog(@"Fuck me!");
    return rCol;
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
    
    //[self drawThings];
    
    glPushMatrix();
    
    RenderObjects();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GLKVector4Make(0.8,0.8,0.8,1).v);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
    [self drawPlane];
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorNone);
    
   
    glPopMatrix();
    
        }
- (void)debug {
    [rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
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


