//
//  RMXCamera.swift
//  RattleGL
//
//  Created by Max Bilbow on 13/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation

@objc public class RMXCamera {
    
    var scene: RMXGLView?
    var pov: RMSParticle?
    var near, far, angle: Float
    
    init(world: RMXGLView?, pov: RMSParticle! = nil, farPane far: Float = 2000 ){
        self.scene = world ?? pov as! RMXWorld
        self.far = far
        self.near = 1
        self.angle = 65.0
        self.pov = pov ?? world?.activeSprite
    }
    
    
    
    public var eye: GLKVector3 {
        return self.pov!.body.position
    
    }
    
    public var center: GLKVector3{
        return GLKVector3Add(GLKVector3Make(Float(self.pov!.body.orientation.m13), Float(self.pov!.body.orientation.m23), Float(self.pov!.body.orientation.m33)), self.pov!.body.position)
    }
    
    public var up: GLKVector3 {
        let simple = true
        if simple {
            return GLKVector3Make(0,1,0)
        } else {
            //return SCNVector3Make(pov.body.orientation.m12,pov.body.orientation.m22,pov.body.orientation.m32)
        }
    }
    
    private func makeLookAtGl(lookAt: CFunctionPointer<(Double, Double, Double, Double, Double, Double, Double, Double, Double) -> Void>) -> Void {
     //   RMSMakeLookAtGL(self)
        RMXMakeLookAtGL(lookAt,
            Double(self.eye.x),     Double(self.eye.y),    Double(self.eye.z),
            Double(self.center.x),  Double(self.center.y), Double(self.center.z),
            Double(self.up.x),      Double(self.up.y),     Double(self.up.z)
        )
    
        
    }
    
    
    func updateView(inout effect: GLKBaseEffect){
        if RMX.usingDepreciated {
            RMXGLMakeLookAt(self)
        } else {
            effect.transform.modelviewMatrix = GLKMatrix4MakeLookAt(
                            self.eye.x, self.eye.y, self.eye.z,
                            self.center.x,  self.center.y, self.center.z,
                            self.up.x,      self.up.y,     self.up.z)
        }
//        RMXGLKMakeLookAt(&effect,self)
    }
    
    var viewDescription: String {
        return "\n      EYE x\(self.eye.x), y\(self.eye.y), z\(self.eye.z)\n   CENTRE x\(self.center.x), y\(self.center.y), z\(self.center.z)\n      UP: x\(self.up.x), y\(self.up.y), z\(self.up.z)\n"
    }
    

    
    func makePerspective(width: Int32, height:Int32, inout effect: GLKBaseEffect?){
        if RMX.usingDepreciated {
            RMXGLMakePerspective(self.angle, Float(width) / Float(height), self.near, self.far)
        } else {
            effect?.transform.projectionMatrix = GLKMatrix4MakePerspective(self.angle, Float(width) / Float(height), self.near, self.far)
        }
    }
    
    

}