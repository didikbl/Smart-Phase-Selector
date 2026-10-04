#ifndef _WIFI_H
#define _WIFI_H
#include <Arduino.h>
#include <WiFi.h>
#include "app_types.h"
#include "app_system_log.h"

//----------------------------------------------STA MODE START OVERLOADED FUNCTIONS---------------------------------------

app_err_t _wifi_start_sta(const char* ssid, const char* password);

app_err_t _wifi_start_sta(String ssid, String password);

//----------------------------------------------AP MODE START OVERLOADED FUNCTIONS---------------------------------------

 app_err_t _wifi_start_ap();

 app_err_t _wifi_start_ap(const char* ssid, const char* password);

 app_err_t _wifi_start_ap(String ssid, String password);

 app_err_t _wifi_start_ap(IPAddress _local_IP, IPAddress _gateway, IPAddress _subnet);

 app_err_t _wifi_start_ap(const char* ssid, const char* password, IPAddress local_IP, IPAddress gateway, IPAddress subnet);

 app_err_t _wifi_start_ap(String ssid, String password, IPAddress _local_IP, IPAddress _gateway, IPAddress _subnet);

//----------------------------------------------INFORMATIONAL FUNCTIONS---------------------------------------

_wifi_mode_t wifi_get_mode();
void _wifi_report();  
void ap_mode_report();
void sta_mode_report();
void ap_sta_mode_report();
void idle_mode_report();

//----------------------------------------------WIFI ENERGY SAVER FUNCTIONS---------------------------------------
void _wifi_off();
//----------------------------------------------WIFI COMPONENT VERSION 1 FUNCTIONS---------------------------------------

int _wifi_get_wifi_status();

#endif