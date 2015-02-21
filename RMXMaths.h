//
//  Maths.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 20/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#ifndef OpenGL_2_0_Maths_h
#define OpenGL_2_0_Maths_h


#endif
#include <complex.h>
#include <math.h>


#define _INFINITY               99999
#define PI                      3.14159265358979323846


typedef struct _RMXVector2 {
    struct {
        float x,y;
        float v[2];
    };
} RMXVector3;


typedef struct _RMXVector3 {
    struct {
        complex double x,y, z;
        complex double v[3];
    };
} RMXVector2;

typedef struct _RMXVector4 {
    struct {
        float w, x,y, z;
        float v[4];
    };
} RMXVector4;


typedef struct _RMXbody
{
    double p[3];//position
    double v[3];//velocity
    double a[3];//acceleration
    double radius;
    double mass;
}RMXBody;

float rmxEquateContours(float x, float y){
    return x+y;//((x*x +3*y*y) / 0.1 * 50*50 ) + (x*x +5*y*y)*exp2f(1-50*50)/2;
}

float rmxEquateCircle(float x, float y, float r, float plane){
    
    return sqrt(x*x+y*y);//((x*x +3*y*y) / 0.1 * 50*50 ) + (x*x +5*y*y)*exp2f(1-50*50)/2;
}


RMXVector4 point_on_circle ( double radius, double angle_in_degrees,  double centre)
{
    RMXVector4 result;

    result.x = centre + radius * cexp ( PI * I * ( angle_in_degrees  / 180.0 ) );
    result.y = 0;
    result.z = centre + radius * csin ( PI * I * ( angle_in_degrees  / 180.0 ) );
    return result;
}


