//
//  cStuff.h
//  RattleGL
//
//  Created by Max Bilbow on 11/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef __RattleGL__cStuff__
#define __RattleGL__cStuff__

#include <stdio.h>

#endif /* defined(__RattleGL__cStuff__) */

void RMXMakeLookAtGL(void (* lookAt)(double eyeX, double eyeY, double eyez,
                                     double centerX, double centerY, double centerZ,
                                     double upX, double upY, double upZ),double eyeX, double eyeY, double eyez,
                     double centerX, double centerY, double centerZ,
                     double upX, double upY, double upZ);