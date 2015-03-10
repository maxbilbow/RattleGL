//
//  RMXDisplayProcessor.h
//  RattleGL3.0
//
//  Created by Max Bilbow on 09/03/2015.
//  Copyright (c) 2015 Rattle Media. All rights reserved.
//

#ifndef RattleGL3_0_RMXDisplayProcessor_h
#define RattleGL3_0_RMXDisplayProcessor_h


#endif






float _dt;


// Position of light
#ifdef _WIN32
static DWORD last_idle_time;
#else
static struct timeval last_idle_time;
#endif

void animate(void);

void AnimateScene(void);
void reshape (int width, int height);

void debug();
void display (void);