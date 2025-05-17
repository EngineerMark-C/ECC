/*
 * kemu44.h
 *
 *  Created on: 2025��5��11��
 *      Author: Ye
 */

#ifndef CODE_KEMU444_H_
#define CODE_KEMU444_H_

void recognize_command(const char* voice_input);
void complete_command(void);
void handle_open_high_beam(void);
void delay_ms(uint16_t ms);
extern int8 completecommand_flag;
extern int8 voice_flag;
extern uint8_t timer_10ms_flag;
#endif /* CODE_KEMU444_H_ */
