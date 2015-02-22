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





void RenderObjects(void);


@implementation RMXArt

//@synthesize x, y, z, d, r,g, b,k;


- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    
    if (self) {
//        self.x = 0;//45.0f;
//        self.y = (GLfloat)250/(GLfloat)250;
//        self.z = 0.1f;
//        self.d = 100.0f;
//        self.r = 0.8f;
//        self.g = 0.85f;
//        self.b = 1.8f;
//        self.k = 0.0f;
        
    }
    
    return self;
    
    
}


+ (RMXWorld*)initializeTestingEnvironment:(RMXWorld*)world {

    //if (world == nil){
         world = [[RMXWorld alloc]initWithName:@"Brave New World" parent:nil world:nil];
    //}
    
    LightSource * sun = [[LightSource alloc]initWithName:@"SUN" parent:world world:world];
    //[sun setRAxis:GLKVector3Make(0, 0, 1)];
    sun->body.radius = 100;
    [world insertSprite: sun];
    
    
    
    float* axisColors[3] = {colorBlue , colorRed , colorGreen};
    [RMXArt drawAxis:axisColors world:world];
    [sun setRender: DrawSphere];
    [sun setShine:glLightfv];
    [RMXArt randomObjects:world];
    
    ShapeObject *ZX = [[ShapeObject alloc]initWithName:@"ZX PLANE" parent:world world:world];
    [ZX setRender:DrawPlane];
    [ZX setColor:GLKVector4Make(0.8,1.2,0.8,1)];
    [ZX setIsAnimated:false];
    ZX->body.position.y = -1;
    [world insertSprite:ZX];
    
    return world;

}

+ (void)drawAxis:(float**)colors world:(RMXWorld*)world {//xCol y:(float*)yCol z:(float*)zCol{
    //BOOL gravity = false;
    double noOfShapes = world->body.radius / 4;
    float axis[3][3];
    double limit = world->body.radius / noOfShapes;
    int test = 0;
    for (int j=0;j<3;++j) {
        int count = 0;
        for(int i=-world->body.radius;i<world->body.radius;++i) {
            if (count<limit) {
                ++count;
            } else {
                count = 0;
                axis[j][j] = i;
                ShapeObject * shape = [[ShapeObject alloc]initWithName:[NSString stringWithFormat:@"Shape: %i",i ] parent:world world:world];
                [shape setHasGravity: false];// ? true : false];
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
    //[rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"axis shapes: %i, radius: %f",test,self.parent->body.radius ]];
}

+ (void)randomObjects:(RMXWorld*)world
{
    //int max =100, min = -100;
    //BOOL gravity = true;
    double noOfShapes = 360;
    for(int i=-noOfShapes/2;i<noOfShapes/2;++i) {
        GLKVector4 points = doASum(world->body.radius, i,noOfShapes );
        complex double X = points.x;
        complex double Y = points.y;
        complex double Z = points.z;
        //float randPos[3] = {(rand() % (max + min))-max/2, (rand() % max), (rand() % (max + min))-max/2};
        int chance = (rand() % 6 + 1);
        float randPos[3] = { X, Y, Z };
        switch (chance) {
            case 1:
                randPos[0] = X;
                randPos[1] = Y;
                randPos[2] = Z;
                break;
            case 2:
                randPos[0] = Z;
                randPos[1] = X;
                randPos[2] = Y;
                break;
            case 3:
                randPos[0] = Y;
                randPos[1] = Z;
                randPos[2] = X;
                break;
            case 4:
                randPos[0] = Y;
                randPos[1] = X;
                randPos[2] = Z;
                break;
            case 5:
                randPos[0] = X;
                randPos[1] = Z;
                randPos[2] = Y;
                break;
            case 6:
                default:
                randPos[0] = Z;
                randPos[1] = Y;
                randPos[2] = X;
                break;
                
            
        }
        randPos[1]+=50;
        
        //gravity = !gravity;
        ShapeObject * shape;
        if((rand() % 100 == 1)) {
            shape = [[LightSource alloc]initWithName:[NSString stringWithFormat:@"Sun: %i",i ] parent:world world:world];
            shape->body.radius = 20;
        }
        else {
            shape = [[ShapeObject alloc]initWithName:[NSString stringWithFormat:@"Shape: %i",i ] parent:world world:world];
        }
        
        if(rand() % 5 == 1) {
            [shape setRender:DrawSphere];
        } else if (rand() % 3 == 1) {
            [shape setRender:DrawTeapot];
        } else {
            [shape setRender:DrawCubeWithTextureCoords];
        }
        
        [shape setHasGravity: (rand()% 1000 + 1)==1];
        shape->body.radius = (rand() % 5 + 4);
        shape->body.position = GLKVector3MakeWithArray(randPos);
        [shape setColor:GLKVector4MakeWithArray([self rColor].v)];
       // shape.rAxis = GLKVector3Make((rand() % 100)/10,(rand() % 100)/10,(rand() % 100)/10);
        
        [world insertSprite:shape];
        
        //free(&shape);

    }
}


+ (GLKVector4)rColor {
    //float rCol[4];
    GLKVector4 rCol;
    //rCol.x = (rand() % 100)/10;
    for (int i = 0; i<3; ++i)
        rCol.v[i] = (rand() % 100)/10;
    
    rCol.v[3] = 1.0;//{ ( ,(rand() % 100)/10,(rand() % 100)/10, 1.0 };
    //if (rCol.v[2] == rCol.z) NSLog(@"Fuck me!");
    return rCol;
}

    /*
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
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, GLKVector4Make(0.8,1.2,0.8,1).v);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, green);
    //[self drawPlane];
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, colorNone);
    
   
    glPopMatrix();
    
        }
- (void)debug {
    [rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}
*/

@end




