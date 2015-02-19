//
//  WorldConstants.h
//  openglplus
//
//  Created by Max Bilbow on 02/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//


#define _INFINITY 99999
#define PI (3.14159265f)

#define U_DEPTH       2
#define U_HORIZONTAL  0
#define U_VERTICAL    1
#define TWIST_AXIS    1
#define NOD_AXIS      0
#define ROLL_AXIS     2
#define U_SPEED       0.05
#define PI_OVER_180 (PI / 180)

#define RMX_DEPRECATED(from, to) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##from, __MAC_##to, __IPHONE_NA, __IPHONE_NA)


@interface RMXDebugger : NSString
-(void)add:(int)index n:(id)name t:(NSString*)text;//, ...;
@end

@implementation RMXDebugger
const bool debugging = true;
const bool debugLoop = true;
const int no_checks = 11;
typedef struct _Loop {
    float loss;
    int count;
    float totalTimePassed;
    float average;
    float previousAverage;
    char diff;
    //char * log;
} Loop;

const int loopSampleSize = 100;
NSString* loopLog = @"Collecting Data";
int monitor=10;
int tog = 1;

NSString * lastCheck;
NSString * priorName;
NSString * checks[no_checks];

Loop loop;


- (instancetype)init
{
    self = [super init];
    if (self) {
        lastCheck = @"";
        for (int i=0;i<no_checks;++i)
            checks[i]=@"";
        priorName = @"";
        
        loop.loss = 0;
        loop.count = 0;
        loop.totalTimePassed = 0;
        loop.average = 0;
        loop.previousAverage = 0;
        loop.diff = '=';
        //loop.log = "Collecting Data";
    }
    return self;
}


- (bool)newLoopAverage
{
    loop.count++;
    loop.totalTimePassed += _dt;
    if (loop.count <= loopSampleSize) {
        return false;
    } else {
        loop.count = 0;
        loop.previousAverage = loop.average;
        loop.average = loop.totalTimePassed / loopSampleSize;
        loop.totalTimePassed = 0;
        const float dl = loop.average - loop.previousAverage;
        loop.loss += dl;

        if (dl == 0)
            return false;
        else if (dl > 0)
            loop.diff = '>';
        else
            loop.diff = '<';

        
        loopLog = [NSString stringWithFormat:@"Loop Time: %f, Average: %f %c %f => Loss of %f (+%f)", _dt, loop.average, loop.diff, loop.previousAverage, loop.loss, dl];
        
        return true;
    }
}

- (void)feedback
{
    if (!debugging) return;
    else if (![checks[monitor] isEqualToString:lastCheck] || [self newLoopAverage]) {
        NSLog(@"\nDEBUG #%i %@\n%@", monitor, checks[monitor],debugLoop ? loopLog : @"");
        if (debugLoop) {
            const char * c = [loopLog UTF8String];
            const long len = [loopLog length];
            printf("%c\n",c[len]);
        }
    } else {
        lastCheck = checks[monitor];
        checks[monitor] = @"";
    }
    
}

-(void)cycle:(int)dir
{
    monitor += dir;
    if(monitor>no_checks-1)
        monitor = 0;
    if(monitor<0)
        monitor = no_checks-1;
    loop.loss = 0;
}


-(void)add:(int)index n:(id)object t:(NSString*)text
{
    if (!debugging||index!=monitor) return;
    NSString * s = ![[object description] isEqualToString: priorName] ? [NSString stringWithFormat:@"\n%@:\n ",[object description]] : @"";
    priorName = [object description];
    checks[index] = [NSString stringWithFormat:@"%@ %@        %@\n",checks[index],s, text];
}

@end


static const RMXDebugger *rmxDebugger;

