//
//  RMXArt.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

//const vector_float4 colorBronzeDiff, colorBronzeSpec, colorBlue, colorRed, colorGreen, colorYellow, nillVector;

@interface RMXArt   

//@property float x, y, z, d, r, g, b, k;
+ (RMXWorld*)initializeTestingEnvironment;
+ (void)randomObjects:(RMXWorld*)sender;
+ (void)drawAxis:(float**)colors world:(RMXWorld*)world;
+ (GLKVector4)rColor;

@end

//const RMXArt* art;