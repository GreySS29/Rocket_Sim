#pragma once

#include <Arduino.h>


constexpr uint8_t ENCODER_CLK = D5;
constexpr uint8_t ENCODER_DT  = D6;
constexpr uint8_t BTN_1       = D3;
constexpr uint8_t BTN_2       = D4;

constexpr unsigned long SEND_INTERVAL = 50;

void initDisplay();
void updateAngleDisplay(int angle);
void showButtonMessage(const char* msg);

void sendTelemetry(int angle, int btn1, int btn2);