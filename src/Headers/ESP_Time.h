#ifndef ESP_Time_h
#define ESP_Time_h

class ESP_Time
{
    private:
        int SecTime = 1000;
        String CurrentTime = "";
        int Year,Month,Hour,Min,Sec;
        long Starting_Time = millis();
    public:
        ESP_Time(){};

        void Tick(){
            if(millis() - Starting_Time >= SecTime){
                Starting_Time = millis();
                Serial.println( String(Hour) + ":" + String(Min) + ":" + String(Sec) );
                Sec++;
            }

            if(Sec == 61){
                Sec = 0;
                Min++;
                if(Min == 61){
                    Min = 0;
                    Hour++;
                    if(Hour == 25){
                        Hour = 0;
                    }
                }
            }
        }

        void Set_Time(int CurrYear, int CurrMonth, int CurrHour, int CurrMin, int CurrSec){
            Year    = CurrYear;
            Month   = CurrMonth;
            Hour    = CurrHour;
            Min     = CurrMin;
            Sec     = CurrSec;
        }

        String GetCurrentTime(){
            return CurrentTime;
        }
};

ESP_Time Time;

    void Time_System( void * parameter ){
        for ever{
            Time.Tick();
            vTaskDelay(1);
        }
    }

#endif