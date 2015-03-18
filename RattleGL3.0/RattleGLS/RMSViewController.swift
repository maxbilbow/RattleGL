//
//  RMXViewController.swift
//  RattleGL
//
//  Created by Max Bilbow on 18/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation
import OpenGL


public class RMSViewController : UIViewController {
    var program: GLuint = 0
    
    var modelViewProjectionMatrix: GLKMatrix4 = GLKMatrix4Identity
    var normalMatrix: GLKMatrix3 = GLKMatrix3Identity
    var rotation: Float = 0.0
    
    var vertexArray: GLuint = 0
    var vertexBuffer: GLuint = 0
    
    var context: EAGLContext? = nil
    var effect: GLKBaseEffect? = nil
}