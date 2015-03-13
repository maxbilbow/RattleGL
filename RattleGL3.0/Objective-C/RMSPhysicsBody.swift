//
//  RMSPhysicsBody.swift
//  RattleGL
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import SceneKit

@objc public class RMSPhysicsBody {
    
    private let PI: CGFloat = 3.14159265358979323846
    var position, velocity, acceleration, forces: RMXVector3
    var orientation: RMXMatrix4
    var vMatrix: RMXMatrix4
    
    var theta, phi, radius, mass, dragC: CGFloat
    var dragArea: CGFloat {
        return ( self.radius * self.radius * self.PI )
    }
    
    init(mass: CGFloat = 1, radius: CGFloat = 1, dragC: CGFloat = 0.1){
        self.theta = 0
        self.phi = 0
        self.mass = mass
        self.radius = radius
        self.dragC = dragC
        self.position = SCNVector3Make(0,0,0)
        self.velocity = SCNVector3Make(0,0,0)
        self.acceleration = SCNVector3Make(0,0,0)
        self.forces = SCNVector3Make(0,0,0)
        self.orientation = SCNMatrix4Identity
        self.vMatrix = SCNMatrix4MakeScale(0,0,0)
    }
    
    class func New() -> RMSPhysicsBody{
        return RMSPhysicsBody()
    }
    class func New(mass: Float = 1, radius: Float = 1, dragC: Float = 0.1) -> RMSPhysicsBody {
        return RMSPhysicsBody(mass: CGFloat(mass), radius: CGFloat(radius), dragC: CGFloat(dragC))
    }
}