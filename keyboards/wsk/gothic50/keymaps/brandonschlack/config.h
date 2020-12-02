#pragma once

#define USE_LEDS_FOR_LAYERS
#define STOPLIGHT_LED

#define TOP_LED    F6
#define MIDDLE_LED F5
#define BOTTOM_LED F4

// #define LED_PIN_FLIP
#ifdef LED_PIN_FLIP
    #define LED_ON(flag) !flag
#else
    #define LED_ON(flag) flag
#endif
