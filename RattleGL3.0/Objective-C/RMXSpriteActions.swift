//
//  RMXInteraction.swift
//  RattleGL
//
//  Created by Max Bilbow on 17/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation


@objc public class RMXSpriteActions : RMXObject {
    var armLength:Float = 0
    var reach:Float = 0
    var jumpStrength: Float = 1
    var squatLevel:Float = 0
    private var _prepairingToJump: Bool = false
    private var _goingUp:Bool = false
    private var _ignoreNextJump:Bool = false
    private var _itemWasAnimated:Bool = false
    private var _itemHadGravity:Bool = false
    
    var item: RMSParticle?
    var itemPosition: RMXVector3 = RMXVector3Zero()

    
    var sprite: RMSParticle {
        return self.parent as! RMSParticle
    }
    
    var body: RMSPhysicsBody {
        return self.sprite.body
    }
    
    func throwItem(strength: Float)
    {
        if self.item != nil {
            self.item!.isAnimated = true
            self.item!.hasGravity = _itemHadGravity
            self.item!.body.velocity = RMXVector3Add3(self.body.velocity,RMXVector3MultiplyScalar(self.body.forwardVector,strength),RMXVector3Zero())
            self.item = nil
        } else {
            return
        }
    }
    
    func manipulate() {
        if self.item != nil {
            self.item?.body.position = RMXVector3Add(self.sprite.viewPoint, RMXVector3MultiplyScalar(self.body.forwardVector, self.armLength + self.item!.body.radius + self.body.radius))
        }
    }
    
    private func setItem(item: RMSParticle!){
        self.item = item
        if item != nil {
            //self.sprite.itemPosition = item!.body.position
            _itemWasAnimated = item!.isAnimated
            _itemHadGravity = item!.hasGravity
            self.item!.hasGravity = false
            self.item!.isAnimated = true
            self.armLength = self.body.distanceTo(self.item!)
            if RMX.isDebugging { NSLog(item!.name) }
        }
    }
    
    
    
    public func grabItem() {
        if self.item != nil {
            self.releaseItem()
        } else {
            let item: RMSParticle? = self.parent?.world?.closestObjectTo(self.sprite)
            self.setItem(item)
        }
    }
    
    func releaseItem() {
        if self.item != nil {
            self.item!.isAnimated = true //_itemWasAnimated
            self.item!.hasGravity = _itemHadGravity
            self.setItem(nil)
        }
    }
    
    //    var ground: Float {
    //        return super.ground()
    //    }
    
    
    func extendArmLength(i: Float)    {
        if self.armLength + i > 1 {
            self.armLength += i
        }
    }
    
    func push(vector: RMXVector3) {
        self.body.velocity = RMXVector3Add(self.body.velocity, vector)
    }
    
    
    func jumpTest() {
        if (_prepairingToJump || _goingUp || self.squatLevel != 0){// || self.squatLevel > 0){
            var i: Float = self.body.radius / 200
            if (_prepairingToJump){
                self.squatLevel += i
                if (self.squatLevel >= self.sprite.ground/4-i) {
                    self.jump()
                    _ignoreNextJump = true
                }
            } else if (self.squatLevel != 0 ) || ( _goingUp ){
                //if (self.goingUp) {
                self.squatLevel -= i * 4;
                if (self.squatLevel <= 0) {
                    self.squatLevel = 0;
                    _goingUp = false;
                    self.body.upStop()
                }
            }
        }
    }
    
   
    
    func prepareToJump() {
        if !_goingUp || _ignoreNextJump {
            _prepairingToJump = true
        }
    }
    
    func jump() {
        if _ignoreNextJump {
            _ignoreNextJump = false
            _goingUp = false
            _prepairingToJump = false
            return
        }
        else if (self.sprite.hasGravity && _prepairingToJump && !_goingUp) {
            let y = self.body.weight * self.jumpStrength * self.body.radius / self.squatLevel
            self.body.acceleration = RMXVector3Add(self.body.acceleration, GLKVector3Make(0,y,0))
            _goingUp = true;
            _prepairingToJump = false;
        }
        
    }


    
}