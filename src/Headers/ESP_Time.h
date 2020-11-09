#ifndef ESP_Time_h
#define ESP_Time_h

class ESP_Time
{
    private:
        String CurrentTime = "";
    public:
        ESP_Time(){};

        void Tick(){

        }

        void Set_Time(){

        }

        String GetCurrentTime(){
            return CurrentTime;
        }
};

ESP_Time Time;

#endif