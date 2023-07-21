/**
 ******************************************************************************
 * @file
 * @author  xtc
 * @date    2023.06.21
 * @brief
 ******************************************************************************
 * @attent  请大家完善函数内的内容
 * @myNote
 ******************************************************************************
 */
#include <stdint.h>
#include <stdarg.h>

float ReturnNum1;
int ReturnNum2;

uint8_t send_frame[10];

/** @brief  发送简单帧
  * @param  引入stdarg.h，解决可变参数问题，...作为占位符
            id : 变量编号
            target_value : 需要修改为的值
  * @example SendSimpleFrame(2, 123);
             SendSimpleFrame(1, 3.14);
*/
void SendSimpleFrame(uint8_t id, ...)
{
  
  send_frame[0] = 0x7E;
  send_frame[1] = 0x00;
  send_frame[2] = 0x05;
  send_frame[9] = 0x30;

  if(id == 0x01){
     uint8_t Farray[4];
     va_list p_args;
     va_start(p_args, id);

     (float *)Farray = va_arg(p_args, float);
     
     send_frame[3] = id
     send_frame[4] = Farray[0];
     send_frame[5] = Farray[1];
     send_frame[6] = Farray[2];
     send_frame[7] = Farray[3];
     send_frame[8] = send_frame[1] + send_frame[2] +send_frame[3];
  }
  else if(id == 0x02){
     int integer;
     va_list p_args;
     va_start(p_args, id);
     *integer = va_arg(p_args,int);
     send_frame[3] = id;
     send_frame[4] =  integer & 0xFFFF;
     send_frame[5] = (integer & 0xFFFF)>>4;
     send_frame[6] = (integer & 0xFFFF)>>8;
     send_frame[7] = (integer & 0xFFFF)>>12;
     send_frame[8] = send_frame[1] + send_frame[2] +send_frame[3];
  }

  // 最后是底层发送函数，假设已经实现
}

/** @brief  接收处理简单帧
  * @param
            recv_frame : 接收帧存放的数组指针
            len : 帧长
*/
void SimpleFrameHandler(uint8_t *recv_frame, uint16_t len)
{
  
  int length = 0;
  int i = 0;
  while((recv_frame[i] != 0x7E)||(i <= 4*len)){i++;}

  if((recv_frame[i] == 0x7E)&&(recv_frame[i + len] == 0x30)&&((recv_frame[i+1]+recv_frame[i+2]+recv_frame[i+3]) == recv_frame[i+8])){
     
     if(recv_frame[3] == 0x01){
        uint8_t Farray[4];
        float Fnum;
        Farray[0] = recv_frame[i+4];
        Farray[1] = recv_frame[i+5];
        Farray[2] = recv_frame[i+6];
        Farray[3] = recv_frame[i+7];
        memcpy(&Fnum, Farray, 4);
        ReturnNum1 = Fnum;
     }
     else if(recv_frame[3] == 0x02){
      int high, mediumhigh, mediumlow, low;
      low = recv_frame[i+4];
      mediumlow = recv_frame[i+5]<<4;
      mediumhigh = recv_frame[i+6]<<8;
      high = recv_frame[i+7]<<12;
      ReturnNum2 = low + mediumlow + mediumhigh + high;
     }
  }
}