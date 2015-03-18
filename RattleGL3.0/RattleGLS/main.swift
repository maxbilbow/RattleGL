//
//  main.swift
//  RattleGLS
//
//  Created by Max Bilbow on 11/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation
let rmxDebugger = RMXDebugger()

//@objc public class world {
//    static let thisWorld: RMXWorld = RMXArt.initializeTestingEnvironment()
//    static var observer: RMXParticle {
//        return thisWorld.observer!
//    }
//}

println("Hello, World!")


func start() {

    
    autoreleasepool {
        let scene = RMXArt.initializeTestingEnvironment()
        for sprite in scene.sprites {
            if sprite.rmxID != scene.observer?.rmxID && sprite.isAnimated {
                sprite.addBehaviour({
                    if sprite.body.distanceTo(scene.observer!) < 50 {
                        sprite.actions?.prepareToJump()
                    }
                })
            }
        }
        RMXGLProxy.initialize(scene,callbacks: RepeatedKeys)
        run(Process.argc, Process.unsafeArgv)
    
        
    }
}

start()