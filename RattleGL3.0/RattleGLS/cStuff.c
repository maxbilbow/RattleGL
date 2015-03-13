//
//  cStuff.c
//  RattleGL
//
//  Created by Max Bilbow on 11/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#include "cStuff.h"


void RMXMakeLookAtGL(void (* lookAt)(double eyeX, double eyeY, double eyez,
                                     double centerX, double centerY, double centerZ,
                                     double upX, double upY, double upZ),double eyeX, double eyeY, double eyez,
                     double centerX, double centerY, double centerZ,
                     double upX, double upY, double upZ) {
    lookAt(eyeX,eyeY,eyez,
           centerX,centerY,centerZ,
           upX,upY,upZ);
    
}