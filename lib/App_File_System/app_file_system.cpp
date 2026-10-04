#include "app_file_system.h"

void init_fs()
{
 if (!LittleFS.begin())
    {
     message_println("[ERREUR DE MONTAGE DU SYSTEME DES FICHIERS]");
     return;
    }
    
     message_println("[SYSTEME DES FICHIERS MONTE]");
}