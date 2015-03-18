//
//  RMSPhysicsBody.swift
//  RattleGL
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import SceneKit

@objc public class RMSPhysicsBody {
    
    private let PI: Float = 3.14159265358979323846
    var position, velocity, acceleration, forces: RMXVector3
    var orientation: RMXMatrix4
    var vMatrix: RMXMatrix4
    var parent: RMSParticle! = nil
    
    var theta, phi, radius, mass, dragC: Float
    var dragArea: Float {
        return ( self.radius * self.radius * self.PI )
    }
    
    init(parent: RMSParticle, mass: Float = 1, radius: Float = 1, dragC: Float = 0.1){
        self.theta = 0
        self.phi = 0
        self.mass = mass
        self.radius = radius
        self.dragC = dragC
        self.position = GLKVector3Make(0,0,0)
        self.velocity = GLKVector3Make(0,0,0)
        self.acceleration = GLKVector3Make(0,0,0)
        self.forces = GLKVector3Make(0,0,0)
        self.orientation = SCNMatrix4Identity
        self.vMatrix = SCNMatrix4MakeScale(0,0,0)
        self.parent = parent
    }
    
    class func New(parent: RMSParticle) -> RMSPhysicsBody{
        return RMSPhysicsBody(parent: parent)
    }
    class func New(parent: RMSParticle, mass: Float = 1, radius: Float = 1, dragC: Float = 0.1) -> RMSPhysicsBody {
        return RMSPhysicsBody(parent: parent, mass: mass, radius: radius, dragC: dragC)
    }
    
    var weight: Float{
        return self.mass * parent.physics!.gravity
    }
    
    func accelerateForward(v: Float) {
        RMXVector3SetZ(&self.acceleration, v * self.parent.accelerationRate)
    }
    
    func accelerateUp(v: Float) {
        RMXVector3SetY(&self.acceleration, v * self.parent.accelerationRate)
    }
    
    func accelerateLeft(v: Float) {
        RMXVector3SetX(&self.acceleration, v * self.parent.accelerationRate)
    }
    
    
    func forwardStop() {
        RMXVector3SetZ(&self.acceleration,0)
    }
    
    func upStop() {
        RMXVector3SetY(&self.acceleration,0)
    }
    
    func leftStop() {
        RMXVector3SetX(&self.acceleration,0)
    }

    var upVector: RMXVector3 {
        return GLKVector3Make(Float(self.orientation.m12),Float(self.orientation.m22),Float(self.orientation.m32))
    }
    
    var rightVector: RMXVector3 {
        return GLKVector3Make(Float(-self.orientation.m11), Float(-self.orientation.m21), Float(-self.orientation.m31))
    }
    
    var leftVector: RMXVector3 {
        return GLKVector3Make(Float(self.orientation.m11),Float(self.orientation.m21),Float(self.orientation.m31))
    }
    
    var forwardVector: RMXVector3 {
        return GLKVector3Make(Float(self.orientation.m13),Float(self.orientation.m23),Float(self.orientation.m33))
    }
    
    func distanceTo(object:RMXObject) -> Float{
        return GLKVector3Distance(self.position,object.getPosition()!)
    }
    
}