//
//  WorldConstants.h
//  openglplus
//
//  Created by Max Bilbow on 02/01/2015.
//  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
//

#define RMX_DEBUGGING           1
#define RMX_FULL_SCREEN         0

#define RMX_TOTAL_CHECKS        13
#define RMX_WORLD               12
#define RMX_WINDOW              12
#define RMX_PHYSICS             12
#define RMX_DISPLAY             11
#define RMX_ART                 10
#define RMX_SHAPE               9
#define RMX_LIGHT               8
#define RMX_PARTICLE            7
#define RMX_MOUSE_PROCESSOR     6
#define RMX_MOUSE               5
#define RMX_KEY_PROCESSOR       4
#define RMX_DISPLAY_PROCESSOR   3
#define RMX_SIMPLE_PARTICLE     2
#define RMX_OBSERVER            1
#define RMX_ERROR               0

#define U_GRAVITY               (0.0002)///50
#define U_FRICTION              1.1

#define U_DEPTH                 2
#define U_HORIZONTAL            0
#define U_VERTICAL              1
#define TWIST_AXIS              1
#define NOD_AXIS                0
#define ROLL_AXIS               2
#define U_SPEED                 0.05

#define RMX_DEPRECATED(from, to) __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_##from, __MAC_##to, __IPHONE_NA, __IPHONE_NA)



@implementation RMXDebugger
const bool isDebugging = RMX_DEBUGGING;
const bool doesDebugLoop = RMX_DEBUGGING;
const int no_checks = RMX_TOTAL_CHECKS;
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
int monitor=RMX_ERROR;
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
    if (!isDebugging) return;
    else if (![checks[monitor] isEqualToString:lastCheck] || [self newLoopAverage]) {
        NSLog(@"\nDEBUG #%i \n%@\n%@", monitor, checks[monitor],doesDebugLoop ? loopLog : @"");
        if (doesDebugLoop) {
            const char * c = [loopLog UTF8String];
            const long len = [loopLog length];
            printf("%c\n",c[len]);
        }
    }
    lastCheck = checks[monitor];
    checks[monitor] = @"";
    
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


-(void)add:(int)index n:(NSObject*)object t:(NSString*)text
{
    NSString* name = [object isKindOfClass:[RMXObject class]] ? ((RMXObject*) object).name : object.description;
    if (!isDebugging||index!=monitor) return;
    NSString * s = ![name isEqualToString: priorName] ? [NSString stringWithFormat:@"\n%@:\n ", name] : @"";
    priorName = name;
    checks[index] = [NSString stringWithFormat:@"%@ %@        %@\n",checks[index],s, text];
}

@end

    

static const RMXDebugger *rmxDebugger;

