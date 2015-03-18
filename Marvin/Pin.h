#ifndef Pin_h
#define Pin_h
enum Pin : int {
    PIN_FRONT = 4,
    PIN_RIGHT = 2,
    PIN_LEFT = 8,
    PIN_BACK = 9,
    PIN_FRONT_RIGHT = 3,
    PIN_FRONT_LEFT = 10,
    PIN_SERVO_RIGHT = 11,
    PIN_SERVO_LEFT = 12,
};
typedef enum Pin Pin;
#endif

