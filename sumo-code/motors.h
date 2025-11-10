#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

class Motors {
  private:
    uint8_t A_direction[2];
    uint8_t B_direction[2];

    uint8_t pwa;
    uint8_t pwb;
    uint8_t ain1;
    uint8_t ain2;
    uint8_t bin1;
    uint8_t bin2;

  public:
    Motors(uint8_t PWA, uint8_t PWB, uint8_t AIN1, uint8_t AIN2, uint8_t BIN1, uint8_t BIN2);

    void init();
    void config_direction(uint8_t A, uint8_t B);

    void set_pwa(uint16_t vel);
    void set_pwb(uint16_t vel);

    void forward();
    void backward();
    void A_forward();
    void B_forward();
    void A_backward();
    void B_backward();
    void A_stop();
    void B_stop();
    void stop();
};


#endif