/**************---< TECHNO ROAD.inc >---**************/
/*                                                   */
/*   File        :coron_wait.h                       */
/*   Version     :v2.1.0                             */
/*   Date        :2010/05/18                         */
/*   Author      :Norio Sakagami                     */
/*   Description :Wait routine Library Header        */
/*                                                   */
/*    Copyright(C) TECHNOROAD.inc                    */
/*                 http://techno-road.com/           */
/*****************************************************/
#ifndef CORON_WAIT_H_
#define CORON_WAIT_H_

extern void wait_timer(u32 time_x100us);
extern void wait_timer_sec(u32 time_sec);
extern void wait_timer_msec(u32 time_msec);
extern void wait_timer_usec(u32 time_usec);
extern void wait_loop(vu32 loop);
extern void wait_init(void);
extern void SysTick_Configuration(void);
extern void Handler_SysTick(void);

extern u8 	wait_timer_flag;
extern u32 wait_timer_count;

#endif /*CORON_WAIT_H_*/
