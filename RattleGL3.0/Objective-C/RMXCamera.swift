//
//  RMXCamera.swift
//  RattleGL
//
//  Created by Max Bilbow on 13/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation

@objc public class RMXCamera {
    
    var parent: RMXParticle!
    
    init(parent: RMXParticle! = nil){
        self.parent = parent
    }
    
    var eye: RMXVector3 {
        return parent.body.position
    
    }
    
    var center: RMXVector3{
        return RMXVector3Add(SCNVector3Make(parent.body.orientation.m13,parent.body.orientation.m23,parent.body.orientation.m33),
        parent.body.position)
    }
    
    var up: RMXVector3 {
        let simple = true
        if simple {
            return SCNVector3Make(0,1,0)
        } else {
            //return SCNVector3Make(parent.body.orientation.m12,parent.body.orientation.m22,parent.body.orientation.m32)
        }
    }
    
    func makeLookAtGl(lookAt: CFunctionPointer<(Double, Double, Double, Double, Double, Double, Double, Double, Double) -> Void>) -> Void {
        
        RMXMakeLookAtGL(lookAt,
            Double(self.eye.x),     Double(self.eye.y),    Double(self.eye.z),
            Double(self.center.x),  Double(self.center.y), Double(self.center.z),
            Double(self.up.x),      Double(self.up.y),     Double(self.up.z)
        )
        
    }
    
    var viewDescription: String {
        return "\n      EYE x\(self.eye.x), y\(self.eye.y), z\(self.eye.z)\n   CENTRE x\(self.center.x), y\(self.center.y), z\(self.center.z)\n      UP: x\(self.up.x), y\(self.up.y), z\(self.up.z)\n"
    }
    
    
    

}