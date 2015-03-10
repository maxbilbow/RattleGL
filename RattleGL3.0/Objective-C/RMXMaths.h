//
//  RMXMaths.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXMaths_h
#define RattleGL3_0_RMXMaths_h


#endif

#define PI                      3.14159265358979323846
#define PI_OVER_180             (PI / 180)

#if defined(__STRICT_ANSI__)
struct _RMXVector2
{
    float v[3];
};
typedef struct _RMXVector2 RMXVector2;
#else
union _RMXVector2
{
    struct { float x, y; };
    struct { float theta, phi; };
    float v[2];
};
typedef union _RMXVector2 RMXVector2;
#endif

typedef GLKVector3 RMXVector3;
typedef GLKMatrix3 RMXMatrix3;
typedef GLKMatrix4 RMXMatrix4;


typedef struct _RMXPhysicsBody
{
    RMXVector3 position;
    RMXVector3 velocity;
    RMXVector3 acceleration;
    RMXVector3 forces;
    RMXMatrix4 orientation;
    RMXMatrix3 vMatrix;
    RMXVector2 angles;
    
    float radius;
    float mass;
    float dragC;
    const float dragArea;
    
}RMXPhysicsBody;


BOOL RMXVector3IsZero(RMXVector3 v);
float RMXGetSpeed(RMXVector3 v);
RMXVector3 RMXVector3Abs(RMXVector3 v);

RMXPhysicsBody RMXPhyisicsBodyMake(float m, float r);

RMXVector3 RMXVector3DivideByScalar(RMXVector3 v, float s);

void RMXVector3RoundToZero(RMXVector3 * v, float dp);

RMXVector3 RMXVector3Divide(RMXVector3 *top, RMXVector3 bottom);

RMXVector3 RMXVector3DivideScalar(RMXVector3 *top, float bottom);

RMXVector3 RMXVector3Add3(RMXVector3 a ,RMXVector3 b, RMXVector3 c );

RMXVector3 RMXVector3Add4(RMXVector3 a ,RMXVector3 b, RMXVector3 c , RMXVector3 d);

RMXVector3 RMXVector3AddScalar(RMXVector3 inOut, float s );

RMXVector3 RMXVector3MultiplyScalarAndSpeed(RMXVector3 v, float s);
RMXVector3 RMXMatrix3MultiplyScalarAndSpeed(RMXMatrix3 m, float s);
RMXVector3 RMXScaler3FromVector3(RMXVector3 x, RMXVector3 y, RMXVector3 z);
RMXVector3 RMXScaler3FromMatrix3(RMXMatrix3 m);
RMXMatrix3 RMXMatrix3RotateAboutY(float theta, RMXMatrix3  matrix);
RMXVector3 RMXMatrix3MultiplyVector3(GLKMatrix3 matrixLeft, GLKVector3 vectorRight);

void RMXPrintMatrix(GLKMatrix4 m);
