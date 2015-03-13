//
//  World.h
//  OpenGL 2.0
//
//  Created by Max Bilbow on 25/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//




#ifndef OpenGL_2_0_World_h
#define OpenGL_2_0_World_h


#endif

#import "RattleGLS-Bridging-Header.h"
#import <RattleGL-Swift.h>

@implementation RMXWorld
    const float _g = W_GRAVITY;
    const float _f = W_FRICTION;


- (id)initWithName:(NSString*)name  parent:(RMXObject*)parent world:(RMXWorld*)world
{
    self = [super initWithName:name parent:parent world:world];
    _observerName = @"Main Observer";
    self.physicsBody.radius = 1000;
    
    _sprites = [[NSMutableArray alloc]initWithCapacity:2500];
    [_sprites addObject:[[RMXObserver alloc]initWithName:_observerName parent:self world:self]];// inPropertyWithKey:observerName];
    //eventHandler = [[RMXEventHandler alloc]initWithName:@"Event Handler" parent:self world:self];
    
    if (self.physicsBody.radius == 0)
        exit(1);
    if ([self observer].parent.physicsBody.radius == 0)
    exit(0);
    return self;
}

- (RMXObserver*)observer {
    return [_sprites firstObject];
}






- (void)setObserverWithName:(NSString*)name {
    if ([_sprites valueForKey:name])
        _observerName = name;
    else
        NSLog(@"ERROR: Object '%@' not found in sprites array",name);
    
}

- (float)µAt:(RMXParticle*)someBody {
    if (someBody->body.position.y <= someBody.ground  )
        return 0.2;// * RMXGetSpeed(someBody->body.velocity);//Rolling wheel resistance
    else
        return 0.01;// * RMXGetSpeed(someBody->body.velocity); //air;
}
- (float)massDensityAt:(RMXParticle*)someBody{
    if (someBody->body.position.y < 0 )// someBody.ground )
        return 99.1;//water or other
    else
        return 0.01; //air;
}

- (bool)collisionTest:(RMXParticle*)sender{
    //Have I gone through a barrier?
    if (sender->body.position.y < /*ground - */ sender.ground) {
       //sender->body.position.y = sender.ground;
        //sender->body.velocity.y = 0;
        return true;
    } else return false;
    
    //Then restore
}

- (float)normalForceAt:(RMXParticle*)someBody {
    if (someBody->body.position.y < someBody.ground - 1){//someBody.physicsBody.radius/4 ){
        return someBody.physicsBody.mass * self.physics.gravity + someBody.ground - someBody->body.position.y;
    } else if (someBody->body.position.y <= someBody.ground ) {
        someBody->body.position.y = someBody.ground;
            return someBody.physicsBody.mass * self.physics.gravity;
    } else {
        return someBody.physicsBody.mass * someBody->body.acceleration.y;// * self.physics.gravity; //air;
    }
}

- (void)setObserverWithId:(RMXParticle*)object {
    _observerName = [object name];
    if (![_sprites doesContain:object])
        [self insertSprite:object];
}


- (id)objectWithName:(NSString*)name{
    return [_sprites valueForKeyPath:name];
}
    
- (void)insertSprite:(id)sprite
{
    [_sprites addObject:sprite];
//        _sprites = (RMXObserver*)shape;
}

    
- (void)animate
{
    for (RMXParticle* sprite in _sprites) {
        [sprite animate];
    }
    [self debug];
}

- (void)resetWorld{
    [self.observer reInit];//->body.position = GLKVector3Make(0,0,0);
    //self.observer->body.velocity = GLKVector3Make(0,0,0);
}
- (RMXObject*)closestObjectTo:(RMXObject*)sender
{
    id closest = [_sprites objectAtIndex:1];
    float dista = GLKVector3Distance(sender->body.position, ((RMXParticle*)[_sprites objectAtIndex:1])->body.position);
        for (RMXParticle* sprite in _sprites){
            float distb = GLKVector3Distance(sender->body.position, sprite->body.position);
            //NSString *lt = @" < ";
            if(distb<dista&&distb!=0){
                closest = sprite;
                //shapes[i];
                //lt = @" > ";
                // cout << i-1 << ": "<< dista << lt << (i) <<": "<< distb << endl;
                dista = distb;
            }
           
        }
    NSLog(@"Returning:\n %@",closest);
        //cout << "closest: "<< closest << ", dist:" << dista << endl;
    return closest;//shapes[closest];
    }
- (void)debug {
    [rmxDebugger add:RMX_WORLD n:self t:[NSString stringWithFormat:@"%@ debug not set up",self.name]];
    //[rmxDebugger feedback];
   // NSLog(@"Well, hellooo!");
}

- (void)applyGravity:(BOOL)hasGrav {
    for (RMXParticle* sprite in _sprites){
            sprite.hasGravity=hasGrav;
            //sprite.isAnimated=YES;
    }
}
@end
