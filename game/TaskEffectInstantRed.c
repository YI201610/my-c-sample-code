/*
 *  TaskEffectInstantRed.c
 *  tech_phone
 *
 *  Created by Yuji Imamura on 11/05/01.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "TaskEffectInstantRed.h"

#include "GI.h"

extern Texture g_font_texture;
extern TaskManager g_tm_scene;

Task* TaskEffectInstantRed_init(TaskManager* tm, char* name, int priority, CGPoint pos) {
	_c_methodname_;
	
    /*実行関数を登録する*/
	Task* task = TaskManager_regist_task(tm, Task_new(name), 
										 TaskEffectInstantRed_func, 
										 TaskEffectInstantRed_move_func, 
										 TaskEffectInstantRed_touch_first_func,
										 TaskEffectInstantRed_touch_move_func,
										 TaskEffectInstantRed_touch_end_func,
										 TaskEffectInstantRed_touch_ui_func,
										 TaskEffectInstantRed_exit, 
										 priority);
	
    /* タスクのワーキングメモリを取得 */
	// 汎用ワーキングタスクメモリを、TaskEffectInstantRed型にキャスト
    TaskEffectInstantRed* this = (TaskEffectInstantRed*)task->m_data;
	//dp("sizeof class TaskEffectInstantRed: %d", sizeof(*this));
	assert(sizeof(*this) <= TASK_WORK_SIZE);	//assert: 診断が偽の場合、プログラム中止
	
	memcpy(task->m_name, name, sizeof(task->m_name));
	
    this->m_change = tc_init;
	Vector_init0(&(this->m_v));
	this->m_color.red = 1.0f;
	this->m_color.green = 1.0f;
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
int TaskEffectInstantRed_func(Task* task, int ogl_version) {
    TaskEffectInstantRed* this = (TaskEffectInstantRed*)task->m_data;

    GI_setClearColor(this->power, 0x00, 0x00);

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
int TaskEffectInstantRed_move_func(Task* task, int* _key) {
    //TaskEffectInstantRed* this = (TaskEffectInstantRed*)task->m_data;
	
	return 0;
}

#pragma mark -
#pragma mark Task Functions - Touch

int TaskEffectInstantRed_touch_first_func(Task* task, float _x, float _y, int _numTap){
	_c_methodname_;
	return 0;
}

int TaskEffectInstantRed_touch_move_func(Task* task, float _x, float _y){
	_c_methodname_;	
	return 0;
}

int TaskEffectInstantRed_touch_end_func(Task* task, float _x, float _y){
	_c_methodname_;
	return 0;
}


#pragma mark -
#pragma mark Task Functions - UIKit

int TaskEffectInstantRed_touch_ui_func(Task* task, int ui_msg) {
	_c_methodname_;
	
	dp("***** RECV UI Message: %d", ui_msg);
	
	return 0;
}


#pragma mark -
#pragma mark Task Functions - Exit

int TaskEffectInstantRed_exit(Task* task) {
	_c_methodname_;
	
    //TaskEffectInstantRed* this = (TaskEffectInstantRed*)task->m_data;
	
	return 0;
}

