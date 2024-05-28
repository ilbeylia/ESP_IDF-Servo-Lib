/* 
 Esp_servo.h
 @brif Servo motor driving 
    It is necessary to configure the angle input section. I am using the angle 
    value in a different way, but to avoid confusion, I am sharing it this way. 
    Please adjust it accordingly.

    Created on: May 25, 2024
    Author: ILBEYLI 
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "driver/ledc.h"


typedef struct{
    gpio_num_t Servo_Gpio_Num;
    uint16_t Servo_Min_Pulse_Width;
    uint16_t Servo_Max_Pulse_Width;
    uint8_t Servo_Max_Degree;

    ledc_timer_config_t timer_conf;
    ledc_channel_t channel;

    uint16_t Angle;;
}Servo_conf_S;




uint16_t map(uint8_t value, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max );

void pwm_timer_init(ledc_timer_config_t *timer_conf, ledc_mode_t speed_mode, ledc_timer_bit_t duty_resolution, ledc_timer_t timer_num, uint32_t freq_hz, ledc_clk_cfg_t clk_conf);

void pwm_channel_init(ledc_channel_config_t * channel_conf, gpio_num_t gpio_num, ledc_channel_t channel, ledc_intr_type_t intr_type, ledc_timer_t timer_sel, uint32_t duty, int hpoint);

void Servo_init(Servo_conf_S *Servo_conf, ledc_timer_config_t *timer_conf, ledc_channel_t channel_conf, gpio_num_t Servo_Gpio_Num, uint16_t Servo_Min_Pulse_Width, uint16_t Servo_Max_Pulse_Width, uint8_t Servo_Max_Degree );

void Servo_Task(void *pvParameters);
