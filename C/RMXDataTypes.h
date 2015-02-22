//
//  RMXDataTypes.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 21/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_RMXDataTypes_h
#define OpenGL_2_0_RMXDataTypes_h


#endif

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

/*

#if defined(__STRICT_ANSI__)
struct _RMXVector3
{
    float v[3];
};
typedef struct _RMXVector3 RMXVector3;
#else
union _RMXVector3
{
    struct { float x, y, z; };
    struct { float r, g, b; };
    struct { float s, t, p; };
    float v[3];
};
typedef union _RMXVector3 RMXVector3;
#endif

*/

/*
#if defined(__STRICT_ANSI__)
struct _GLKMatrix3
{
    float m[9];
};
typedef struct _GLKMatrix3 GLKMatrix3;
#else
union _GLKMatrix3
{
    struct
    {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
    float m[9];
};
typedef union _GLKMatrix3 GLKMatrix3;
#endif */

typedef GLKVector3 RMXVector3;
typedef GLKMatrix3 RMXMatrix3;


typedef struct _RMXPhysicsBody
{
    RMXVector3 position;
    RMXVector3 velocity;
    RMXVector3 acceleration;
    RMXVector3 forces;
    RMXMatrix3 orientation;
    RMXMatrix3 vMatrix;
    RMXVector2 angles;
    
    float radius;
    float mass;
    float dragC;
    float dragArea;
    
}RMXPhysicsBody;
