#ifndef _SYSTEME_LOG_H
#define _SYSTEME_LOG_H
#include <Arduino.h>

//---------------------------------DISPLAYING FUNCTIONS--------------------------------------------
void init_log_system(int baud_rate);
//---------------------------------1.FOR CHARACTERS------------------------------------------------
void message_print(const char* message);
void message_println(const char* message);

void message_print(const String message);
void message_println(const String message);
//---------------------------------2.FOR OTHER TYPES ------------------------------------------------

void message_print(IPAddress message);
void message_println(IPAddress message);

void message_print(const int message);
void message_println(const int message);

void message_print(const double message);
void message_println(const double message);

void message_print(const float message);
void message_println(const float message);

void message_print(const bool message);
void message_println(const bool message);
#endif