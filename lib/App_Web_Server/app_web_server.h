#ifndef _WEBSERVER_H
#define _WEBSERVER_H
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h> 
#include "app_wifi.h"
#include "app_system_log.h"
#include "app_file_system.h"
#include "app_types.h"

static unsigned long _start_attempt_time;

void setup_roots();

void run_webserver();

void webserver_update_data(AsyncWebServerRequest *request);

void webserver_parse_data(AsyncWebServerRequest *request);

void webserver_get_data(const float value_1, const float value_2, const float value_3 );

active_line_t webserver_get_active_line();

void webserver_home(AsyncWebServerRequest*request);

void webserver_home_example(AsyncWebServerRequest*request);

#endif