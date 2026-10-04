#include "app_wifi.h"

//------------------DEFAULT WIFI AP CONFIGURATION----------------------------------
      static char _ssid [] ="ESP-32-AP";
      static char _password [] = "12345678";
      IPAddress local_IP(192,168,4,2);
      IPAddress gateway(192,168,4,1);
      IPAddress subnet(255,255,255,0);

      static unsigned long _start_attempt_time;
      static _wifi_mode_t _wifi_mode;
      static app_err_t err;


app_err_t  _wifi_start_sta(const char *ssid, const char *password)
{  
      
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED && millis() - _start_attempt_time < 10000) 
      {

      }

      switch (WiFi.status())
      {
             case WL_CONNECTED:
                  return err = APP_OK;
             break;
      
             default:
                  return err = APP_FAIL;
             break;
      } 
}
app_err_t _wifi_start_sta(const String ssid, const String password)
{
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED && millis() - _start_attempt_time < 10000) {
             
      }

      switch (WiFi.status())
      {
              case WL_CONNECTED:
                   return err = APP_OK;
              break;
      
              default:
                   return err = APP_FAIL;
              break;
      }
}

//--------------------------------------------WIFI AP------------------------------------------------
app_err_t _wifi_start_ap()
{
      WiFi.softAPConfig(local_IP,gateway,subnet);
      WiFi.softAP(_ssid, _password);
      err = (WiFi.getMode() != WIFI_AP)? APP_FAIL : APP_OK;
      return err;
}

app_err_t _wifi_start_ap(const char* ssid, const char* password)
{
      WiFi.softAPConfig(local_IP,gateway,subnet);
      WiFi.softAP(ssid, password);
      err = (WiFi.getMode() != WIFI_AP)? APP_FAIL : APP_OK;
      return err;
}

app_err_t _wifi_start_ap(String ssid, String password)
{
      WiFi.softAPConfig(local_IP,gateway,subnet);
      WiFi.softAP(ssid, password);
      err = (WiFi.getMode() != WIFI_AP)? APP_FAIL : APP_OK;
      return err;
}

app_err_t _wifi_start_ap(IPAddress _local_IP, IPAddress _gateway, IPAddress _subnet)
{
      WiFi.softAPConfig(_local_IP,_gateway,_subnet);
      WiFi.softAP(_ssid, _password);
      err = (WiFi.getMode() != WIFI_AP)? APP_FAIL : APP_OK;
      return err;
      
}
app_err_t _wifi_start_ap(const char* ssid, const char* password, IPAddress _local_IP, IPAddress _gateway, IPAddress _subnet)
{
      WiFi.softAPConfig(_local_IP,_gateway,_subnet);
      WiFi.softAP(ssid, password);
      err = (WiFi.getMode() != WIFI_AP)? APP_FAIL : APP_OK;
      return err;
}

app_err_t _wifi_start_ap(String ssid, String password, IPAddress _local_IP, IPAddress _gateway, IPAddress _subnet)
{
     WiFi.softAPConfig(_local_IP,_gateway,_subnet);
     WiFi.softAP(ssid, password);
     err = (WiFi.getMode() != WIFI_AP)? APP_FAIL : APP_OK;
     return err;
}

//--------------------------------------------------REPORT------------------------------------------------
_wifi_mode_t wifi_get_mode()
{
             switch (WiFi.getMode())
             {
             case WIFI_AP:
                  _wifi_mode = WIFI_AP_MODE;
             break;

             case WIFI_STA:
                  _wifi_mode = WIFI_STA_MODE;
             break;

             case WIFI_AP_STA:
                  _wifi_mode = WIFI_AP_STA_MODE;
             break;
 
             default:
                    _wifi_mode = WIFI_IDLE_MODE;
             break;
             }
             return _wifi_mode;
}
void _wifi_report()
{ 

     wifi_get_mode();
     switch (_wifi_mode)
     {
     case WIFI_AP_MODE:
          ap_mode_report();
     break;

     case WIFI_STA_MODE:
          sta_mode_report();
     break;

     case WIFI_AP_STA_MODE:
          ap_sta_mode_report();
     break;
     
     default:
           idle_mode_report();
     break;
     }
}
void ap_mode_report()
{
     String device_ssid = WiFi.softAPSSID();
     IPAddress ip = WiFi.softAPIP();
     String device_ip = ip.toString();
     int connected_devices = WiFi.softAPgetStationNum();
     if(err != APP_FAIL){
        //---------------DISPLAY INFORMATIONS-------------------
        printf("[----------[WIFI MODULE]---------]\n");
        printf("[WIFI MODE]:[ACCES POINT]\n[AP SSID]:[%s]\n",device_ssid.c_str());
        printf("[IP ADDRESS]:[%s]\n[CONNECTED STATION]:[%d]\n",device_ip,connected_devices); 
     }

     else{
          printf("[----------[WIFI MODULE]---------]\n");
          printf("[AP CONFIGURATION ERROR....]\n");
          printf("[PLEASE REBOOT....]\n");
     }
}
void sta_mode_report()
{
     String network_ssid = WiFi.SSID();
     IPAddress ip = WiFi.localIP();
     String device_ip = ip.toString();
     int network_power = WiFi.RSSI();
     if(err != APP_FAIL){
        //---------------DISPLAY INFORMATIONS-------------------
        printf("[----------[WIFI MODULE]---------]\n");
        printf("[WIFI MODE]:[STATION MODE]\n[NETWORK SSID]:[%s]\n",network_ssid.c_str());
        printf("[IP ADDRESS]:[%s]\n[NETWORK STRENGTH]:[%d]\n",device_ip,network_power); 
     }

     else{
          printf("[----------[WIFI MODULE]---------]\n");
          printf("[STA CONFIGURATION ERROR....]\n");
          printf("[PLEASE REBOOT....]\n");
     }
}
void ap_sta_mode_report()
{
     
}
void idle_mode_report()
{
     
}
//------------------------------------ENERGY SAVING FUNCTIONS-------------------------------------------
void _wifi_off(){
     WiFi.mode(WIFI_OFF);
}
