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
    //var uniformBuffer: MTLBuffer?
    
    init(gameView: RMXGameView) {
        self.gameView = gameView
        self.modelMatrix.translate(0.0, y: 0.0, z: -7.0)
        self.modelMatrix.rotateAroundX(Matrix4.degreesToRad(25), y: 0.0, z: 0.0)
    }
    func update(){
//self.gameView.commandQueue, pipelineState: self.gameView.pipelineState, drawable: self.gameView.metalLayer.nextDrawable(), parentModelViewMatrix: self.world.modelMatrix, projectionMatrix: self.gameView.projectionMatrix ,clearColor: nil)
        let drawable = self.gameView.metalLayer.nextDrawable()
        let renderPassDescriptor = MTLRenderPassDescriptor()
        renderPassDescriptor.colorAttachments[0].texture = drawable.texture
        renderPassDescriptor.colorAttachments[0].loadAction = .Clear
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColor(red: 0.0, green: 104.0/255.0, blue: 5.0/255.0, alpha: 1.0)
        renderPassDescriptor.colorAttachments[0].storeAction = .Store
        
        let depthTexDesc = MTLTextureDescriptor() //(MTLPixelFormat.Depth32Float, gameView.metalLayer.frame.width, gameView.metalLayer.frame.height, false)
        let depthTex = gameView.device.newTextureWithDescriptor(depthTexDesc)
        renderPassDescriptor.depthAttachment.texture = depthTex
//        renderPassDescriptor.depthAttachment.loadAction = MTLLoadActionClear
//        renderPassDescriptor.depthAttachment.storeAction = MTLStoreActionStore
        renderPassDescriptor.depthAttachment.clearDepth = 1.0

        
        
        let commandBuffer = self.gameView.commandQueue.commandBuffer()
        let renderEncoderOpt = commandBuffer.renderCommandEncoderWithDescriptor(renderPassDescriptor)
        
        
        if let renderEncoder = renderEncoderOpt {
            //For now cull mode is used instead of depth buffer
            renderEncoder.setCullMode(MTLCullMode.Front)
//            let depthStateDescriptor = MTLDepthStencilDescriptor()
//            depthStateDescriptor.depthWriteEnabled = true
//            renderEncoder.setDepthStencilState(depthStateDescriptor.)
            
            renderEncoder.setRenderPipelineState(self.gameView.pipelineState)
            var i: Int = 0
            for sprite in sprites {
                sprite.update()
                
                if sprite.isVisible {
                    renderEncoder.setVertexBuffer(sprite.vertexBuffer, offset: 0, atIndex: 0); ++i
                    
                    // 1
                    var nodeModelMatrix = sprite.modelMatrix()
                    nodeModelMatrix.multiplyLeft(self.modelMatrix)
                    // 2
                    let uniformBuffer = self.gameView.device.newBufferWithLength(sizeof(Float) * Matrix4.numberOfElements() * sprites.count, options: nil)
                    // 3
                    var bufferPointer = uniformBuffer?.contents()
                    // 4
                    memcpy(bufferPointer!, nodeModelMatrix.raw(), UInt(sizeof(Float)*Matrix4.numberOfElements()))
                    memcpy(bufferPointer! + sizeof(Float)*Matrix4.numberOfElements(), self.gameView.projectionMatrix.raw(), UInt(sizeof(Float)*Matrix4.numberOfElements()))
                    // 5
                    renderEncoder.setVertexBuffer(uniformBuffer, offset: 0, atIndex: 1)//; ++i
                    renderEncoder.drawPrimitives(.Triangle, vertexStart: 0, vertexCount: sprite.vertexCount, instanceCount: sprite.vertexCount/3)
                    
                }
            }
            
            renderEncoder.endEncoding()
            commandBuffer.presentDrawable(drawable)
            commandBuffer.commit()
            }
    }
    
    
}