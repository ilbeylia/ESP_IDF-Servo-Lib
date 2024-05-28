#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include "Esp_servo.h"


#define SERVO_GPIO 19
#define SERVO_MIN_PULSEWIDTH 500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH 2500 // Maximum pulse width in microsecond
#define SERVO_MAX_DEGREE 180  



ledc_timer_config_t Timer_1;
ledc_channel_config_t ledc_channel;   

void app_main() {


    pwm_timer_init(&Timer_1, LEDC_HIGH_SPEED_MODE, LEDC_TIMER_10_BIT, LEDC_TIMER_1, 50, LEDC_AUTO_CLK);

    pwm_channel_init(&ledc_channel, SERVO_GPIO, LEDC_CHANNEL_0, LEDC_INTR_DISABLE, LEDC_TIMER_1, 0, 0);

    Servo_conf_S Servo1;  
    Servo1.Angle = 180;
    Servo_init(&Servo1, &Timer_1, LEDC_CHANNEL_0, SERVO_GPIO, SERVO_MIN_PULSEWIDTH, SERVO_MAX_PULSEWIDTH, SERVO_MAX_DEGREE );
    
    xTaskCreate(Servo_Task,"Servo task", 2048, &Servo1,1, NULL);

    vTaskDelay(1000/ portTICK_PERIOD_MS);
}
