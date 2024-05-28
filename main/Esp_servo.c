#include "Esp_servo.h"

static const char *Motor_TAG = "Motor_Control";

uint16_t map(uint8_t value, uint8_t in_min, uint8_t in_max, uint8_t out_min, uint8_t out_max ){
    return((((value - in_min)*(out_max-out_min))/(in_max-in_min)) + out_min);
}


void pwm_timer_init(ledc_timer_config_t *timer_conf, ledc_mode_t speed_mode, ledc_timer_bit_t duty_resolution, ledc_timer_t timer_num, uint32_t freq_hz, ledc_clk_cfg_t clk_conf) {
    timer_conf->speed_mode = speed_mode;
    timer_conf->duty_resolution = duty_resolution;
    timer_conf->timer_num = timer_num;
    timer_conf->freq_hz = freq_hz;
    timer_conf->clk_cfg = clk_conf;

    esp_err_t err = ledc_timer_config(timer_conf);
    if (err != ESP_OK) {
        ESP_LOGI(Motor_TAG, "Timer Config Error...");
    }
}

void pwm_channel_init(ledc_channel_config_t * channel_conf, gpio_num_t gpio_num, ledc_channel_t channel, ledc_intr_type_t intr_type, ledc_timer_t timer_sel, uint32_t duty, int hpoint) {
    channel_conf->gpio_num = gpio_num;
    channel_conf->channel = channel;
    channel_conf->intr_type = intr_type;
    channel_conf->timer_sel = timer_sel;
    channel_conf->duty = duty;
    channel_conf->hpoint = hpoint;
    channel_conf->speed_mode = LEDC_HIGH_SPEED_MODE;

    esp_err_t err = ledc_channel_config(channel_conf);
    if (err != ESP_OK) {
        ESP_LOGI(Motor_TAG, "Channel Config Error...");
    }
}

void Servo_init(Servo_conf_S *Servo_conf, ledc_timer_config_t *timer_conf, ledc_channel_t channel_conf, gpio_num_t Servo_Gpio_Num, uint16_t Servo_Min_Pulse_Width, uint16_t Servo_Max_Pulse_Width, uint8_t Servo_Max_Degree ){
    Servo_conf->timer_conf = *timer_conf;
    Servo_conf->channel = channel_conf;
    
    Servo_conf->Servo_Gpio_Num = Servo_Gpio_Num;
    Servo_conf->Servo_Min_Pulse_Width = Servo_Min_Pulse_Width;
    Servo_conf->Servo_Max_Pulse_Width = Servo_Max_Pulse_Width;
    Servo_conf->Servo_Max_Degree = Servo_Max_Degree;

}

void Servo_Task(void *pvParameters){
    // angle aslinda disardan gelen bir deger olucak disardan okuycaz
    Servo_conf_S * Servo = (Servo_conf_S*)pvParameters;

    uint16_t pulse_width = map(Servo->Angle, 0, Servo->Servo_Max_Degree, Servo->Servo_Min_Pulse_Width, Servo->Servo_Max_Pulse_Width);
    uint16_t duty = (pulse_width *(1024)) / 2000;

    ledc_set_duty(LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0, duty);
    ledc_update_duty (LEDC_HIGH_SPEED_MODE, LEDC_CHANNEL_0);
/*     vTaskDelay(pdMS_TO_TICKS(pulse_width)); */
    printf("duty %u \n" , duty);
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    vTaskDelete(NULL);


}