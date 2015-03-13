//
//  main.swift
//  RattleGLS
//
//  Created by Max Bilbow on 11/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation
let rmxDebugger = RMXDebugger()

@objc public class world {
    static let thisWorld: RMXWorld = RMXArt.initializeTestingEnvironment()
    static var observer: RMXObserver {
        return thisWorld.observer
    }
}

println("Hello, World!")

func start() {
    // var argc: Int32 = C_ARGC
    // var argv: UnsafeMutablePointer<UnsafePointer<Int8>> = UnsafeMutablePointer<UnsafePointer<Int8>>(C_ARGV)
    
    autoreleasepool {
       // rmxDebugger = RMXDebugger()
       // world = RMXArt.initializeTestingEnvironment()
        //art = RMXArt(name: "Art", parent:world, world:world)
       // observer = world.observer
        //observer.physicsBody.mass = 90
        
        //window = RMXWindow(name:"RMX Window", parent:world, world:world)
        
        run(Process.argc, Process.unsafeArgv)
    }
}

start()