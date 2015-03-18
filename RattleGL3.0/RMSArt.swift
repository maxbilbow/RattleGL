//
//  RMSArt.swift
//  RattleGL
//
//  Created by Max Bilbow on 11/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation


public class RMXArt : RMXObject {
    static let colorBronzeDiff: [Float]  = [ 0.8, 0.6, 0.0, 1.0 ]
    static let colorBronzeSpec: [Float]  = [ 1.0, 1.0, 0.4, 1.0 ]
    static let colorBlue: [Float]        = [ 0.0, 0.0, 0.1, 1.0 ]
    static let colorNone: [Float]        = [ 0.0, 0.0, 0.0, 0.0 ]
    static let colorRed: [Float]         = [ 0.1, 0.0, 0.0, 1.0 ]
    static let colorGreen: [Float]       = [ 0.0, 0.1, 0.0, 1.0 ]
    static let colorYellow: [Float]      = [ 1.0, 0.0, 0.0, 1.0 ]
    static let nillVector: [Float]       = [ 0  ,   0,  0,  0   ]
    
    
    class func initializeTestingEnvironment() -> RMXWorld {
    

        let world = RMXWorld()
        
        if (world.observer == nil ){ fatalError(__FUNCTION__) }
    
    
        let sun = RMSParticle(world: world)
        //[sun setRAxis:GLKVector3Make(0, 0, 1)];
        sun.body.radius = 100
        sun.shape!.color = GLKVector4Make(0.5,0.5,0.5,0.5)
        sun.shape!.makeAsSun(rDist: world.body.radius * 2, isRotating: true)
        sun.shape!.setRenderer(self.drawSphere)
        world.insertSprite(sun)
        
        let axisColors = [colorBlue , colorRed , colorGreen]
        
        let ZX = RMSParticle(world: world)
        ZX.shape!.setRenderer(DrawPlane)
        ZX.shape!.color = GLKVector4Make(0.8,1.2,0.8,0.5)
        ZX.isAnimated = false
        ZX.body.position = GLKVector3Make(ZX.body.position.x, 0, ZX.body.position.z)
        world.insertSprite(ZX)
        
        RMXArt.drawAxis(world)
        RMXArt.randomObjects(world)
        

        return world
        
    }
    
    class func drawSphere(radius: Float){
        RMXDrawSphere(radius)
    }
    
    class func drawAxis(world: RMXWorld) {//xCol y:(float*)yCol z:(float*)zCol{
    
    //BOOL gravity = false;
        let shapeRadius: Float = 10
        let axisLenght = world.body.radius * 2
        let shapesPerAxis: Float = axisLenght / (shapeRadius * 2)
        let step: Float = axisLenght / shapesPerAxis
        
        func drawAxis(axis: String) {
            var point =  -world.body.radius
            var color: [Float]
            switch axis {
            case "x":
                color = self.colorRed
                break
            case "y":
                color = self.colorGreen
                break
            case "z":
                color = self.colorBlue
                break
            default:
                fatalError(__FUNCTION__)
            }
            for (var i: Float = 0; i < shapesPerAxis; ++i){
                let position = GLKVector3Make(axis == "x" ? point : 0, axis == "y" ? point : 0, axis == "z" ? point : 0)
                point += step
                let object:RMSParticle = RMSParticle(world: world)
                object.addInitCall( {
                    object.hasGravity = false
                    object.body.radius = shapeRadius
                    object.body.position = position
                    object.shape!.visible = true
                    object.shape?.setRenderer(DrawCubeWithTextureCoords)
                    //object.shape?.setRenderer(DrawCubeWithTextureCoords)
                    // if y??? object.body.position = GLKVector3Make(object.body.position.x, object.body.radius, object.body.position.z)
                    //}
            
                    object.shape!.color = GLKVector4Make(color[0], color[1], color[2], color[3])
                    object.isAnimated = false
                })
                world.insertSprite(object)
            }
            
            
        }
        drawAxis("x")
        drawAxis("y")
        drawAxis("z")
    }
    
    class func randomObjects(world: RMXWorld )    {
    //int max =100, min = -100;
    //BOOL gravity = true;
        let noOfShapes: Int32 = 1980
        for(var i: Int32 = -noOfShapes / 2; i < noOfShapes / 2; ++i) {
            let points = doASum(Float(world.body.radius), i, noOfShapes )
            let X = points.x
            let Y = points.y
            let Z = points.z
        //float randPos[3] = {(rand() % (max + min))-max/2, (rand() % max), (rand() % (max + min))-max/2};
        let chance = 1;//(rand() % 6 + 1);
            var randPos: [Float] = [ X, Y, Z ]
            switch (chance) {
                case 1:
                    randPos[0] = X
                    randPos[1] = Y
                    randPos[2] = Z
                    break
                case 2:
                    randPos[0] = Z
                    randPos[1] = X
                    randPos[2] = Y
                    break
                case 3:
                    randPos[0] = Y
                    randPos[1] = Z
                    randPos[2] = X
                    break
                case 4:
                    randPos[0] = Y
                    randPos[1] = X
                    randPos[2] = Z
                    break
                case 5:
                    randPos[0] = X
                    randPos[1] = Z
                    randPos[2] = Y
                    break
                default:
                    randPos[0] = Z
                    randPos[1] = Y
                    randPos[2] = X
                    break
            
            
            }
        randPos[1] = randPos[1] + 50
        
        //gravity = !gravity;
            let object: RMSParticle = RMSParticle(world: world)
//            if(false){//(rand() % 10000) == 1) {
//                object.shape.makeAsSun(rDist: 0, isRotating:false)
//            }
        
        if(random() % 500 == 1) {
            object.shape!.setRenderer(self.drawSphere)
        } else {
            object.shape!.setRenderer(DrawCubeWithTextureCoords)
        }
        
        object.hasGravity = false //(rand()% 100) == 1
        object.body.radius = Float(random() % 3 + 2)
        object.body.position = GLKVector3Make(randPos[0], randPos[1], randPos[2])
        object.body.mass = Float(random()%15+2)/10;
        object.body.dragC = Float(random() % 99+1)/100;
        object.shape!.color = RMXRandomColor()
        world.insertSprite(object)
        
        
        }
    }
    
    
    class func randomColor() -> GLKVector4 {
    //float rCol[4];
        var rCol = GLKVector4Make(
            Float(random() % 800)/500,
            Float(random() % 800)/500,
            Float(random() % 800)/500,
        1)

    return rCol
    }

}