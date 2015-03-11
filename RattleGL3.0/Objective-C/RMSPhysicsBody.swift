//
//  RMSPhysicsBody.swift
//  RattleGL
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import GLUT

@objc public class RMSPhysicsBody {
    
    private let PI: Float = 3.14159265358979323846
    var position: [Float] = [0,0,0]
    var velocity: [Float] = [0,0,0]
    var acceleration: [Float] = [0,0,0]
    var forces: [Float] = [0,0,0]
    var orientation: Matrix4 = Matrix4()
    var vMatrix: Matrix4 = Matrix4()
    
    var theta, phi, radius, mass, dragC: Float32
    var dragArea: Float32 {
        return (self.radius * self.radius * self.PI)
    }
    
    init(mass: Float32 = 1, radius: Float32 = 1, dragC: Float32 = 0.1){
        self.theta = 0
        self.phi = 0
        self.mass = mass
        self.radius = radius
        self.dragC = dragC
    }
    
    class func New() -> RMSPhysicsBody{
        return RMSPhysicsBody()
    }
    class func New(mass: Float32 = 1, radius: Float32 = 1, dragC: Float32 = 0.1) -> RMSPhysicsBody {
        return RMSPhysicsBody(mass: mass, radius: radius, dragC: dragC)
    }
}