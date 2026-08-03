#include "../include/Launch_bay.h"

void Launch_bay::launch_falcon9(Earth& earth, std::unique_ptr<Rocket>& rocket , RocketRender& roc_render)
{

   std::ofstream ofs("../Log/log.txt");

    if (!ofs.is_open()) {
        std::cout << "log doesn't exist\n";
        return;
    }

    
    rocket->print_status();
    
    const int max_steps = 537;
    const int separation_time = 160;
    const int PACE = 1;
    int last_step = 0;
    rocket ->run(earth,PACE);
    
     for(int step=0; step<=separation_time; ++step)
     {
        if(step >100 && step <160) rocket->set_direction(190.0-step);
        double t = step* PACE;
        
        rocket ->run(earth,PACE);
        rocket ->print_status_flight_short(ofs, step);
      //   if(step % 20 == 0) {
      //    std::cout << "Time : " << t << " s" << '\n';
      //    rocket->print_status_flight_short();
      //   }
        
        roc_render.add_trajectory(rocket->get_position().x, rocket->get_position_above_face().y);
        last_step = t;
     }
    std::cout << "time of separate Booster : " << last_step << '\n';
    std::unique_ptr<Stage> booster_single =rocket->separate_booster();  
    rocket->set_direction(30.0); 
    rocket->print_status();


     for(int step=last_step; step<=max_steps; ++step)
     {
      if(step >170 && step <200) rocket->set_direction(200.0-step);

        double t = step* PACE;
        
        rocket ->run(earth,PACE);
        rocket ->print_status_flight_short(ofs,step);
      //   if(step % 40 == 0) 
      //   {
      //    std::cout << "Time : " << t << " s" << '\n';
      //    rocket->print_status_flight_short();
      //   }
       
        
      roc_render.add_trajectory(rocket->get_position().x, rocket->get_position_above_face().y);
     }

    rocket->print_status(); 

    
};

void Launch_bay::launch_def_rock(Earth& earth,std::unique_ptr<Rocket>& rocket){
      rocket->print_status();
    
     const int max_steps = 140;
     const int separation_time = 72;
     const int PACE = 1;
     int last_step = 0;
    rocket ->run(earth,PACE);
    
     for(int step=0; step<=separation_time; ++step)
     {
        
        if(step >10) rocket->set_direction(100.0-step);
        double t = step* PACE;
        std::cout << "Time : " << t << " s" << '\n';
        rocket ->run(earth,PACE);
        
        
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
        rocket ->run(earth,PACE);
        
        
        last_step = t;
     }

    rocket->print_status(); 
};