//
//  RMSWorld.swift
//  RattleGL
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation


@objc public class RMXWorld : RMXObject{
//    let _g: Float = 0.01/50
//    let _f: Float = 1.1
    private let GRAVITY: Float = 9.8
    private var sprites: [RMXParticle];
    var observer: RMXObserver! = nil
//        {
//        return sprites.first as RMXObserver
//    }

    override init!(name: String!, parent: RMXObject!, world: RMXWorld!) {
        fatalError("DO not run this \(__FILE__)")
    }
    init(parent: RMXObject!, name: String = "The World", capacity: Int = 3004) {
        self.sprites = Array<RMXParticle>()
        super.init(name: name, parent: parent, world: nil)
        self.physicsBody.radius = 1000
        self.sprites.reserveCapacity(capacity)
        self.observer = RMXObserver(name: "Main Observer", parent:self, world:self)
        self.sprites.append(self.observer)
        //fatalError("Grav: \(self.physics.gravity)")
    }
    
    class func New() -> RMXWorld!{
        return RMXWorld(parent: nil)
    }
  
    func insertSprite(sprite: RMXParticle){
        self.sprites.append(sprite)
    }
            
    func µAt(someBody: RMXParticle) -> Float {
        if (someBody.altitude <= someBody.ground  ) {
            return 0.2// * RMXGetSpeed(someBody->body.velocity);//Rolling wheel resistance
        } else {
            return 0.01// * RMXGetSpeed(someBody->body.velocity); //air;
        }
    }
    func massDensityAt(someBody: RMXParticle) -> Float {
        if (someBody.altitude < someBody.ground ) {// someBody.ground )
            return 99.1 //water or other
        } else {
            return 0.01 //air;
        }
    }
    func collisionTest(sender: RMXParticle) -> Bool{
    //Have I gone through a barrier?
    if (sender.altitude < /*ground - */ sender.ground) {
        //sender->body.position.y = sender.ground;
        //sender->body.velocity.y = 0;
        return true
    } else { return false }
    
    //Then restore
    }
    
    func normalForceAt(someBody: RMXParticle) -> Float {
        var result: Float = 0
        let bounce: Float = 0.5
        if someBody.altitude <= someBody.ground - 1 {
            result = someBody.weight + (0 + abs(-someBody.altitude + someBody.ground)*bounce)
            
        } else if (someBody.altitude <= someBody.ground ){
            //if someBody.altitude < someBody.ground + 1 {
                someBody.setAltitude(someBody.ground)
            //}
            result = someBody.weight
        } else {
            result = 0//someBody.weight// * self.physics.gravity; //air;
        }
        if (someBody.altitude <= someBody.ground) && (someBody is RMXObserver) {
            println ("Normal: \(result), Weight: \(someBody.weight), Altitude: \(someBody.altitude) <= \(someBody.ground)")
        }
        return result
    }
    
    public override func debug() {
        
    }
    func animate() {
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
        var dista = sender.distanceTo(closest)
        for sprite in sprites {
            let distb = sender.distanceTo(sprite)
            //NSString *lt = @" < ";
            if(distb < dista) && (distb != 0){
                closest = sprite
                dista = distb
            }
        }
        
        NSLog("Returning:\n \(closest)")
        return closest;//shapes[closest];
    }
    
//    public func debug(){
//        rmxDebugger.add(RMX_WORLD, n:self, t:"\(self.name) debug not set up")
//        //[rmxDebugger feedback];
//        // NSLog(@"Well, hellooo!");
//    }
        
    func applyGravity(hasGrav: Bool) {
        for sprite in sprites {
            if !((sprite is RMXLightSource) && hasGrav) {
                sprite.hasGravity = hasGrav
            }
        }
    }
}