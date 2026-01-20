/*Mia Vatanapradit 1/19/2026
This code turns on an LED every other time a button is pressed. \
 LED is configured as an output connected to GPIO pin 10 and the \
 button is configured as an input connected to GPIO pin 4 with an \
 internal pull-up resistor.*/

#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"


#define LED_PIN GPIO_NUM_10 // Choose your LED pin
#define BUTTON_PIN GPIO_NUM_4 // Choose your button pin


void app_main(void) {


   // TO-DO: Configure LED output
   gpio_reset_pin(LED_PIN);
   gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
   gpio_pullup_dis(LED_PIN);
   gpio_pulldown_dis(LED_PIN);
   gpio_intr_disable(LED_PIN);


   // TO-DO: Configure Button input
   gpio_reset_pin(BUTTON_PIN);
   gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
   gpio_pullup_en(BUTTON_PIN);
   gpio_pulldown_dis(BUTTON_PIN);
   gpio_intr_disable(BUTTON_PIN);


   bool every_other_press = false;
   bool led_state = false;


   while (1) {
   // TO-DO: Implement LED toggle and button logic here
       if (gpio_get_level(BUTTON_PIN) == 0) {   // button pressed
           vTaskDelay(25 /portTICK_PERIOD_MS); // debounce


           if (gpio_get_level(BUTTON_PIN) == 0) {
               every_other_press = !every_other_press;


               if (every_other_press) {
                   led_state = !led_state;
                   gpio_set_level(LED_PIN, led_state);
               }


               while (gpio_get_level(BUTTON_PIN) == 0) {
                   vTaskDelay(25 /portTICK_PERIOD_MS);
               }
           }
       }


       vTaskDelay(25 /portTICK_PERIOD_MS);
   }
}