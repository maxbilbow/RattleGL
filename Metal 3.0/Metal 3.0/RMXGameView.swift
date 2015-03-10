//
//  RMXGameView.swift
//  Metal 3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import Foundation


protocol RMXGameView {
    var world: RMXWorld! { get }
    var dPad: RMXDPad! { get }
    var device: MTLDevice! { get }
    var metalLayer: CAMetalLayer! { get }
    var pipelineState: MTLRenderPipelineState! { get }
    var commandQueue: MTLCommandQueue! { get }
    var timer: CADisplayLink! { get }
    var projectionMatrix: Matrix4! { get }
    var lastFrameTimestamp: CFTimeInterval { get }
    // var drawable: CAMetalDrawable! { get }
    var timeSinceLastUpdate: CFTimeInterval { get }
}