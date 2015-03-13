//
//  RMSMaths.swift
//  RattleGL
//
//  Created by Max Bilbow on 13/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation


extension RMXMatrix4 {
    
    var upVector: RMXVector3 {
        return SCNVector3Make(m12,m22,m32)
    }
    
    var rightVector: RMXVector3 {
        return SCNVector3Make(-m11, -m21, -m31)
    }
    
    var leftVector: RMXVector3 {
        return SCNVector3Make(m11,m21,m31)
    }
    
    var forwardVector: RMXVector3 {
        return SCNVector3Make(m13,m23,m33)
    }
    
}

extension RMXVector3 {
    var isZero: Bool {
        return (x == 0) && (y == 0) && (z == 0)
    }
}