//
//  RMXPhysics.swift
//  RattleGL
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//


@objc public class RMXPhysics {
    var gravity: CGFloat = 0.098
    public var parent: RMXParticle
    //public var world: RMXWorld
    var upVector: RMXVector3
    
    init(parent: RMXParticle!) {
        //super.init(name: "World Physics", parent: parent, world: world)
        if parent != nil {
            self.parent = parent
            //self.world = parent is RMXWorld ? parent as! RMXWorld : parent.world
            self.upVector = SCNVector3Make(0,1,0)
        } else {
            fatalError(__FUNCTION__)
        }
    }
    
    class func New(parent: RMXParticle) -> RMXPhysics {
        return RMXPhysics(parent: parent)
    }

    func gVector(hasGravity: Bool) -> RMXVector3 {
        return RMXVector3MultiplyScalar(self.upVector, hasGravity ? Float(-gravity) : 0 )
    }
    
    
    
    func gravityFor(sender: RMXParticle) -> RMXVector3{
        return RMXVector3MultiplyScalar(self.upVector,Float(-sender.body.weight))
    }
    
    
    
    func dragFor(sender: RMXParticle) -> RMXVector3{
        let dragC = CGFloat(sender.body.dragC)
        let rho = CGFloat(0.005 * sender.world!.massDensityAt(sender))
        let u = CGFloat(RMXGetSpeed(sender.body.velocity))
        let area = CGFloat(sender.body.dragArea)
        var v: RMXVector3 = RMXVector3Zero()
        v.x = CGFloat(0.5 * rho * u * u * dragC * area)
        return v
    }
    
    func frictionFor(sender: RMXParticle) -> RMXVector3{
        let µ = CGFloat(sender.world!.µAt(sender))
        return SCNVector3Make(µ, µ, µ);//TODO
    }
    
    func normalFor(sender: RMXParticle) -> RMXVector3 {
        let normal = sender.world!.normalForceAt(sender)
        return RMXVector3MultiplyScalar(self.upVector,Float(normal));// : GLKVector3Make(0,0,0);
    }
}