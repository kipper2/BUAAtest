/**
 ******************************************************************************
 * @file    PID.h
 * @author  Maxsh
 * @date    2021.07.14
 * @brief   PID算法面向对象风格的C语言实现
 ******************************************************************************
 * @attent  请大家完善函数内的内容
 * @myNote
 ******************************************************************************
 */
#ifndef PID_H
#define PID_H

typedef struct _PID_t
{
  float KP;
  float KI;
  float KD;

  float TargetValue;    // 目标值
  float CurrentValue;   // 当前值
  float Error;          // 误差
  float LastError;      // 上次误差
  float PValue;         // 比例计算结果
  float IValue;         // 积分计算结果
  float DValue;         // 微分计算结果
  float integral_limit; // 抗积分饱和限制也就是积分上限

  float max_output; // 输出上限
  float output;     // 输出值

  void (*f_Calculate)(
      struct _PID_t *pid,
      float current_value,
      float target_value);
} PID_t;

void PID_StructInit(PID_t *pid, float p, float i, float d, float integral_limit, float max_output);

#endif
