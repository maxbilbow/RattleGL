//
//  RMXPhysicsBody.swift
//  Metal 3.0
//
//  Created by Max Bilbow on 08/03/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import UIKit


struct RMXPhysicsBody {
    
    init(){
//        self.velocityMatrix = CATransform3DMakeScale(0, 0, 0)
//        self.orientationMatrix = CATransform3DMakeScale(0, 0, 0)
    }
    
    var position: [CGFloat] = [ 0, 0, 0]
    var velocity: [CGFloat] = [ 0, 0, 0]
    var acceleration: [CGFloat] = [ 0, 0, 0]
    var forces: [CGFloat] = [ 0, 0, 0]
    var rotation: [CGFloat] = [ 0, 0, 0]
    
    var modelMatrix: CATransform3D = CATransform3DMakeScale(0, 0, 0)
    var velocityMatrix: CATransform3D = CATransform3DMakeScale(0, 0, 0)
    var orientationMatrix: CATransform3D = CATransform3DMakeScale(0, 0, 0)// = CATransform3D
    var radius: CGFloat = 1
    var mass: CGFloat = 0
    
    
    var dragC: CGFloat {
        return radius * radius * 3
    }
    
    
};