#ifndef IR_H
#define IR_H

class IR {
  private:
    const uint8_t N = 10;
    uint8_t pin;
    uint16_t white;

  public:
    bool is_calibrated = false;

    IR(const uint8_t p);
    bool value();
    uint16_t get_white();
    void set_white(int valor);
    int calibrar_color(uint16_t pin_led);
};

#endif