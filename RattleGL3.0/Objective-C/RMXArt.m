//
//  RMXArt.m
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#import "RattleGLS-Bridging-Header.h"
#import <complex.h>
#import <RattleGL-Swift.h>

float colorBronzeDiff[4]  = { 0.8, 0.6, 0.0, 1.0 };
 float colorBronzeSpec[4]  = { 1.0, 1.0, 0.4, 1.0 };
float colorWhite[4]        = { 1,1,1,1 };
float colorBlue[4]        = { 0.0, 0.0, 0.1, 1.0 };
 float colorNone[4]        = { 0.0, 0.0, 0.0, 0.0 };
 float colorRed[4]         = { 0.1, 0.0, 0.0, 1.0 };
 float colorGreen[4]       = { 0.0, 0.1, 0.0, 1.0 };
 float colorYellow[4]      = { 1.0, 0.0, 0.0, 1.0 };
 float nillVector[4]       = {0,0,0,0};

@implementation RMXArt

/*
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
    
    return self;
    
    
}

*/
+ (RMXWorld*)initializeTestingEnvironment {
    
    //if (world == nil){
    RMXWorld* world = [RMXWorld New];
    // world.uiView = sender;
    //world.observer.uiView = sender;
    if (world.observer == nil )exit(0);
    //}
    
    
    
    RMXLightSource * sun = [[RMXLightSource alloc]initWithName:@"SUN" parent:world world:world];
    //[sun setRAxis:GLKVector3Make(0, 0, 1)];
    sun.body.radius = 100;
    
    [sun setColorfv:colorWhite];
    
    float * axisColors[3] = {colorBlue , colorRed , colorGreen};
    
    [sun setRender: DrawSphere];
    
    
    
    [sun setShine:glLightfv];
    
    [world insertSprite:sun];
    [RMXArt drawAxis:axisColors world:world];
    
    [RMXArt randomObjects:world];
    
    RMXShapeObject *ZX = [[RMXShapeObject alloc]initWithName:@"ZX PLANE" parent:world world:world];
    [ZX setRender:DrawPlane];
    float planeColor[4]= {0.8,1.2,0.8,1};
    [ZX setColorfv:planeColor];
    ZX.isAnimated = false;
    ZX.body.position = SCNVector3Make(ZX.body.position.x, 0, ZX.body.position.z);
    [world insertSprite:ZX];
    
    return world;
    
}

+ (void)drawAxis:(float**)colors world:(RMXWorld*)world {//xCol y:(float*)yCol z:(float*)zCol{
    //BOOL gravity = false;
    double noOfShapes = world.body.radius / 4;
    vector_float3 axis[3];
    double limit = world.body.radius / noOfShapes;
    int test = 0;
    for (int j=0;j<3;++j) {
        int count = 0;
        for(int i=-world.body.radius;i<world.body.radius;++i) {
            if (count<limit) {
                ++count;
            } else {
                count = 0;
                axis[j][j] = i;
                RMXShapeObject * shape = [[RMXShapeObject alloc]initWithName:[NSString stringWithFormat:@"Shape: %i",i ] parent:world world:world];
                [shape setHasGravity: false];// ? true : false];
                [shape setRender:DrawCubeWithTextureCoords];
                shape.body.radius = limit/2;
                shape.body.position = SCNVector3FromFloat3(axis[j]);
                if ( j != 1 ) shape.body.position = SCNVector3Make(shape.body.position.x, shape.body.radius, shape.body.position.z);
                [shape setColorfv:colors[j]];
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
    double noOfShapes = 1980;
    for(int i=-noOfShapes/2;i<noOfShapes/2;++i) {
        GLKVector4 points = doASum(world.body.radius, i,noOfShapes );
        complex double X = points.x;
        complex double Y = points.y;
        complex double Z = points.z;
        //float randPos[3] = {(rand() % (max + min))-max/2, (rand() % max), (rand() % (max + min))-max/2};
        int chance = 1;//(rand() % 6 + 1);
        vector_float3 randPos = { X, Y, Z };
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
        RMXShapeObject * shape;
        if(false){//(rand() % 10000) == 1) {
            shape = [[RMXLightSource alloc]initWithName:[NSString stringWithFormat:@"Sun: %i",i ] parent:world world:world];
            //shape->body.radius = 20;
            [shape setShine:glLightfv];
            //[shape setRender:DrawCubeWithTextureCoords];
        }
        else {
            shape = [[RMXShapeObject alloc]initWithName:[NSString stringWithFormat:@"Shape: %i",i ] parent:world world:world];
        }
        
        if(rand() % 500 == 1) {
            [shape setRender:DrawSphere];
        } else {
            [shape setRender:DrawCubeWithTextureCoords];
        }
        
        [shape setHasGravity: (rand()% 100)==1];
        shape.body.radius = (rand() % 3 + 2);
        shape.body.position = SCNVector3FromFloat3(randPos);
        shape.body.mass = (rand()%15+2)/10;
        //int drag = shape->body.mass * 10;
        shape.body.dragC = (rand()% 99+1)/100;
        //shape->body.dragArea = shape->body.radius * shape->body.radius * PI;
        [shape setColor:[self rColor]];
        // shape.rAxis = GLKVector3Make((rand() % 100)/10,(rand() % 100)/10,(rand() % 100)/10);
        
        [world insertSprite:shape];
        
        //free(&shape);
        
    }
}


+ (vector_float4)rColor {
    //float rCol[4];
    vector_float4 rCol;
    //rCol.x = (rand() % 100)/10;
    for (int i = 0; i<3; ++i)
        rCol[i] = (rand() % 800)/500;
    
    rCol[3] = 1.0;//{ ( ,(rand() % 100)/10,(rand() % 100)/10, 1.0 };
    //if (rCol.v[2] == rCol.z) NSLog(@"Fuck me!");
    return rCol;
}



- (void)debug {
   // [rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}


@end

