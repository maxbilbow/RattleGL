//
//  GameViewController.swift
//  Metal 3.0
//
//  Created by Max Bilbow on 25/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

import UIKit
import Metal
import QuartzCore

let MaxBuffers = 3
let ConstantBufferSize = 1024*1024
//
//let vertexData:[Float] =
//[
//    -1.0, -1.0, 0.0, 1.0,
//    -1.0,  1.0, 0.0, 1.0,
//    1.0, -1.0, 0.0, 1.0,
//    
//    1.0, -1.0, 0.0, 1.0,
//    -1.0,  1.0, 0.0, 1.0,
//    1.0,  1.0, 0.0, 1.0,
//    
//    -0.0, 0.25, 0.0, 1.0,
//    -0.25, -0.25, 0.0, 1.0,
//    0.25, -0.25, 0.0, 1.0,
//    
//]
//
//let vertexColorData:[Float] =
//[
//    0.0, 0.0, 1.0, 1.0,
//    0.0, 0.0, 1.0, 1.0,
//    0.0, 0.0, 1.0, 1.0,
//    
//    0.0, 0.0, 1.0, 1.0,
//    0.0, 0.0, 1.0, 1.0,
//    0.0, 0.0, 1.0, 1.0,
//    
//    0.0, 0.0, 1.0, 1.0,
//    0.0, 1.0, 0.0, 1.0,
//    1.0, 0.0, 0.0, 1.0
//]

class GameViewController: UIViewController , RMXGameView {
    var world: RMXWorld!// = nil// = RMXWorld(gameView: self)
    var dPad: RMXDPad!
    var device: MTLDevice! = nil
    var metalLayer: CAMetalLayer! = nil
    var objectToDraw: Cube!
    var pipelineState: MTLRenderPipelineState! = nil
    var commandQueue: MTLCommandQueue! = nil
    var timer: CADisplayLink! = nil
    var projectionMatrix: Matrix4!
    var lastFrameTimestamp: CFTimeInterval = 0.0
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        projectionMatrix = Matrix4.makePerspectiveViewAngle(Matrix4.degreesToRad(85.0), aspectRatio: Float(self.view.bounds.size.width / self.view.bounds.size.height), nearZ: 0.01, farZ: 100.0)
        
        device = MTLCreateSystemDefaultDevice()
        metalLayer = CAMetalLayer()          // 1
        metalLayer.device = device           // 2
        metalLayer.pixelFormat = .BGRA8Unorm // 3
        metalLayer.framebufferOnly = true    // 4
        metalLayer.frame = view.layer.frame  // 5
        view.layer.addSublayer(metalLayer)   // 6
        
        self.world = RMXWorld(gameView: self)
        self.dPad = RMXDPad(gameView: self)
        self.objectToDraw = Cube(gameView: self)
        
        commandQueue = device.newCommandQueue()
        
        // 1
        let defaultLibrary = device.newDefaultLibrary()
        let fragmentProgram = defaultLibrary!.newFunctionWithName("basic_fragment")
        let vertexProgram = defaultLibrary!.newFunctionWithName("basic_vertex")
        
        // 2
        let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
        pipelineStateDescriptor.vertexFunction = vertexProgram
        pipelineStateDescriptor.fragmentFunction = fragmentProgram
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = .BGRA8Unorm
        
        // 3
        var pipelineError : NSError?
        pipelineState = device.newRenderPipelineStateWithDescriptor(pipelineStateDescriptor, error: &pipelineError)
        if pipelineState == nil {
            println("Failed to create pipeline state, error \(pipelineError)")
        }
        
        timer = CADisplayLink(target: self, selector: Selector("newFrame:"))
        timer.addToRunLoop(NSRunLoop.mainRunLoop(), forMode: NSDefaultRunLoopMode)
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func render() {
        self.dPad.update()
        self.world.update()
        var drawable = metalLayer.nextDrawable()
        
//        var worldModelMatrix = Matrix4()
//        worldModelMatrix.translate(0.0, y: 0.0, z: -7.0)
//        worldModelMatrix.rotateAroundX(Matrix4.degreesToRad(25), y: 0.0, z: 0.0)
        
        objectToDraw.render(commandQueue, pipelineState: pipelineState, drawable: drawable, parentModelViewMatrix: world.modelMatrix, projectionMatrix: projectionMatrix ,clearColor: nil)
    }
    
    // 1
    func newFrame(displayLink: CADisplayLink){
        
        if lastFrameTimestamp == 0.0
        {
            lastFrameTimestamp = displayLink.timestamp
        }
        
        // 2
        var elapsed:CFTimeInterval = displayLink.timestamp - lastFrameTimestamp
        lastFrameTimestamp = displayLink.timestamp
        
        // 3
        gameloop(timeSinceLastUpdate: elapsed)
    }
    
    func gameloop(#timeSinceLastUpdate: CFTimeInterval) {
        
        // 4
        objectToDraw.updateWithDelta(timeSinceLastUpdate)
        
        // 5
        autoreleasepool {
            self.render()
        }
    }

    
}