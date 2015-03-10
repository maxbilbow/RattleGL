//
//  RMXArt.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

float colorBronzeDiff[4], colorBronzeSpec[4], colorBlue[4], colorNone[4], colorRed[4], colorGreen[4], colorYellow[4], nillVector[4];

@interface RMXArt : RMXObject

@property float x, y, z, d, r, g, b, k;
+ (RMXWorld*)initializeTestingEnvironment:(id)sender;
+ (void)randomObjects:(RMXWorld*)sender;
+ (void)drawAxis:(float**)colors world:(RMXWorld*)world;
+ (GLKVector4)rColor;

@end

const RMXArt* art;