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
    var parent: RMXParticle
    
    var theta, phi, radius, mass, dragC: CGFloat
    var dragArea: CGFloat {
        return ( self.radius * self.radius * self.PI )
    }
    
    init(parent: RMXParticle, mass: Float = 1, radius: Float = 1, dragC: Float = 0.1){
        self.theta = 0
        self.phi = 0
        self.mass = CGFloat(mass)
        self.radius = CGFloat(radius)
        self.dragC = CGFloat(dragC)
        self.position = SCNVector3Make(0,0,0)
        self.velocity = SCNVector3Make(0,0,0)
        self.acceleration = SCNVector3Make(0,0,0)
        self.forces = SCNVector3Make(0,0,0)
        self.orientation = SCNMatrix4Identity
        self.vMatrix = SCNMatrix4MakeScale(0,0,0)
        self.parent = parent
    }
    
    class func New(parent: RMXParticle) -> RMSPhysicsBody{
        return RMSPhysicsBody(parent: parent)
    }
    class func New(parent: RMXParticle, mass: Float = 1, radius: Float = 1, dragC: Float = 0.1) -> RMSPhysicsBody {
        return RMSPhysicsBody(parent: parent, mass: mass, radius: radius, dragC: dragC)
    }
    
    var weight: CGFloat{
        return self.mass * parent.physics.gravity
    }
    
    func accelerateForward(v: Float) {
        self.acceleration.z = CGFloat(v) * parent.accelerationRate
    }
    
    func accelerateUp(v: Float) {
        self.acceleration.y = CGFloat(v) * parent.accelerationRate
    }
    
    func accelerateLeft(v: Float) {
        self.acceleration.x = CGFloat(v) * parent.accelerationRate
    }
    
    
    func forwardStop() {
        self.acceleration.z = 0
    }
    
    func upStop() {
        self.acceleration.y = 0
    }
    
    func leftStop() {
        self.acceleration.x = 0
    }

    var upVector: RMXVector3 {
        return SCNVector3Make(self.orientation.m12,self.orientation.m22,self.orientation.m32)
    }
    
    var rightVector: RMXVector3 {
        return SCNVector3Make(-self.orientation.m11, -self.orientation.m21, -self.orientation.m31)
    }
    
    var leftVector: RMXVector3 {
        return SCNVector3Make(self.orientation.m11,self.orientation.m21,self.orientation.m31)
    }
    
    var forwardVector: RMXVector3 {
        return SCNVector3Make(self.orientation.m13,self.orientation.m23,self.orientation.m33)
    }
    
    func distanceTo(object:RMXObject) -> CGFloat{
        return CGFloat(GLKVector3Distance(SCNVector3ToGLKVector3(self.position),SCNVector3ToGLKVector3(object.body.position)))
    }
    
}