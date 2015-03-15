//
//  RMXObject.swift
//  RattleGL3-0
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//


public class RMXObject {
    private static var COUNT: Int = 0
    var rmxID: Int
    var isAnimated: Bool = true
    var name: String
    var parent: RMXObject?
    var world: RMXWorld?
    
    init(parent: RMXObject? = nil, world: RMXWorld? = nil, name: String = __FUNCTION__){
        self.parent = parent
        self.world = world
        self.rmxID = RMXObject.COUNT
        self.name = "\(self.rmxID): \(name)";
        RMXObject.COUNT++
        self.reInit()
        
    }
    
    
    func reInit() {  }
   
   
    func plusAngle(x: Float,y:Float) {  }
    
    func debug() {}
    
    public func getPosition() -> RMXVector3? { return nil }
}

