//
//  Shader.fsh
//  Lets Make a GLES game
//
//  Created by Max Bilbow on 22/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
