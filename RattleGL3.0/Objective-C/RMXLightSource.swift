//
//  RMXLightSource.swift
//  RattleGL
//
//  Created by Max Bilbow on 13/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation

@objc public class RMXLightSource : RMXShapeObject {

   
    
    override init!(name: String!, parent: RMXObject!, world: RMXWorld!) {
        super.init(name: name, parent: parent, world: world)
        self.hasGravity = false
        self.body.radius = 50
        self.r = 1000;
        self.isRotating = true
        self.w = 1
        self.type = GL_POSITION
        self.gl_light = GL_LIGHT0
    }
    

    

    
   
    
    
    
    func lightUp(i: CGFloat) {
        self.body.position = SCNVector3Make(self.body.position.x + i,self.body.position.y, self.body.position.z)
    }
    
    func lightSwitch(i: Character) {
    
    switch (i){
        case "1":
            self.type = GL_POSITION;
            break
        case "2":
            self.type = GL_SPECULAR;
            break
        case "3":
            self.type = GL_AMBIENT;
            break
        case "4":
            self.type = GL_DIFFUSE;
            break
        case "5":
            self.type = GL_AMBIENT_AND_DIFFUSE;
            break
        default:
            break
    }

}

    override public func setMaterial(){
        //let color: [Float] = [ self.color.x,self.color.y,self.color.z,self.color.w ]
        RMXGLMaterialfv(GL_FRONT,GL_EMISSION, color);
        super.setMaterial()
    }
    
    override public func unsetMaterial() {
        let nill = GLKVector4Make(0,0,0,0)
        RMXGLMaterialfv(GL_FRONT, GL_EMISSION,nill);//TODO
        
        super.unsetMaterial()
    }
        
}