//
//  RMXCamera.swift
//  RattleGL
//
//  Created by Max Bilbow on 13/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation

public class RMXCamera {
    
    var parent: RMXParticle!
    
    init(parent: RMXParticle! = nil){
        self.parent = parent
    }
    
    var eye: RMXVector3 {
        return parent.body.position
    
    }
    
    var center: RMXVector3{
        return RMXVector3Add(SCNVector3Make(parent.body.orientation.m11,parent.body.orientation.m21,parent.body.orientation.m31),
        parent.body.position)
    }
    
    var up: RMXVector3 {
        let simple = true
        if simple {
            return SCNVector3Make(0,1,0)
        } else {
            return SCNVector3Make(parent.body.orientation.m12,parent.body.orientation.m22,parent.body.orientation.m32)
        }
        
    }
    
    
    

}