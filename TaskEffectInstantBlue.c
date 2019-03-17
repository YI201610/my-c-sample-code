/*
 *  TaskEffectInstantBlue.c
 *  tech_phone
 *
 *  Created by Yuji Imamura on 11/05/01.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "TaskEffectInstantBlue.h"

#include "GI.h"

extern Texture g_font_texture;
extern TaskManager g_tm_scene;

Task* TaskEffectInstantBlue_init(TaskManager* tm, char* name, int priority, CGPoint pos) {
	_c_methodname_;
	
    /*実行関数を登録する*/
	Task* task = TaskManager_regist_task(tm, Task_new(name), 
										 TaskEffectInstantBlue_func, 
										 TaskEffectInstantBlue_move_func, 
										 TaskEffectInstantBlue_touch_first_func,
										 TaskEffectInstantBlue_touch_move_func,
										 TaskEffectInstantBlue_touch_end_func,
										 TaskEffectInstantBlue_touch_ui_func,
										 TaskEffectInstantBlue_exit, 
										 priority);
	
    /* タスクのワーキングメモリを取得 */
	// 汎用ワーキングタスクメモリを、TaskEffectInstantBlue型にキャスト
    TaskEffectInstantBlue* this = (TaskEffectInstantBlue*)task->m_data;
	//dp("sizeof class TaskEffectInstantBlue: %d", sizeof(*this));
	assert(sizeof(*this) <= TASK_WORK_SIZE);	//assert: 診断が偽の場合、プログラム中止
	
	memcpy(task->m_name, name, sizeof(task->m_name));
	
    this->m_change = tc_init;
	Vector_init0(&(this->m_v));
	this->m_color.red = 0.0f;
	this->m_color.green = 0.0f;
	this->m_color.blue = 1.0f;
	this->m_color.alpha = 1.0f;
	
	this->pos.x = pos.x;
	this->pos.y = pos.y;

    this->power = 255;
	
    return task;
}


#pragma mark -
#pragma mark Task Functions - Basic

/**
 勢い良くフェードインし、最大値までくっきりした後、静かにフェードアウトする
 */
int TaskEffectInstantBlue_func(Task* task, int ogl_version) {
    TaskEffectInstantBlue* this = (TaskEffectInstantBlue*)task->m_data;

    GI_setClearColor(0x00, 0x00, this->power);

	switch (this->m_change) {
		case tc_init:
			this->m_change = tc_fadein;
			break;

		case tc_fadein:
			{
				this->m_change = tc_stay;
			}
			break;
			
		case tc_stay:
		{
            this->m_change = tc_fadeout;
		}
			break;
			
		case tc_fadeout:
		{
			this->power -= 10;
			if(this->power <= 0){
                this->power = 0;
				this->m_change = tc_makunudu;
			}
		}
			break;
			
		case tc_makunudu:
		{
			dp("%s, makunudo...", task->m_name);
			task->m_status = TASK_KILL;	//自滅
		}
			break;
			
		default:
			break;
	}
	
	return 0;
}

/**
 */
int TaskEffectInstantBlue_move_func(Task* task, int* _key) {
    //TaskEffectInstantBlue* this = (TaskEffectInstantBlue*)task->m_data;
	
	return 0;
}

#pragma mark -
#pragma mark Task Functions - Touch

int TaskEffectInstantBlue_touch_first_func(Task* task, float _x, float _y, int _numTap){
	_c_methodname_;
	return 0;
}

int TaskEffectInstantBlue_touch_move_func(Task* task, float _x, float _y){
	_c_methodname_;	
	return 0;
}

int TaskEffectInstantBlue_touch_end_func(Task* task, float _x, float _y){
	_c_methodname_;
	return 0;
}


#pragma mark -
#pragma mark Task Functions - UIKit

int TaskEffectInstantBlue_touch_ui_func(Task* task, int ui_msg) {
	_c_methodname_;
	
	dp("***** RECV UI Message: %d", ui_msg);
	
	return 0;
}


#pragma mark -
#pragma mark Task Functions - Exit

int TaskEffectInstantBlue_exit(Task* task) {
	_c_methodname_;
	
    //TaskEffectInstantBlue* this = (TaskEffectInstantBlue*)task->m_data;
	
	return 0;
}

