#include "app_system_log.h"
//---------------------------------DISPLAYING FUNCTIONS--------------------------------------------
void init_log_system(int baud_rate){
     Serial.begin(baud_rate);
}
//---------------------------------1.FOR CHARACTERS------------------------------------------------
void message_print(const char* message)
{
     Serial.print(message);
}
void message_println(const char* message)
{
     Serial.println(message);
}

void message_print(const String message)
{
     Serial.print(message);
}
void message_println(const String message)
{
     Serial.println(message);
}
//---------------------------------2.FOR OTHER TYPES ------------------------------------------------

void message_print(IPAddress message)
{
     Serial.print(message);
}
void message_println(IPAddress message)
{
     Serial.println(message);
}

void message_print(const int  message)
{
     Serial.print(message);
}
void message_println(const int message)
{
     Serial.println(message);
}

void message_print(const double message)
{
     Serial.print(message);
}
void message_println(const double message)
{
     Serial.println(message);
}

void message_print(const float message)
{
     Serial.print(message);
}
void message_println(const float message)
{
     Serial.println(message);
}

void message_print(const bool message)
{
     Serial.print(message);
}
void message_println(const bool message)
{
     Serial.println(message);
}