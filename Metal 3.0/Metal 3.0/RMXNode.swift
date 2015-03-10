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
    
    var positionX:Float = 0.0
    var positionY:Float = 0.0
    var positionZ:Float = 0.0
    
    var rotationX:Float = 0.0
    var rotationY:Float = 0.0
    var rotationZ:Float = 0.0
    var scale:Float     = 1.0
    
    var name: String
    var device: MTLDevice
    var time:CFTimeInterval = 0.0
    var isVisible = false
    
    var vertexCount: Int = 0
    var vertexBuffer: MTLBuffer?
    var uniformBuffer: MTLBuffer?
    
    let physicsBody: RMXPhysicsBody = RMXPhysicsBody()
    
    //var transform: CATransform3D
    var world: RMXWorld
    var gameView: RMXGameView
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
    
    func updateWithDelta(delta: CFTimeInterval){
        time += delta
    }
    
    func update() {
        self.updateWithDelta(self.gameView.timeSinceLastUpdate)
    }

    
    init(name: String, gameView: RMXGameView){
        self.world = gameView.world
        self.name = name
        self.device = gameView.device
        self.gameView = gameView
        
        
    }
    
    func modelMatrix() -> Matrix4{
        var matrix = Matrix4()
        matrix.translate(positionX, y: positionY, z: positionZ)
        matrix.rotateAroundX(rotationX, y: rotationY, z: rotationZ)
        matrix.scale(scale, y: scale, z: scale)
        return matrix
    }
    
    
    
}