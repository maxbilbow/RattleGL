//
//  RMXNode.swift
//  Metal 3.0
//
//  Created by Max Bilbow on 08/03/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import Metal
import QuartzCore

class RMXNode : NSObject, RMXSprite, MTLDrawable {
    
    var name: String
    var device: MTLDevice

    
    let physicsBody: RMXPhysicsBody = RMXPhysicsBody()
    
    //var transform: CATransform3D
    var world: RMXWorld
    
//    required init(world: RMXWorld) {
//        self.world = world
//        self.transform = CATransform3DIdentity
//    }
    
    func present() {
        NSLog(__FUNCTION__)
    }
    
    func presentAtTime(presentationTime: CFTimeInterval) {
        NSLog(__FUNCTION__)
    }
    
    func update() {
        
    }

    
    init(name: String, gameView: RMXGameView){
        self.world = gameView.world
        self.name = name
        self.device = gameView.device
        
    }
    
    
    
    
    
}