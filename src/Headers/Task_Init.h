#ifndef Task_Init_h
#define Task_Init_h

static const inline void File_System_Task_Init(int Stack_Depth,int Core,int Priority){
    xTaskCreatePinnedToCore(File_System,"File_System",Stack_Depth,NULL,Priority,&File_System_Task_Handle,Core);
}

static const inline void Time_System_Task_Init(int Stack_Depth,int Core,int Priority){
    xTaskCreatePinnedToCore(Time_System,"Time_System",Stack_Depth,NULL,Priority,&Time_System_Task_Handle,Core);
}

static const inline void Animation_Task_Init(int Stack_Depth,int Core,int Priority){
    xTaskCreatePinnedToCore(Animation,"Animation",Stack_Depth,NULL,Priority,&Animation_Task_Handle,Core);
}

static const inline void CaptivePortal_Task_Init(int Stack_Depth,int Core,int Priority){
    xTaskCreatePinnedToCore(CaptivePortal,"CaptivePortal",Stack_Depth,NULL,Priority,&CaptivePortal_Task_Handle,Core);
}

static const inline void Init_Tasks(){
    Animation_Task_Init(8048,1,3);
    File_System_Task_Init(5120,0,1);
    CaptivePortal_Task_Init(8000,0,1);
    Time_System_Task_Init(6048,0,1);
}

#endif