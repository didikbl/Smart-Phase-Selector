
#include "app_web_server.h"


AsyncWebServer server(80); 

static float input_voltage[3];
static active_line_t active_line = NO_ACTIVE_LINE;
String selected_line;

void run_webserver()
{
          setup_roots();
          server.begin();
          message_println("[SERVEUR ON....]");
          message_println("[SERVEUR RUNNING....]");
}


void setup_roots()
{
     server.on("/",HTTP_GET, webserver_home);
     server.on("/fetch-data",HTTP_GET ,webserver_update_data); 
     server.on("/post-data",HTTP_POST, webserver_parse_data); 
}


void webserver_update_data(AsyncWebServerRequest *request)
{
     
     JsonDocument doc;
     doc["value_1"] =  input_voltage[LINE_1];
     doc["value_2"] =  input_voltage[LINE_2];
     doc["value_3"] =  input_voltage[LINE_3];

     float value_1 = input_voltage[LINE_1];
     float value_2 = input_voltage[LINE_2]; 
     float value_3 = input_voltage[LINE_3];
     printf("LINE 1 : %f V \n",value_1);
     printf("LINE 2 : %f V \n",value_2);
     printf("LINE 3 : %f V \n",value_3);
     
     String json;
     serializeJson(doc, json); 

     request->send(200, "application/json", json);
     request->send(200, "text/plain", "OK");
     message_println("[DATA UPDATED]");
} 

void webserver_parse_data(AsyncWebServerRequest *request)
{
    
    bool parse_data = false;
    parse_data = request->hasParam("data",true); 
    //bool parse_data = request->hasParam("data",false);
    switch (parse_data)
    {
      case true:
          selected_line  = request->getParam("data",true)->value();
          message_print("[RECEIVED DATA]:");
          message_println(selected_line);
          request->send(200, "text/plain", "OK");
      break;
     
     default:
            message_println("[NO DATA RECEIVED]");
            request->send(200, "text/plain", "OK");
     break;
     }
}

void webserver_get_data(const float value_1, const float value_2, const float value_3 )
{
     input_voltage[LINE_1] = value_1;
     input_voltage[LINE_2] = value_2;
     input_voltage[LINE_3] = value_3;
}

active_line_t webserver_get_active_line()
{             

              active_line = (selected_line == "ACTIVE_LINE_1")? ACTIVE_LINE_1 : active_line;
              active_line = (selected_line == "ACTIVE_LINE_2")? ACTIVE_LINE_2 : active_line;
              active_line = (selected_line == "ACTIVE_LINE_3")? ACTIVE_LINE_3 : active_line;
              active_line = (selected_line == "LINE_1_INACTIVE")? LINE_1_INACTIVE : active_line;
              active_line = (selected_line == "LINE_2_INACTIVE")? LINE_2_INACTIVE : active_line;
              active_line = (selected_line == "LINE_3_INACTIVE")? LINE_3_INACTIVE : active_line;


              return active_line;
}



void webserver_home(AsyncWebServerRequest*request)
{
     request->send(LittleFS,"/index.html","text/html");
}
void webserver_home_example(AsyncWebServerRequest*request)
{
     request->send(LittleFS,"/index.html","text/html");
}