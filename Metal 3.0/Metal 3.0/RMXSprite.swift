//
//  RMXSprite.swift
//  Metal 3.0
//
//  Created by Max Bilbow on 08/03/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation
import UIKit

protocol RMXSprite {
    //var transform: CATransform3D { get set }
    var world: RMXWorld { get }
    var physicsBody: RMXPhysicsBody { get }
    var isVisible: Bool { get }
    var vertexCount: Int { get }
    var vertexBuffer: MTLBuffer? { get }
    //var uniformBuffer: MTLBuffer? { get set }
    //init(world: RMXWorld)
    func update()
    func modelMatrix() -> Matrix4
    //    func render(commandQueue: MTLCommandQueue, pipelineState: MTLRenderPipelineState, drawable: CAMetalDrawable, clearColor: MTLClearColor?)
}

