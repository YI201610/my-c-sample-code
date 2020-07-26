/**
 *  TaskEffectInstantRed.h
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


typedef struct TaskEffectInstantRed {
	
	int id;
	Vector pos;
	MYCOLOR m_color;
	float size;
	
	Vector m_v;
	
    int power;
	
    int m_change;
	
} TaskEffectInstantRed;


Task* TaskEffectInstantRed_init(TaskManager* tm, char* name, int priority, CGPoint pos); 

int TaskEffectInstantRed_move_func(Task* task, int* _v);
int TaskEffectInstantRed_func(Task* task, int ogl_version);

int TaskEffectInstantRed_touch_first_func(Task* task, float _x, float _y, int _numTap);
int TaskEffectInstantRed_touch_move_func(Task* task, float _x, float _y);
int TaskEffectInstantRed_touch_end_func(Task* task, float _x, float _y);

int TaskEffectInstantRed_touch_ui_func(Task* task, int _ui_pattern);

int TaskEffectInstantRed_exit(Task* task); 
