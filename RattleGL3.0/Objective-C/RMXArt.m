//
//  RMXArt.m
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//
#import <complex.h>
#import <RattleGL-Swift.h>
#import "RattleGLS-Bridging-Header.h"


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
    
    
    
    RMXParticle * sun = [RMXParticle NewWithWorld:world parent:nil];
    //[sun setRAxis:GLKVector3Make(0, 0, 1)];
    sun.body.radius = 100;
    sun.shape.color = GLKVector4Make(0.5,0.5,0.5,0.5);
    [sun.shape makeAsSunWithRDist:world.body.radius*2 isRotating:true];
    [sun.shape setRender: DrawSphere];
    [world insertSprite:sun];
    
    float * axisColors[3] = {colorBlue , colorRed , colorGreen};
    
    RMXParticle *ZX = [RMXParticle NewWithWorld:world parent:world];
    [ZX.shape setRender:DrawPlane];
    ZX.shape.color = GLKVector4Make(0.8,1.2,0.8,0.5);
    ZX.isAnimated = false;
    ZX.body.position = SCNVector3Make(ZX.body.position.x, 0, ZX.body.position.z);
    [world insertSprite:ZX];

    [RMXArt drawAxis:axisColors world:world];
    [RMXArt randomObjects:world];
    
   
    
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
                RMXParticle * object = [RMXParticle NewWithWorld:world parent:nil];
                object.hasGravity = false;// ? true : false];
                [object.shape setRender:DrawCubeWithTextureCoords];
                object.body.radius = limit/2;
                object.body.position = SCNVector3FromFloat3(axis[j]);
                if ( j != 1 ) object.body.position = SCNVector3Make(object.body.position.x, object.body.radius, object.body.position.z);
                object.shape.color = GLKVector4MakeWithArray(colors[j]);
                object.isAnimated = false;
                [world insertSprite:object];
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
        RMXParticle * object;
        if(false){//(rand() % 10000) == 1) {
            object = [RMXParticle NewWithWorld:world parent:nil];
            [object.shape makeAsSunWithRDist:0 isRotating:false];
        }
        else {
            object = [RMXParticle NewWithWorld:world parent:nil];
        }
        
        if(rand() % 500 == 1) {
            [object.shape setRender:DrawSphere];
        } else {
            [object.shape setRender:DrawCubeWithTextureCoords];
        }
        
        [object setHasGravity: (rand()% 100)==1];
        object.body.radius = (rand() % 3 + 2);
        object.body.position = SCNVector3Make(randPos[0], randPos[1], randPos[2]);
        object.body.mass = (rand()%15+2)/10;
        object.body.dragC = (rand()% 99+1)/100;
        [object.shape setColor:[self rColor]];
        [world insertSprite:object];
        
        
    }
}


+ (GLKVector4)rColor {
    //float rCol[4];
    GLKVector4 rCol = GLKVector4Make(0,0,0,0);
    //rCol.x = (rand() % 100)/10;
    for (int i = 0; i<3; ++i)
        rCol.v[i] = (rand() % 800)/500;
    
    rCol.v[3] = 1.0;//{ ( ,(rand() % 100)/10,(rand() % 100)/10, 1.0 };
    //if (rCol.v[2] == rCol.z) NSLog(@"Fuck me!");
    return rCol;
}



- (void)debug {
   // [rmxDebugger add:RMX_ERROR n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
}


@end

