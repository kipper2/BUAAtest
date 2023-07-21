/**
 ******************************************************************************
 * @file    PID.c
 * @author  Maxsh
 * @date    2021.07.14
 * @brief   PID算法面向对象风格的C语言实现
 ******************************************************************************
 * @attent  请大家完善函数内的内容
 * @myNote
 ******************************************************************************
 */

#include "PID.h"

PID_t PID = {1, 0.2, 0.01, 0, 0, 0, 0, 0, 0, 0, 50000, 100, 0};

static void Calculate(PID_t *pid, float current_value, float target_value);

/** @brief  结构体格式初始化，为输入参数结构体中的函数指针变量赋值，并初始化一些属性
  * @param  pid            : 被操作的结构体，可理解为self
            p              : 给定的p
            i              : 给定的i
            d              : 给定的d
            integral_limit : 积分值上限
            max_output     : PID输出上限
*/
void PID_StructInit(PID_t *pid, float p, float i, float d, float integral_limit, float max_output)
{
  pid->KP = p;
  pid->KI = i;
  pid->KD = d;
  pid->integral_limit = integral_limit;
  pid->max_output = max_output;

  pid->f_Calculate = Calculate;
}

/** @brief  私有函数，但可以结构体内函数指针的方式被外部调用。功能为计算一帧的pid
  * @param  pid          : 被操作的结构体，可理解为self
            current_value: 该帧的当前值
            target_value : 目标值
*/
static void Calculate(PID_t *pid, float current_value, float target_value)
{
  pid->CurrentValue = current_value;
  pid->TargetValue = target_value;
  pid->PValue = pid->KP * (pid->TargetValue - pid->CurrentValue);
  pid->IValue = ((pid->KI * pid->Error) > pid->integral_limit)?pid->integral_limit:(pid->KI * pid->Error);
  pid->DValue = pid->KD * (pid->TargetValue - pid->CurrentValue - pid->LastError);
  pid->output = ((pid->DValue + pid->IValue + pid->PValue) > pid->max_output)?pid->max_output:(pid->DValue + pid->IValue + pid->PValue);
}
