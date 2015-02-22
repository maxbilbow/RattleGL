//
//  GameViewController.h
//  Lets Make a GLES game
//
//  Created by Max Bilbow on 22/02/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

//#import <GLKit/GLKit.h>
#import "oHeader.h"
//#import "RMXViewController.h"

@interface GameViewController : GLKViewController <RMXObject> {
    @public RMXPhysicsBody body;
}


- (void)handleSingleTap:(UITapGestureRecognizer *)recognizer;
//- (void)handlePan:(UIPanGestureRecognizer *)recognize;
//- (void)handleSwipe:(UISwipeGestureRecognizer *)recognizer;
//- (void)handleLongPress:(UILongPressGestureRecognizer*)recogniser;
- (void)handlePanRightSide:(UIPanGestureRecognizer *)recognizer;
- (void)handlePanLeftSide:(UIPanGestureRecognizer *)recognizer;


@end

