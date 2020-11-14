#ifndef ESP_Time_h
#define ESP_Time_h

class ESP_Time
{
    private:
        String CurrentDay = "Monday";
        String CurrentTime = "";

        long Starting_Time  = millis();
        int SecTime         = 1000;
        int Year            = 2020;
        int Month,Day,Hour,Min,Sec = 0;
        
        
        int months[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        char daysOfTheWeek[7][13] = {"Vasárnap", "Hétfő", "Kedd", "Szerda", "Csütörtök", "Péntek", "Szombat"};

        void Assemble_Time(){
            String ReadableMonth,ReadableHour,ReadableMin,ReadableSec = "0";
            if(Hour < 10)   {ReadableHour   += String(Hour);}   else{ReadableHour   = String(Hour);}
            if(Min < 10)    {ReadableMin    += String(Min);}    else{ReadableMin    = String(Min);}
            if(Sec < 10)    {ReadableSec    += String(Sec);}    else{ReadableSec    = String(Sec);}
            if(Month < 10)  {ReadableMonth  += String(Month);}  else{ReadableMonth  = String(Month);}
            CurrentTime = String(Year) + ":" + ReadableMonth + "  " + ReadableHour += ":" + ReadableMin += ":" + ReadableSec;
            Send_Async(CurrentTime,";InternalTime");
        }

        void Refresh_from_RTC(){
            DateTime now = rtc.now();
            Year    = now.year();
            Month   = now.month();
            Day     = now.day();
            Hour    = now.hour();
            Min     = now.minute()+5;
            Sec     = now.second()+30;
            CurrentDay = daysOfTheWeek[now.dayOfTheWeek()];
        }

    public:
        ESP_Time(){};
        
        void Setup_RTC(){
            if ( !rtc.begin() ) {
                Serial.println("Couldn't find RTC");
            }else{
                if ( rtc.lostPower() ) {
                    Serial.println("RTC lost power, lets set the time!");
                    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
                }
                Refresh_from_RTC();
            }
        }
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
                    Refresh_from_RTC();
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
            rtc.adjust(DateTime(Year, Month, Day, Hour, Min, Sec));
        }

        String GetCurrentTime(){return CurrentTime;}
};

ESP_Time Time;

    void Time_System( void * parameter ){
        //Time.Set_Time(2020,11,10,10,40,0);
        Time.Setup_RTC();
        for ever{
            Time.Tick();
            vTaskDelay(5);
        }
    }

#endif