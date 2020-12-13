#ifndef File_System_h
#define File_System_h

    static const inline void File_System_Init(){LITTLEFS.begin();}

    String Error_Log(String szoveg){
        File f = LITTLEFS.open(ErrorLog, "a");
        if (!f) {} else {
            f.print(szoveg);f.print(" at: ");
            f.println( Time.GetCurrentTime() );
        }
            f.close();
        return szoveg;
    }

    long File_Size_Checker_Timer = 0;
    static const inline void Dynamic_File_Size_Manager(){
        if((millis() - File_Size_Checker_Timer >= 3600000)){
            File_Size_Checker_Timer = millis();
            if(LITTLEFS.exists(ErrorLog)){
            File ErrorLogFile = LITTLEFS.open(ErrorLog);
                if(ErrorLogFile.size() >= 16000){
                    ErrorLogFile.close();
                    LITTLEFS.remove(ErrorLog);
                }else{
                    ErrorLogFile.close();
                }
            }
        }
    }

    static const inline void Save_Current_Animation(int animNUM){
        File f = LITTLEFS.open(CurrentAnimation, "w");
        if (!f) {Error_Log("Can't open currentAnimation File for save!");} 
        else {f.print(animNUM);f.print("!");f.print(currentBrightness);}
        f.close();
    }

    static const inline int Get_Current_Animation(){
        if(LITTLEFS.exists(CurrentAnimation)){
            String ANIM = "",CrBright = "";
            boolean isOpened = false;
            File f = LITTLEFS.open(CurrentAnimation, "r");
            if (!f) {Error_Log("Can't open currentAnimation File for read!");
            }else {
                boolean FoundFirst = false;
                for (int i = 0; i < f.size(); i++){
                    char Buffer[1];
                    Buffer[0] = (char)f.read();
                    if(Buffer[0] == '!' || FoundFirst){
                        FoundFirst = true;
                        CrBright += Buffer[0];
                    }else{
                        ANIM += (char)f.read();
                    }
                    
                }
                isOpened = true;
            }
            f.close();
            if(isOpened){
                currentBrightness = CrBright.toInt();
                return ANIM.toInt();
            }else{return -1;}
        }else{
            return -1;
        }
    }

    static const inline String Get_All_File(){
        StaticJsonDocument<5000> doc;
        String MSG = "";
        JsonArray files = doc.createNestedArray("FILES");
        File root = LITTLEFS.open("/");
        File file = root.openNextFile();
        int SUM_Size = 0;
        while(file){
            JsonObject files_info = files.createNestedObject();
            files_info["NAME"] = String(file.name());
            files_info["SIZE"] = String(file.size());
            SUM_Size += file.size();
            file = root.openNextFile();
        }
        root.close();
        JsonObject SUM_FS_SIZE = doc.createNestedObject("FS_SIZE");
        SUM_FS_SIZE["All_File_Size"] = String(SUM_Size);
        serializeJson(doc,MSG);
        MSG += ";allinfo";
        return MSG;
    }

    static const inline String Del_Files(String File){
        if(LITTLEFS.exists(File)){
            if(LITTLEFS.remove(File)){
                return "File Deleted";
            }else{
                return "Cant Delete";
            }
        }else{
            return "File with name \"" + File + "\" does not exist.";
        }
    }

    String Get_Available_Space(){
        String SpaceArr = "";
        StaticJsonDocument<500> doc;
            doc["Chip Revision"]  = ESP.getChipRevision();
            doc["Current Frequency"] = ESP.getCpuFreqMHz();
            doc["Free Sketch Space"] = ESP.getFreeSketchSpace();
            doc["Total Heap"]   = ESP.getHeapSize();
            doc["Free Heap"]    = ESP.getFreeHeap();
            doc["Total PSRAM"]  = ESP.getPsramSize();
            doc["Free PSRAM"]   = ESP.getFreePsram();
        serializeJson(doc, SpaceArr);
        return SpaceArr;
    }

    long spacemonitorstart = 0;
    static const inline void Monitor_Space(){
        if(millis() - spacemonitorstart >= 10000){
            spacemonitorstart = millis();
            Send_Async(Get_Available_Space(),";SpaceMonitoring");
        }
    }

    void File_System( void * parameter ){
        File_System_Init();
        for ever{
            Dynamic_File_Size_Manager();
            Monitor_Space();
            vTaskDelay(10);
        }
    }
#endif