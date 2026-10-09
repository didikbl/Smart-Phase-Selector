/*      
      wifi
       |
       V
 setup_roots()
       |
       V
  server_run()

*/
#include "app_web_server.h"

//-----------------------------------------------GLOBAL VARIABLE--------------------------------------------------

AsyncWebServer server(80); 

static float input_voltage[3];
static active_line_t active_line = NO_ACTIVE_LINE;
String  selected_line;

bool web_server_init()
{
          setup_roots();
          server.begin();
          message_println("[SERVEUR ON....]");
          message_println("[SERVEUR RUNNING....]");
          return true;
}

//------------------------------------------------SETUP YOUR ROOTS HERE--------------------------------------------
void setup_roots()
{
     //server.on("/",HTTP_GET, webserver_home_example);
     server.on("/",HTTP_GET, webserver_home);
     server.on("/fetch-data",HTTP_GET ,webserver_update_data); 
     server.on("/post-data",HTTP_POST, webserver_parse_data); 
}
//------------------------------------------------IMPLEMENT YOUR CALLBACK FUNCTIONS HERE--------------------------
//------------------------------------------------FOR DATA--------------------------------------------------------
void webserver_update_data(AsyncWebServerRequest *request)
{
     // Création d'un objet JSON
     JsonDocument doc;
     doc["value_1"] =  input_voltage[LINE_1];
     doc["value_2"] =  input_voltage[LINE_2];
     doc["value_3"] =  input_voltage[LINE_3];

     //Conversion en chaîne JSON
     String json;
     serializeJson(doc, json); 

     // Envoi de la réponse JSON
     request->send(200, "application/json", json);
     request->send(200, "text/plain", "OK");
     message_println("[DATA UPDATED]");
} 

void webserver_parse_data(AsyncWebServerRequest *request)
{
     //data in the body of URL
    bool parse_data = false;
    parse_data = request->hasParam("data",true); 
    //data in the URL
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

//------------------------------------------------IMPLEMENT FUNCTION TO SERVE YOUR HTML PAGES HERE -------------------------------------------------------
//-----------------------------------------------------------EXAMPLE------------------------------------------------
void webserver_home(AsyncWebServerRequest*request)
{
     request->send(LittleFS,"/index.html","text/html");
}
void webserver_home_example(AsyncWebServerRequest*request)
{
     request->send(LittleFS,"/index.html","text/html");
}