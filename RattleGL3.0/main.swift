//
//  main.swift
//  RattleGL3-0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

//import Foundation



//var world = RMXArt.initializeTestingEnvironment()


func start() {
    // var argc: Int32 = C_ARGC
    // var argv: UnsafeMutablePointer<UnsafePointer<Int8>> = UnsafeMutablePointer<UnsafePointer<Int8>>(C_ARGV)
    
    autoreleasepool {
        rmxDebugger = RMXDebugger()
        world = RMXArt.initializeTestingEnvironment()
        art = RMXArt(name: "Art", parent:world, world:world)
        observer = world.observer
        //observer.physicsBody.mass = 90
        
        window = RMXWindow(name:"RMX Window", parent:world, world:world)
        
        run(C_ARGC, C_ARGV)
    }
}

start()