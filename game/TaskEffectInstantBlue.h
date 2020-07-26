/**
 *  TaskEffectInstantBlue.h
 *  tech_phone
 *
 *  Created by Yuji Imamura on 11/05/01.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Model.h"	
#include "TaskManager.h"
#include "Texture.h"
#include "Math.h"


typedef struct TaskEffectInstantBlue {
	
	int id;
	Vector pos;
	MYCOLOR m_color;
	float size;
	
    int power;
	Vector m_v;
	
	int m_change;
	
} TaskEffectInstantBlue;


Task* TaskEffectInstantBlue_init(TaskManager* tm, char* name, int priority, CGPoint pos); 

int TaskEffectInstantBlue_move_func(Task* task, int* _v);
int TaskEffectInstantBlue_func(Task* task, int ogl_version);

int TaskEffectInstantBlue_touch_first_func(Task* task, float _x, float _y, int _numTap);
int TaskEffectInstantBlue_touch_move_func(Task* task, float _x, float _y);
int TaskEffectInstantBlue_touch_end_func(Task* task, float _x, float _y);

int TaskEffectInstantBlue_touch_ui_func(Task* task, int _ui_pattern);

int TaskEffectInstantBlue_exit(Task* task); 
