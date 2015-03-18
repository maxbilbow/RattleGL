//
//  RMXObserver.swift
//  RattleGL
//
//  Created by Max Bilbow on 13/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation


@objc public class RMXObserver : RMXParticle {
    
    
    //@property (readonly) RMXMatrix4 modelViewMatrix, projectionMatrix;
    
    override init(world: RMXWorld!, parent: RMXObject!) {
       // self.mouse = RMXMouse(name: name, parent:self, world:world)
        super.init(world: world,parent: parent)
        self.reInit()
    }
    
//    var mousePos:GLKVector2 {
//        return self.mouse.pos
//    }
    override public func reInit() {
        super.reInit()
        self.armLength = 8;
        self.reach = 10;
        self.body.mass = 9;
        self.body.radius = 10;
        self.body.position = SCNVector3Make(0,0,-0.4);
        self.body.position = SCNVector3Make(CGFloat(20.0),self.body.radius,CGFloat(20.0))
    
    //self.body.position[2] = -0.4;
    //    body.position = GLKVector3Make(-10,body.radius,-10);
    self.jumpStrength = 1;
    }
    
    private var _itemWasAnimated = false;
    private var _itemHadGravity = false;
    
    func grabObject(i: RMXParticle) {
        
        if self.item != nil {
            self.releaseObject()
        } else if self.body.distanceTo(i) < self.reach + i.body.radius + self.body.radius {
            self.item = i
            self.itemPosition = i.body.position
            _itemWasAnimated = self.item.isAnimated
            _itemHadGravity = self.item.hasGravity
            self.item.hasGravity = false
            self.item.isAnimated = true
            //[self.item setIsAnimated:false]; //TODO: Make this not necessary
            self.armLength = self.body.distanceTo(self.item)
            println(self.item.name)
        }
    }
    
    func releaseObject() {
        if self.item != nil {
            self.item.isAnimated = _itemWasAnimated
            self.item.hasGravity = _itemHadGravity
            self.item = nil
        }
    }
    
//    var ground: Float {
//        return super.ground()
//    }
    
    
    func extendArmLength(i: CGFloat)    {
        if self.armLength + i > 1 {
            self.armLength += i
        }
    }
    /*
    - (GLKMatrix4)makeLookAt:(GLKMatrix4(float eyeX,float eyeY, float eyeZ, float cx,float cy, float cz, float ux,float uy, float uz ))lookAt
    {
    return (GLKMatrix4)lookAt(
    self.eye[0],      self.eye[1],    self.eye[2],
    self.center[0],   self.center[1], self.center[2],
    self.up[0],       self.up[1],     self.up[2]
    );
    
    } */
    
    
    /*
    - (GLKMatrix4)makePerspective:(GLKMatrix4(float fovyRadians, float aspect, float nearZ, float farZ))make
    m:(float)m width:(int)width height:(int)height
    {//, Number fovyRadians, Number aspect, Number nearZ, Number farZ){
    
    return (GLKMatrix4)make(60*m ,width / height, 1.0, 1000.0);
    }
    
    */
    
    
    
    
    
    
    var viewDescription: String? {
        return self.camera?.viewDescription
    }
    
    
    func modelViewMatrix() -> RMXMatrix4 {
    
        let m = SCNMatrix4Translate(self.body.orientation, self.body.velocity.x, self.body.velocity.y, self.body.velocity.z);
    //    (
    //                                             GLKVector4MakeWithVector3(self.eye, 0),
    //                                             GLKVector4MakeWithVector3(self.center, 0),
    //                                             GLKVector4MakeWithVector3(self.up, 0),
    //                                             GLKVector4MakeWithVector3(GLKVector3Make(0,0,0), 1)
    //                                             );
        return m;
    }
    
    func projectionMatrix() -> RMXMatrix4 {
    //
    //    float aspect = fabsf(self.uiView.view.bounds.size.width / self.uiView.view.bounds.size.height);
    //    return GLKMatrix4MakePerspective(GLKMathDegreesToRadians(65.0f), aspect, 0.1f, 100.0f);
    //#else
        return SCNMatrix4Identity;
    }
    
    
    

}