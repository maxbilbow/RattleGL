//
//  RMSWorld.swift
//  RattleGL
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation


@objc public class RMXWorld : RMXParticle {
//    let _g: Float = 0.01/50
//    let _f: Float = 1.1
    private let GRAVITY: Float = 9.8
    var sprites: [RMXParticle]
    var observer: RMXObserver! = nil
    //var camera: RMXCamera! = nil
//        {
//        return sprites.first as RMXObserver
//    }

    init(parent: RMXObject! = nil, name: String = "The World", capacity: Int = 3004) {
        self.sprites = Array<RMXParticle>()
        self.sprites.reserveCapacity(capacity)
        super.init(world: nil, parent: parent)
        self.body.radius = 1000

        self.observer = RMXObserver(world: self, parent: self)
        self.camera = self.observer.camera
        self.sprites.append(self.observer)
        //fatalError("Grav: \(self.physics.gravity)")
         self.isAnimated = false
    }
    
    class func New() -> RMXWorld!{
        return RMXWorld(parent: nil)
    }
  
    func insertSprite(sprite: RMXParticle){
        self.sprites.append(sprite)
    }
            
    func µAt(someBody: RMXParticle) -> CGFloat {
        if (someBody.body.position.y <= someBody.ground  ) {
            return 0.2// * RMXGetSpeed(someBody->body.velocity);//Rolling wheel resistance
        } else {
            return 0.01// * RMXGetSpeed(someBody->body.velocity); //air;
        }
    }
    func massDensityAt(someBody: RMXParticle) -> CGFloat {
        if (someBody.body.position.y < someBody.ground  * 8 / 10 ) {// someBody.ground )
            return 99.1 //water or other
        } else {
            return 0.01 //air;
        }
    }
    func collisionTest(sender: RMXParticle) -> Bool{
    //Have I gone through a barrier?
    if (sender.body.position.y < /*ground - */ sender.ground) {
        //sender->body.position.y = sender.ground;
        //sender->body.velocity.y = 0;
        return true
    } else { return false }
    
    //Then restore
    }
    
    func normalForceAt(someBody: RMXParticle) -> CGFloat {
        var result: CGFloat = 0
        let bounce: CGFloat = 1
        var s: String = ""
        if someBody.body.position.y < someBody.ground  * 9 / 10 {
            result = someBody.body.weight + CGFloat(abs(-someBody.body.position.y)  / someBody.ground) * bounce
            s = "\(someBody.body.position.y ) Bouncing   || "
        } else if someBody.body.position.y  <= someBody.ground  {
            s = "\(someBody.body.position.y ) == Ground  || "
            result = someBody.body.weight
            someBody.body.position.y = CGFloat(someBody.ground - someBody.upThrust)
        } else if someBody.body.position.y  > someBody.ground {
            result = 0//someBody.weight// * self.physics.gravity; //air;
            s = "\(someBody.body.position.y) IN THE AIR || "
        } else {
            s = "\(someBody.body.position.y) DEFAULT    || "
            result = someBody.body.weight
        }
//        if someBody is RMXObserver {
//            println ("\(s)Normal: \(result), Weight: \(someBody.weight), Altitude: \(someBody.altitude), upThrust: \(someBody.upThrust), Ground: \(someBody.ground), Radius: \(someBody.body.radius), dF: \(someBody.downForce)")
//        }
        return result
    }
    
   
    override func animate() {
        super.animate()
        for sprite in sprites {
            sprite.animate()
           
        }
        self.debug()
        if self.physics == nil {
            fatalError("World Physics is nil")
        }
        
    }
    
    func resetWorld() {
        self.observer.reInit()//->body.position = GLKVector3Make(0,0,0);
            //self.observer->body.velocity = GLKVector3Make(0,0,0);
    }
    
    func closestObjectTo(sender: RMXParticle)->RMXParticle {
        var closest: RMXParticle = sprites[1]
        var dista: CGFloat = sender.body.distanceTo(closest)
        for sprite in sprites {
            let distb: CGFloat = sender.body.distanceTo(sprite)
            //NSString *lt = @" < ";
            if sprite.rmxID != sender.rmxID {
                if distb < dista {
                    closest = sprite
                    dista = distb
                }
            }
        }
        
        //NSLog("Returning:\n \(closest)")
        return closest;//shapes[closest];
    }
    
  
        
    func applyGravity(hasGrav: Bool) {
        for sprite in sprites {
            if !(sprite.isLightSource && hasGrav) {
                sprite.hasGravity = hasGrav
            }
        }
    }
}