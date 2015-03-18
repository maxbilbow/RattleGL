//
//  RMXGLut.swift
//  RattleGL
//
//  Created by Max Bilbow on 15/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

import Foundation

public protocol RMXGLView  {
//    var effect: GLKBaseEffect? { get set }
//    var context: GLContext? { get set }
    var activeCamera: RMXCamera? { get }
    var activeSprite: RMSParticle? { get }
    func animate()
    func message(function: String, args: AnyObject?...)
}


@objc public class RMXGLProxy {
    //let world: RMXWorld? = RMXArt.initializeTestingEnvironment()
    static var callbacks: [()->Void] = Array<()->Void>()
    static var gameView: RMXGLView?
    static var effect: GLKBaseEffect? = GLKBaseEffect()
    static var itemBody: RMSPhysicsBody? {
        return self.activeSprite?.actions?.item?.body
    }
    static var activeSprite: RMXParticle? {
        return self.gameView?.activeSprite
    }
    var displayPtr: CFunctionPointer<(Void)->Void>?
    var reshapePtr: CFunctionPointer<(Int32, Int32)->Void>?
    
    class func animateScene() {
        if self.gameView != nil {
            gameView?.animate()
        } else {
            fatalError("RMXWorld is nots set")
        }
        
        DrawFog();
        
        RMXGLPostRedisplay();
    }
    class func initialize(gameView: RMXGLView, callbacks: ()->Void ...){
        self.gameView = gameView
        for function in callbacks {
            self.callbacks.append(function)
        }
    }
    
    class func message(function: String, args: AnyObject?){
        self.gameView?.message(function, args: args)
    }
    
//initializeFrom(RMXGLProxy.reshape)
        
        
    class func reshape(width: Int32, height: Int32) -> Void {
        //[window setSize:width h:height]; //glutGet(GLUT_WINDOW_WIDTH);
        // window.height = height;// glutGet(GLUT_WINDOW_HEIGHT);
        glViewport(0, 0, width, height)
        glMatrixMode(GLenum(GL_PROJECTION))
        glLoadIdentity()
        self.gameView?.activeCamera?.makePerspective(width, height: height,effect: &self.effect)
        glMatrixMode(GLenum(GL_MODELVIEW))
        
    }

    
    class func display () -> Void {
        glClear(GLenum(GL_COLOR_BUFFER_BIT) | GLenum(GL_DEPTH_BUFFER_BIT))
        //glClearColor(art.r,art.g,art.b,art.k);
        glClearColor(0.8, 0.85, 1.8, 0.0)
        //[rmxDebugger add:RMX_DISPLAY_PROCESSOR n:@"DisplayProcessor" t:[NSString stringWithFormat:@"r%f, g%f, b%f, k%f",art.r,art.g,art.b,art.k]];
        glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
        if self.gameView?.activeCamera != nil {
            self.gameView?.activeCamera?.updateView(&self.effect!)
        } else {
            fatalError("World Camera not initialised")
        }
        self.animateScene()
        for function in self.callbacks {
            function()
        }

        // Make sure changes appear onscreen
        RMXGlutSwapBuffers()
        glFlush()
        debug()
        //tester.checks[1] = observer->toString();
        //NSLog([world.observer viewDescription]);
    }
    
        

}


extension RMXGLProxy {
    
}