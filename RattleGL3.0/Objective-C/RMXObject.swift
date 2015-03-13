//
//  RMXObject.swift
//  RattleGL3-0
//
//  Created by Max Bilbow on 10/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//


@objc public class RMXObject : NSObject {
    var isAnimated: Bool = true
    var body: RMSPhysicsBody! = nil
    var name: String
    var parent: RMXObject!
    var world: RMXWorld!
   // var physics: RMXPhysics
//    @property (readonly) float altitude, positionX, positionY;
    //@property RMXPhysicsBody body;
//    @property (readonly) RMXVector3 upVector, rightVector, forwardVector, leftVector;
    
    init(name:String!, parent: RMXObject!, world: RMXWorld!){
        
        self.parent = parent
        self.world = world
        //    if (world != nil && [world isKindOfClass:[RMXWorld class]]){
        //        self.uiView = ((RMXWorld*)world).uiView;
        //    } else if (world == nil && [parent isKindOfClass:[UIVideoEditorController class]]) {
        //        self.uiView = (UIVideoEditorController*) parent;
        //    }
        self.name = name;
        //    self.physics = nil;
        //self.physics = (world != nil) ? world.physics : RMXPhysics(parent: parent, world: self as RMXWorld)
       
        self.reInit()
    }
    
    var altitude: CGFloat {
        return self.body.position.y;
    }
    /*
    - (void)setAltitude:(float)altitude {
    self.body.position.y = altitude;
    }
    */
    var positionX: CGFloat {
        return self.body.position.x
    }
    
    var positionZ: CGFloat {
        return self.body.position.z
    }
    
    func reInit() {
        self.body = RMSPhysicsBody()
    }
   
    
    var upVector: RMXVector3{
    // GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(SCNMatrix4ToGLKMatrix4(body.orientation)),1);
        return SCNVector3Make(self.body.orientation.m12,self.body.orientation.m22,self.body.orientation.m32);
    }
    
    var rightVector: RMXVector3{
    //  GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(SCNMatrix4ToGLKMatrix4(body.orientation)),0);
    return SCNVector3Make(-self.body.orientation.m11, -self.body.orientation.m21, -self.body.orientation.m31);
    }
    
    var leftVector: RMXVector3{
    //GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(SCNMatrix4ToGLKMatrix4(body.orientation)),0);
    return SCNVector3Make(self.body.orientation.m11,self.body.orientation.m21,self.body.orientation.m31);
    }
    
    var forwardVector: RMXVector3{
    //GLKVector4 v = GLKMatrix4GetColumn(GLKMatrix4Transpose(SCNMatrix4ToGLKMatrix4(body.orientation)),2);
    return SCNVector3Make(self.body.orientation.m13,self.body.orientation.m23,self.body.orientation.m33);
    }
    
    func distanceTo(object: RMXObject) -> Float {
        return GLKVector3Distance(SCNVector3ToGLKVector3(self.body.position),SCNVector3ToGLKVector3(object.body.position));
    }
    //- (void)animate{}
    
    
}

