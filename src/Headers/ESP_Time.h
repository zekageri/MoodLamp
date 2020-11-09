#ifndef ESP_Time_h
#define ESP_Time_h

class ESP_Time
{
    private:
        int SecTime = 1000;
        String CurrentTime = "";
        int Year = 2020;
        int Month,Day,Hour,Min,Sec = 0;
        long Starting_Time = millis();
        int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

        void Assemble_Time(){
            String ReadableMonth,ReadableHour,ReadableMin,ReadableSec = "0";
            if(Hour < 10)   {ReadableHour   += String(Hour);}   else{ReadableHour   = String(Hour);}
            if(Min < 10)    {ReadableMin    += String(Min);}    else{ReadableMin    = String(Min);}
            if(Sec < 10)    {ReadableSec    += String(Sec);}    else{ReadableSec    = String(Sec);}
            if(Month < 10)  {ReadableMonth  += String(Month);}  else{ReadableMonth  = String(Month);}
            CurrentTime = String(Year) + ":" + ReadableMonth + "  " + ReadableHour += ":" + ReadableMin += ":" + ReadableSec;
            Serial.println(CurrentTime);
        }

    public:
        ESP_Time(){};

        void Tick(){
            if(millis() - Starting_Time >= SecTime){
                Starting_Time = millis();
                Assemble_Time();
                Sec++;
            }

            if(Sec > 59){
                Sec = 0;
                Min++;
                if(Min > 59){
                    Min = 0;
                    Hour++;
                    if(Hour > 23){
                        Hour = 0;
                        Day++;
                        if(Day > (months[Month]-1) ){
                            Day = 0;
                            Month++;
                            if(Month > 11){
                                Month   = 0;
                                Day     = 0;
                                Hour    = 0;
                                Min     = 0;
                                Sec     = 0;
                                Year++;
                            }
                        }
                    }
                }
            }
        }

        void Set_Time(int CurrYear, int CurrMonth, int CurrDay, int CurrHour, int CurrMin, int CurrSec){
            Year    = CurrYear;
            Month   = CurrMonth;
            Day     = CurrDay;
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
        Time.Set_Time(2020,11,9,22,26,0);
        for ever{
            Time.Tick();
            vTaskDelay(1);
        }
    }

#endif