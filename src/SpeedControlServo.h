#ifndef SERVO_SPEED_H
#define SERVO_SPEED_H

#include <Arduino.h>

class SpeedControlServo {
public:
  SpeedControlServo();
  ~SpeedControlServo();
  void attach(pin_size_t pin, int min, int max, int value);
  void attach(pin_size_t pin, int min, int max);
  void attach(pin_size_t pin);
  void write(int time_ms, int angle);
  void loop();

  pin_size_t m_pin;
  int m_min_us;
  int m_max_us;
  int m_value_us;
  int m_move_time_ms;
  int m_move_angle;
  bool m_dir;
  int m_target_angle;
  int m_pre_angle;
  int m_period;
  int m_pre_us;
  int m_pre_ms;
  bool m_move_flag;
  const int PERIOD_MAX = 20000;

private:
};

#endif // SERVO_SPEED_H