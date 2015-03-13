//
//  RMXPhysics.swift
//  RattleGL
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//


@objc public class RMXPhysics {
    var gravity: Float = 0.098
    public var parent: RMXObject!
    public var world: RMXWorld!
    var upVector: RMXVector3
    
    init(parent: RMXObject! = nil, world:RMXWorld! = nil) {
        //super.init(name: "World Physics", parent: parent, world: world)
        self.parent = parent
        self.world = world
        self.upVector = SCNVector3Make(0,1,0)
    }
    
    class func New(parent: RMXObject! = nil, world:RMXWorld! = nil) -> RMXPhysics {
        return RMXPhysics(parent: parent, world: world)
    }

    func gVector(hasGravity: Bool) -> RMXVector3 {
        return RMXVector3MultiplyScalar(self.upVector, hasGravity ? -gravity : 0 )
    }
    
    
    
    func gravityFor(sender: RMXParticle) -> RMXVector3{
        return RMXVector3MultiplyScalar(self.upVector,-sender.weight)
    }
    
    
    
    func dragFor(sender: RMXParticle) -> RMXVector3{
        let dragC = CGFloat(sender.body.dragC)
        let rho = CGFloat(0.005 * self.world.massDensityAt(sender))
        let u = CGFloat(RMXGetSpeed(sender.body.velocity))
        let area = CGFloat(sender.body.dragArea)
        var v: RMXVector3 = RMXVector3Zero()
        v.x = CGFloat(0.5 * rho * u * u * dragC * area)
        return v
    }
    
    func frictionFor(sender: RMXParticle) -> RMXVector3{
        let µ = CGFloat(self.world.µAt(sender))
        return SCNVector3Make(µ, µ, µ);//TODO
    }
    
    func normalFor(sender: RMXParticle) -> RMXVector3 {
        let normal = self.world.normalForceAt(sender)
        return RMXVector3MultiplyScalar(self.upVector,normal);// : GLKVector3Make(0,0,0);
    }
}