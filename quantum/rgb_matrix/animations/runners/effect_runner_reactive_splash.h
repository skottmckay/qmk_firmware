#pragma once
#define RGB_MATRIX_KEYREACTIVE_ENABLED
#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED

#include <time.h>

static const RGB daily_colors[7] = {
    {RGB_ORANGE}, // Sunday
    {0x00, 0x20, 0xFF}, // Monday
    {0x00, 0x50, 0xFF}, // Tuesday
    {0x00, 0x80, 0xFF}, // Wednesday 
    {0x00, 0xA0, 0xFF}, // Thursday 
    {0x00, 0xD0, 0xFF}, // Friday
    {RGB_ORANGE}  // Saturday
};

RGB get_todays_color(void) {
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);

    uint8_t day = tm_now->tm_wday; // Sunday = 0, Monday = 1, ..., Saturday = 6

    return daily_colors[day];
}

typedef HSV (*reactive_splash_f)(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick);

bool effect_runner_reactive_splash(uint8_t start, effect_params_t* params, reactive_splash_f effect_func) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    uint8_t count = g_last_hit_tracker.count;
    RGB default_color = get_todays_color();

    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        HSV hsv = rgb_matrix_config.hsv;  // default colors - which is black
        hsv.v   = 0;
        for (uint8_t j = start; j < count; j++) {
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            hsv           = effect_func(hsv, dx, dy, dist, tick);
        }
        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        if (rgb.r != 0 || rgb.b != 0 || rgb.g != 0) {
            rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
        } else {
            rgb_matrix_set_color(i, default_color.r, default_color.g, default_color.b);
        }
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_KEYREACTIVE_ENABLED
