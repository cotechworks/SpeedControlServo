#include "SpeedControlServo.h"

SpeedControlServo::SpeedControlServo() {}

SpeedControlServo::~SpeedControlServo() {}

void SpeedControlServo::attach(pin_size_t pin, int min, int max, int value) {
  m_pin = pin;
  m_min_us = min;
  m_max_us = max;
  m_pre_us = 0;
  m_move_flag = true;
  m_target_angle = value;

  pinMode(m_pin, OUTPUT);
}

void SpeedControlServo::attach(pin_size_t pin, int min, int max) {
  attach(pin, min, max, 0);
}

void SpeedControlServo::attach(pin_size_t pin) { attach(pin, 500, 2400, 0); }

void SpeedControlServo::write(int time_ms, int angle) {
  // 移動時間を保存
  m_move_time_ms = time_ms;

  // 移動量を計算
  m_move_angle = abs(m_target_angle - angle);

  // 移動向きの判定
  if (angle - m_target_angle > 0) {
    m_dir = true;
  } else {
    m_dir = false;
  }

  // 目標位置を更新
  m_target_angle = angle;

  // 経過時間をリセット
  m_pre_ms = millis();

  // 移動フラグをセット
  m_move_flag = true;
}

void SpeedControlServo::loop() {
  int time_us = micros() - m_pre_us;
  if (time_us < 0) {
    return;
  }

  // 目標位置の更新
  int now_angle;
  if (m_move_flag) {
    // 経過時間を更新
    int time_ms = millis() - m_pre_ms;
    if (time_ms < 0) {
      return;
    }

    // 角度を更新
    int angle = map(time_ms, 0, m_move_time_ms, 0, m_move_angle);
    if (m_dir) {
      now_angle = m_pre_angle + angle;
      if (now_angle >= m_target_angle) {
        m_move_flag = false;
      }
    } else {
      now_angle = m_pre_angle - angle;
      if (now_angle <= m_target_angle) {
        m_move_flag = false;
      }
    }

    // 目標位置に到達したらリセット
    if (!m_move_flag) {
      now_angle = m_target_angle;
      m_pre_angle = m_target_angle;
    }
  } else {
    now_angle = m_target_angle;
  }

  // 角度をON時間に換算
  m_period = map(now_angle, 0, 180, m_min_us, m_max_us);

  // ON・OFF切り替え
  if (time_us < m_period) { // ON
    digitalWrite(m_pin, HIGH);
  } else if (time_us < PERIOD_MAX) { // OFF
    digitalWrite(m_pin, LOW);
  } else { // リセット
    m_pre_us = micros();
  }
}