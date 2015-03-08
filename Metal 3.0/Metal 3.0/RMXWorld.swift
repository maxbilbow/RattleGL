//
//  RMXWorld.swift
//  Metal 3.0
//
//  Created by Max Bilbow on 08/03/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation


class RMXWorld {
    var sprites: [RMXSprite] = []
    var gameView: RMXGameView
    var modelMatrix: Matrix4 = Matrix4()
    
    init(gameView: RMXGameView) {
        self.gameView = gameView
        self.modelMatrix.translate(0.0, y: 0.0, z: -7.0)
        self.modelMatrix.rotateAroundX(Matrix4.degreesToRad(25), y: 0.0, z: 0.0)
    }
    func update(){
        for sprite in sprites {
            sprite.update()
        }
    }
}