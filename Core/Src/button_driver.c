/*
 * button_driver.c
 *
 *  Created on: May 17, 2025
 *      Author: tdo56
 */


#include "button_driver.h"
#include "stm32c0xx_hal.h"

typedef enum {
    IDLE,
    PRESSING,
    WAIT_DOUBLE
} State_t;

typedef struct {
    State_t       state;
    uint32_t      press_time;
    uint32_t      timer;
    buttonEvent_t event;
} ButtonCtx_t;

static ButtonCtx_t ctx[NUM_BUTTONS];

void BUTTON_init(void)
{
    buttons_init();
    for (int i = 0; i < NUM_BUTTONS; i++) {
        ctx[i].state      = IDLE;
        ctx[i].press_time = 0;
        ctx[i].timer      = 0;
        ctx[i].event      = NONE;
    }
}

void BUTTON_update_state(void)
{
    buttons_update();
    uint32_t now = HAL_GetTick();

    for (buttonName_t b = UP; b <= JOYSTICK; b++) {
        buttonState_t raw = buttons_checkButton(b);

        switch (ctx[b].state) {

            case IDLE:
                if (raw == PUSHED) {
                    //start timing
                    ctx[b].press_time = now;
                    ctx[b].state      = PRESSING;
                }
                break;

            case PRESSING:
                //held past longpress threshold
                if ((now - ctx[b].press_time) >= LONG_PRESS_TIME_MS) {
                    ctx[b].event = LONG_PRESS;
                    ctx[b].state = IDLE;
                }
                //release before threshold
                else if (raw == RELEASED) {
                    ctx[b].timer = now;  //start doubletap window
                    ctx[b].state = WAIT_DOUBLE;
                }
                break;

            case WAIT_DOUBLE:
                //second tap within window = doublepress
                if (raw == PUSHED && (now - ctx[b].timer) <= DOUBLE_PRESS_WINDOW_MS) {
                    ctx[b].event = DOUBLE_PRESS;
                    ctx[b].state = IDLE;
                }
                //window expired = single press
                else if ((now - ctx[b].timer) > DOUBLE_PRESS_WINDOW_MS) {
                    ctx[b].event = PRESSED;
                    ctx[b].state = IDLE;
                }
                break;
        }
    }
}

buttonEvent_t BUTTON_get_event(buttonName_t name)
{
    if (name < 0 || name >= NUM_BUTTONS) {
        return NONE;
    }

    buttonEvent_t ev = ctx[name].event;
    ctx[name].event = NONE;
    return ev;
}

