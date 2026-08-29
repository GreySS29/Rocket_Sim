#include "../include/Launch_bay.h"

void Launch_bay::launch_falcon9(Earth& earth, std::unique_ptr<Rocket>& rocket , RocketRender& roc_render)
{
// remove to log class
   std::ofstream ofs("../Log/log.txt");

    if (!ofs.is_open()) {
        std::cout << "log doesn't exist\n";
        return;
    }

    std::ofstream ofs_force("../Log/force.txt");

    if (!ofs_force.is_open()) {
        std::cout << "log doesn't exist\n";
        return;
    }



    
    rocket->print_status();

    const int max_steps = 537;
    const int separation_time = 160;
    const int PACE = 1;
    int last_step = 0;
    
     for(int step=0; step<=separation_time; ++step)
     {
         if(step >120 && step <=140 && step%2 ==0) rocket->set_direction(160.0-step); // 30
        else if(step >60 && step <=120 && step%2 ==0) rocket->set_direction(130.0-step); // 40
        else if(step >40 && step <=60 && step%2==0) rocket->set_direction(120.0-step); //70
        else if(step >20 && step <=40 && step%2==0) rocket->set_direction(110.0-step); //80
        double t = step* PACE;
        
        rocket ->run(earth,PACE, roc_render);
        
        
        if(step % 20 == 0) {
      rocket ->print_status_flight_short(ofs, step);
         }
        
        
        last_step = t; 
     }

      
    std::cout << "time of separate Booster : " << last_step << '\n';
    std::unique_ptr<Stage> booster_single =rocket->separate_booster();  
    rocket->set_direction(30.0); 
    rocket->print_status();


     for(int step=last_step; step<=max_steps; ++step)
     {
      if(step >440 && step <460 && step%2==0 ) rocket->set_direction(470.0-step);

      double t = step* PACE;
        
      rocket ->run(earth,PACE,roc_render);
      
      if(step % 30 == 0) {
      rocket ->print_status_flight_short(ofs, step);
         }
      }
    
   
   roc_render.put_force_buffer(ofs_force);
   rocket->print_status(); 

    
};

void Launch_bay::launch_def_rock(Earth& earth,std::unique_ptr<Rocket>& rocket, RocketRender& roc_render)
{

   rocket->print_status();
    
     const int max_steps = 140;
     const int separation_time = 72;
     const int PACE = 1;
     int last_step = 0;
    
     for(int step=0; step<=separation_time; ++step)
     {
        
        if(step >10) rocket->set_direction(100.0-step);
        double t = step* PACE;
        std::cout << "Time : " << t << " s" << '\n';
        rocket ->run(earth,PACE, roc_render);
        
        
        last_step = t;
     }
    std::cout << "time of separate Booster : " << last_step << '\n';
    std::unique_ptr<Stage> booster_single =rocket->separate_booster();  
     rocket->set_direction(32.0); //temp
    rocket->print_status();


     for(int step=last_step; step<=max_steps; ++step)
     {
         if(step == 100) rocket->set_direction(0.0);
         if(step >72) rocket->set_direction(100.0-step);
        double t = step* PACE;
        std::cout << "Time : " << t << " s" << '\n';
        rocket ->run(earth,PACE, roc_render);
        
        
        last_step = t;
     }

    rocket->print_status(); 
};