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
        RMXGLProxy.initialize(RMXArt.initializeTestingEnvironment(),callbacks: RepeatedKeys)
        run(Process.argc, Process.unsafeArgv)
    }
}

start()