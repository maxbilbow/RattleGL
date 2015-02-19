/*
 *  Rattle_GL_2_0.cp
 *  Rattle GL 2.0
 *
 *  Created by Max Bilbow on 17/02/2015.
 *  Copyright (c) 2015 Rattle Media Ltd. All rights reserved.
 *
 */

#include "Rattle_GL_2_0.h"
#include "Rattle_GL_2_0Priv.h"

CFStringRef Rattle_GL_2_0UUID(void)
{
	CRattle_GL_2_0* theObj = new CRattle_GL_2_0;
	return theObj->UUID();
}

CFStringRef CRattle_GL_2_0::UUID()
{
	return CFSTR("0001020304050607");
}
