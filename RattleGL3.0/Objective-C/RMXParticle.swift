//
//  RMXSprite.swift
//  RattleGL
//
//  Created by Max Bilbow on 13/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation



@objc public class RMXParticle : RMXObject {
    private var ignoreNextjump: Bool = false
    
    lazy var camera: RMXCamera? = RMXCamera(parent: self)
    var physics: RMXPhysics?
    lazy var body: RMSPhysicsBody = RMSPhysicsBody(parent: self)
    var shape: RMXShape? = nil
    var anchor = RMXVector3Zero()
    var itemPosition = RMXVector3Zero()
    var rAxis = RMXVector3Zero()
    var rotation:CGFloat = 0
    var rotationCenterDistance:CGFloat = 0
    var armLength:CGFloat = 0
    var reach:CGFloat = 0
    var accelerationRate:CGFloat = 0
    var speedLimit:CGFloat = 0
    var squatLevel:CGFloat = 0
    var rotationSpeed:CGFloat = 0
    var jumpStrength: CGFloat = 0
    var item: RMXParticle! = nil
//    @property (readonly) float weight, ground;
//    @property (readonly) float upThrust, downForce;
    var limitSpeed = false
    var hasFriction = false
    var hasGravity = false
    private var prepairingToJump = false
    private var goingUp = false
    var isRotating = false
    //static var COUNT: Int = 0
    
    init(world:RMXWorld!, parent:RMXObject! = nil)
    {
        super.init(parent:parent, world:world)
        self.physics = world != nil ? world.physics : RMXPhysics(parent: self)
        //RMXParticle.COUNT++
        self.reInit()
    }
    
    public class func New(world: RMXWorld! = nil, parent: RMXObject! = nil) -> RMXParticle {
        return RMXParticle(world: world, parent: parent)
    }
    public override func reInit() {
            //super.reInit()
        
        self.body = RMSPhysicsBody(parent: self)
        self.shape = RMXShape(parent: self, world:self.world)
        self.hasGravity = true
        self.hasFriction = true
        
        self.accelerationRate = 0.4
        self.speedLimit = 1.0
        self.limitSpeed = false
        self.anchor = SCNVector3Make(0,0,0)
        
        self.rotationSpeed = -0.1
        self.jumpStrength = 1
        self.item = nil
        self.itemPosition = self.viewPoint
        self.squatLevel = 0
        self.goingUp = false
        //    if (self.body.position.y < self.ground) {
        //        self.body.position.y = self.body.radius;
        //    }
        self.isAnimated = true
        
        self.rAxis = SCNVector3Make(0,0,1)
        self.rotation = 0
        self.isRotating = false
        self.rotationCenterDistance = 0
    }
    
    var viewPoint: RMXVector3{
        return RMXVector3Add(SCNVector3Make(self.body.orientation.m11,self.body.orientation.m21,self.body.orientation.m31),
            self.body.position)
    }
    
    var ground: CGFloat {
        return self.body.radius - self.squatLevel
    }
    
    override public func getPosition() -> RMXVector3 {
        return self.body.position
    }
    
    func animate() {
        if self.isAnimated {
            self.jumpTest()
            self.accelerate()
            self.manipulate()
        }
    
    
        if self.isRotating {
            self.rotation += self.rotationSpeed/self.rotationCenterDistance
            var temp = RMXSomeCircle(Float(self.rotation), Float(self.rotationCenterDistance) * 2)
            self.body.position = SCNVector3Make(CGFloat(temp.x) - self.rotationCenterDistance,CGFloat(temp.y),0)
        }
        self.shape!.draw()
    }
    
    func jumpTest() {
        if (self.prepairingToJump || self.goingUp || self.squatLevel != 0){// || self.squatLevel > 0){
            var i: CGFloat = self.body.radius / 200
            if (self.prepairingToJump){
                self.squatLevel += i
                if (self.squatLevel >= self.ground/4-i) {
                    self.jump()
                    ignoreNextjump = true
                }
            } else if (self.squatLevel != 0 ) || ( self.goingUp ){
    //if (self.goingUp) {
                self.squatLevel -= i * 4;
                if (self.squatLevel <= 0) {
                    self.squatLevel = 0;
                    self.goingUp = false;
                    self.body.upStop()
                }
            }
        }
    }
    
    
    
    //float total, previousUV, previousLV = 0;
    
    
    func accelerate()    {
    //GLKVector3 upThrust = GLKVector3Make( 0,0,0 );
        let g = (self.hasGravity) ? self.world!.physics!.gravityFor(self) : RMXVector3Zero()
        let n = (self.hasGravity) ? self.world!.physics!.normalFor(self) : RMXVector3Zero()
        let f = self.physics!.frictionFor(self)// : GLKVector3Make(1,1,1);
        let d = self.physics!.dragFor(self)// : GLKVector3Make(1,1,1);
    
    
        //#if TARGET_OS_IPHONE
        //    self.body.velocity = GLKVector3DivideScalar(self.body.velocity, 1 );
        //#else
        self.body.velocity = RMXVector3DivideScalar(self.body.velocity, Float(1 + self.world!.µAt(self) + d.x))
        
        
        let forces = SCNVector3Make(
                            (g.x + /* d.x + f.x +*/ n.x),
                            (g.y +/* d.y + f.y +*/ n.y),//+body.acceleration.y,
                            (g.z +/* d.z + f.z +*/ n.z)
                )
        
        //    self.body.forces.x += g.x + n.x;
        //    self.body.forces.y += g.y + n.y;
        //    self.body.forces.z += g.z + n.z;
        
        
        self.body.forces = RMXVector3Add(forces,RMXMatrix4MultiplyVector3( RMXMatrix4Transpose(self.body.orientation),self.body.acceleration));
        self.body.velocity = RMXVector3Add(self.body.velocity,self.body.forces);
    
    
    
        self.world!.collisionTest(self)
        
        self.applyLimits()
        self.body.position = RMXVector3Add(self.body.position,self.body.velocity);
    
    
    /*
    if([self.name isEqual:@"Main Observer"]) {
    if (RMX_DEBUGGING) NSLog(@"\n gv %f , %f, %f\n nv %f , %f, %f\n fv %f , %f, %f\n Dv %f , %f, %f"
    ,g.x,g.y,g.z
    ,n.x,n.y,n.z
    ,f.x,f.y,f.z
    ,d.x,d.y,d.z);
    if (RMX_DEBUGGING) NSLog(@"\n FORCE: %f, %f, %f\n Accel: %f, %f, %f\n Veloc: %f, %f, %f\n Posit: %f, %f, %f",
    self.body.forces.x,self.body.forces.y,self.body.forces.z,
    self.body.acceleration.x,self.body.acceleration.y,self.body.acceleration.z,
    self.body.velocity.x, self.body.velocity.y,self.body.velocity.z,
    self.body.position.x, self.body.position.y, self.body.position.z );
    }
    */
    }
    
    
    
    private func applyLimits()
    {
    //body.acceleration.y -= [self gravity];
    //Need to calculate this
    /*
    if (self.limitSpeed){
    if (self.body.velocity.x > self.speedLimit){
    self.body.velocity.x = self.speedLimit;
    } else if (self.body.velocity.x < -self.speedLimit){
    self.body.velocity.x = -self.speedLimit;
    }
    if (self.body.velocity.y > self.speedLimit){
    self.body.velocity.y = self.speedLimit;
    } else if (self.body.velocity.y < -self.speedLimit){
    self.body.velocity.y = -self.speedLimit;
    }
    if (self.body.velocity.z > self.speedLimit){
    self.body.velocity.z = self.speedLimit;
    } else if (self.body.velocity.z < -self.speedLimit){
    self.body.velocity.z = -self.speedLimit;
    }
    } */
    }
    
    
    private func manipulate() {
        if self.item != nil {
            self.item.body.position = RMXVector3Add(self.viewPoint, RMXVector3MultiplyScalar(self.body.forwardVector, Float(self.armLength + self.item.body.radius + self.body.radius)))
        }
    }
    
    func stop() {
        self.body.velocity = SCNVector3Make(0,0,0)
    }
    
    public override func plusAngle(var x:Float, var y:Float) {
        super.plusAngle(x, y: y)
        //body.position.z += theta; return;
        let theta = CGFloat(x) * -self.rotationSpeed * PI_OVER_180
        let phi = CGFloat(y) * self.rotationSpeed * PI_OVER_180
        
        
        //let lim = CGFloat(cos(0.0))
//        if self.body.phi + phi < lim && self.body.phi + phi > -lim {
//            self.body.phi += phi
//            self.body.angles.phi = -lim;
//        }
    
        self.body.theta += theta
        
    
    
    
        self.body.orientation = SCNMatrix4Rotate(self.body.orientation, CGFloat(theta), 0, 1, 0);
        self.body.orientation = SCNMatrix4Rotate(self.body.orientation, CGFloat(phi), self.body.leftVector.x, self.body.leftVector.y, self.body.leftVector.z);
        
    }
    
    
    var isGrounded: Bool {
        return self.body.position.y <= self.body.radius
    }
    
    func push(vector: RMXVector3) {
        self.body.velocity = RMXVector3Add(self.body.velocity, vector)
    }
    
    var upThrust: CGFloat {
        return self.body.velocity.y
    }
    
    var downForce: CGFloat {
        return self.body.forces.y
    }
    func prepareToJump() {
        self.prepairingToJump = true
    }
    
    func jump() {
        if ignoreNextjump {
            ignoreNextjump = false
            self.goingUp = false
            self.prepairingToJump = false
            return
        }
        else if (self.hasGravity&&self.prepairingToJump && !self.goingUp) {
            let y = self.body.weight * self.jumpStrength * self.body.radius / self.squatLevel
            self.body.acceleration = RMXVector3Add(self.body.acceleration, SCNVector3Make(0,y,0))
            self.goingUp = true;
            self.prepairingToJump = false;
        }
        
    }
    
    func toggleGravity() {
        self.hasGravity = !self.hasGravity
    }
    
    func toggleFriction() {
        self.hasFriction = !self.hasFriction
    }
    

    
    func describePosition() -> String? {
/*    RMXVector3 drag = [self.physics dragFor:self];
    return [NSString stringWithFormat:@"\n   Pos: %f, %f, %f (%p)\n   Vel: %f, %f, %f (%p)\n   Acc: %f, %f, %f (%p)\n   µ: %f, %f, %f\n   g: %f, %f, %f\n  dF: %f, %f, %f\n  hasG: %i, hasF: %i, µ: %f", self.body.position.x,self.body.position.y,self.body.position.z,self.body,
    self.body.velocity.x,self.body.velocity.y,self.body.velocity.z,self.body
    ,self.body.acceleration.x,self.body.acceleration.y,self.body.acceleration.z,self.body,
    [self.physics frictionFor:self].x,[self.physics frictionFor:self].y,[self.physics frictionFor:self].z,
    [self.physics gravityFor:self].x,[self.physics gravityFor:self].y,[self.physics gravityFor:self].z,
    drag.x,drag.y,drag.z
    ,self.hasGravity,self.hasFriction, self.absFriction];
    
    //[rmxDebugger add:RMX_PARTICLE n:self t:[NSString stringWithFormat:@"%@",self.name]];
    //[rmxDebugger add:RMX_PARTICLE n:self.name t:[NSString stringWithFormat:@"%@ POSITION: %p | PX: %f, PY: %f, PZ: %f",self.name,[self pMem],[self position].x,[self position].y,[self position].z ]]; */
        return nil
    }
    
  /*
    func absFriction() {
    RMXVector3 µ = [self.physics frictionFor:self];
    
    return RMXGetSpeed(µ);
    }
*/
    
    var isLightSource: Bool {
        return (self.shape != nil && self.shape!.isLight)
    }

}