//
//  RMXObject.swift
//  RattleGL3-0
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//


public class RMXObject  {
    
    init(name: NSString,  parent:RMXObject, world:RMXWorld) {
        super.init()
        self.parent = parent;
        self.world = world;
        self.name = name;
        if self is RMXWorld {
            self.physics = RMXPhysics(name: "World Physics", parent:self, world: self)
        } else {
            self.physics = (world != nil) ? world.physics : nil
        }
        self.reInit()
    }
    
    
    func reInit() {
        body = RMXPhyisicsBodyMake();
        
    }
    func debug() {
        //[rmxDebugger add:RMX_ERROR n:self t:_name];
    }
    
    func upVector() -> RMXVector3{
        let v: GLKVector4 = GLKMatrix4GetColumn(GLKMatrix4Transpose(body.orientation),1)
        return GLKVector3Make(v.x,v.y,v.z);
    }
    
    func rightVector() -> RMXVector3{
        let v: GLKVector4 = GLKMatrix4GetColumn(GLKMatrix4Transpose(body.orientation),0)
        return GLKVector3Negate(GLKVector3Make(v.x,v.y,v.z));
    }
    
    func leftVector() -> RMXVector3{
        let v: GLKVector4 = GLKMatrix4GetColumn(GLKMatrix4Transpose(body.orientation),0)
        return GLKVector3Make(v.x,v.y,v.z);
    }
    
    func forwardVector() -> RMXVector3 {
        let v: GLKVector4 = GLKMatrix4GetColumn(GLKMatrix4Transpose(body.orientation),2)
        return GLKVector3Make(v.x,v.y,v.z);
    }
}

