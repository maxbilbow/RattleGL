//
//  RMXSprite.swift
//  RattleGL
//
//  Created by Max Bilbow on 13/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation


@objc public protocol RMXParticle {
    var mouse: RMXMouse? { get }
    var actions: RMXSpriteActions? { get }
    var camera: RMXCamera? { get }
    var body: RMSPhysicsBody { get }
    func toggleGravity()
}

public class RMSParticle : RMXObject, RMXParticle {
    var behaviours: [() -> ()]
    public enum RMXParticleType { case OBSERVER, SHAPE, SIMPLE_PARTICLE, WORLD }
    @objc public var mouse: RMXMouse?
    @objc public var actions: RMXSpriteActions?
    private var ignoreNextjump: Bool = false
    var type: RMXParticleType = .SIMPLE_PARTICLE
    
    @objc public var camera: RMXCamera?
    var physics: RMXPhysics? {
        return self.world?.physics
    }
    @objc lazy public var body: RMSPhysicsBody = RMSPhysicsBody(parent: self)
    var shape: RMXShape?
    var anchor = RMXVector3Zero()

    var rAxis = RMXVector3Zero()
    var rotation:Float = 0
    var rotationCenterDistance:Float = 0
    
    var accelerationRate:Float = 0

    
    var rotationSpeed:Float = 0
    var hasFriction = true
    var hasGravity = false

    var isRotating = false
    //static var COUNT: Int = 0
    
    init(world:RMXWorld?,  parent:RMXObject! = nil)
    {
        self.actions = RMXSpriteActions()
        self.behaviours = Array<() -> ()>()
        super.init(parent:parent, world:world)
        //RMSParticle.COUNT++
        self.actions!.parent = self
        self.mouse = RMXMouse(parent:self, world:self.world)
        self.body = RMSPhysicsBody(parent: self)
        self.shape = RMXShape(parent: self, world:self.world)
        self.actions = RMXSpriteActions(parent: self, world: self.world)
        self.camera = RMXCamera(world: world, pov: self)
        self.shape = RMXShape(parent: self, world: world)
        
        //Set up for basic particle
        self.resets.append({
            self.accelerationRate = 0.4
            self.anchor = GLKVector3Make(0,0,0)
            self.rotationSpeed = -0.1
            self.isAnimated = true
            self.rAxis = GLKVector3Make(0,0,1)
            self.rotation = 0
            self.isRotating = false
            self.rotationCenterDistance = 0
        })
        
        self.resets.last?()
    }
    
    private var _asObserver = false
    private var _asShape = false
    
    func setAsShape(shape render: ((Float)->Void)?) -> RMSParticle? {//, mass: Float? = nil, isAnimated: Bool? = true, hasGravity: Bool? = false) -> RMSParticle {
        if _asShape { return self }
        if render != nil { self.shape!.setRenderer(render!) }
        self.resets.append({
            //if body != nil { self.body = body! }
            self.shape?.visible = true
        })
        _asShape = true
        self.resets.last?()
        return self
    }
    
    func setAsObserver() -> RMSParticle {
        if _asObserver { return self }
        self.resets.append({
            self.actions!.armLength = self.body.radius * 2
            self.actions!.reach = 2 * self.actions!.armLength;
            self.body.mass = 9
            self.body.radius = 10
            self.body.position = GLKVector3Make(20,self.body.radius,20)
            self.hasGravity = true
           
        })
        _asObserver = true
        self.resets.last?()
        return self
    }
    
    public class func New(world: RMXWorld! = nil, parent: RMXObject! = nil) -> RMSParticle {
        return RMSParticle(world: world, parent: parent)
        
    }
    
    func addBehaviour(behaviour: () -> ()) {
        self.behaviours.append(behaviour)
        //self.behaviours.last?()
    }
   
    
    var viewPoint: RMXVector3{
        return RMXVector3Add(GLKVector3Make(Float(self.body.orientation.m11),Float(self.body.orientation.m21),Float(self.body.orientation.m31)),
            self.body.position)
    }
    
    var ground: Float {
        return self.body.radius - ( self.actions?.squatLevel ?? 0 )
    }
    
    override public func getPosition() -> RMXVector3 {
        return self.body.position
    }
    
    func animate() {
        if self.isAnimated {
            self.actions?.jumpTest()
            self.accelerate()
            self.actions?.manipulate()
            for behaviour in self.behaviours {
                behaviour()
            }
        }
    
    
        if self.isRotating {
            self.rotation += self.rotationSpeed/self.rotationCenterDistance
            var temp = RMXSomeCircle(Float(self.rotation), Float(self.rotationCenterDistance) * 2)
            self.body.position = GLKVector3Make(temp.x - self.rotationCenterDistance,temp.y,0)
        }
        self.shape?.draw()
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
        
        
        let forces = GLKVector3Make(
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
    
    }
    
    
    
    private func applyLimits()
    {
    }
    
    
    
    
    func stop() {
        self.body.velocity = RMXVector3Zero()
    }
    
    public override func plusAngle(var x:Float, var y:Float) {
        super.plusAngle(x, y: y)
        //body.position.z += theta; return;
        let theta = x * -self.rotationSpeed * PI_OVER_180
        let phi = y * self.rotationSpeed * PI_OVER_180
        
        
        //let lim = CGFloat(cos(0.0))
//        if self.body.phi + phi < lim && self.body.phi + phi > -lim {
//            self.body.phi += phi
//            self.body.angles.phi = -lim;
//        }
    
        self.body.theta += theta
        
    
    
    
        self.body.orientation = SCNMatrix4Rotate(self.body.orientation, CGFloat(theta), 0, 1, 0);
        self.body.orientation = SCNMatrix4Rotate(self.body.orientation, CGFloat(phi), CGFloat(self.body.leftVector.x), CGFloat(self.body.leftVector.y), CGFloat(self.body.leftVector.z))
        
    }
    
    
    var isGrounded: Bool {
        return self.body.position.y <= self.body.radius
    }
    
    
    
    var upThrust: Float {
        return self.body.velocity.y
    }
    
    var downForce: Float {
        return self.body.forces.y
    }
    
        
    @objc public func toggleGravity() {
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
    
    
    var isLightSource: Bool {
        return (self.shape != nil && self.shape!.isLight)
    }
    


}