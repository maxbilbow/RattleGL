//
//  RMXPhysics.swift
//  RattleGL
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//


@objc public class RMXPhysics : NSObject, RMXObjectProtocol{
    var gravity: Float = 0.098
    var parent: RMXObjectProtocol!
    public var world: RMXWorld!
    
    init(parent: RMXObject! = nil, world:RMXWorld! = nil) {
        self.parent = parent
        self.world = world
    }
    
    
    func applyGravityTo(particle: RMXParticle) {
     // NSLog(@"Probably should delete this: (void)applyGravityTo:(RMXParticle*)particle");
        exit(0);
    }
    func gVector(hasGravity: Bool) -> RMXVector3 {
        return GLKVector3MultiplyScalar(self.upVector,(hasGravity)?-_gravity:0);
    }
    
    
    
    
    
    
    - (GLKVector3)gravityFor:(RMXParticle*)sender {
    return GLKVector3MultiplyScalar(self.upVector,-sender.weight);
    }
    
    
    
    - (GLKVector3)dragFor:(RMXParticle*)sender{
    float dragC = sender.physicsBody.dragC;
    float rho = 0.005 * [self.world massDensityAt:sender];
    float u = RMXGetSpeed(sender->body.velocity);// RMXScaler3FromMatrix3(body.vMatrix);
    float area = sender.physicsBody.dragArea;//PI * sender->body.radius * sender->body.radius;
    GLKVector3 v;
    //for (int i = 0;i<3;++i){
    v.v[0] = 0.5 * rho * u*u * dragC * area;
    // }
    
    return v;
    }
    
    - (GLKVector3)frictionFor:(RMXParticle*)sender {
    float µ = [self.world µAt:sender];
    
    
    
    return RMXMatrix3MultiplyScalarAndSpeed(sender->body.vMatrix,µ); //RMXVector3Add4(GLKVector3Make(0,0,0),µX,µY,µZ);
    }
    
    - (RMXVector3)normalFor:(RMXParticle*)sender{
    float normal = [self.world normalForceAt:sender];
    return GLKVector3MultiplyScalar(self.upVector,normal);// : GLKVector3Make(0,0,0);
    }

}