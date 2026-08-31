#include "../include/Fabric.h"


std::unique_ptr<Rocket> Fabric::create_def_rock (const Earth& earth)
{
    //booster
    Engine engine {earth.surfacePoint(5.0),
        5000.0, //mass engine kg
        1500000.0, // thrust H
        547.0 // fuel_consumption kg/s
    };
    Tank tank {earth.surfacePoint(10.0), 
        5000.0, //mass tank kg
        45000.0 // fuel_mass kg
    };

    std::unique_ptr<Stage> booster = Stage::creat_stage(
        5.0, // position
        0.3, // C_D
        10.0, // Area
        engine,
        tank,
        earth,
        20*m
    );

    //upper_stage
    Engine engine_up {earth.surfacePoint(15.0),
        2000.0, //mass engine kg
        400000.0,  // thrust H
        200.0 // fuel_consumption kg/s
    };
    Tank tank_up {earth.surfacePoint(20.0),
        1000.0,  //mass tank kg
        12000.0 // fuel_mass kg
    };
    std::unique_ptr<Stage> upper_stage = Stage::creat_stage(
        15.0, // position
        0.3, // C_D
        10.0, // Area
        engine_up, 
        tank_up, 
        earth,
        10 * m
    );
    
    Payload payload {earth.surfacePoint(25.0),
        10000, //mass
        0.3, //c_d
        10 // area
    };

    return Rocket::create_rocket(std::move(booster),std::move(upper_stage),payload,earth);
};


std::unique_ptr<Rocket> Fabric::create_falcon9 (const Earth& earth){
    //booster
    Engine engine {earth.surfacePoint(5.0),
        15000.0,
        7600000.0, 
        2440.0
    };
    Tank tank {earth.surfacePoint(10.0), 
        15000.0,
        395700.0
    };
    std::unique_ptr<Stage> booster = Stage::creat_stage(
        5.0,
        0.3,
        10,
        engine,
        tank, 
        earth,
        40*m
    );

    //upper_stage
    Engine engine_up {earth.surfacePoint(15.0),
        10000.0,
        981000.0, 
        247.0
    };
    Tank tank_up {earth.surfacePoint(20.0),
        10000.0,
        92670.0
    };
    std::unique_ptr<Stage> upper_stage = Stage::creat_stage(
        15.0,
        0.3,
        10,
        engine_up,
        tank_up,
        earth,
        30*m
    );
    
    Payload payload {earth.surfacePoint(25.0),
        5000,
        0.3,
        10
    };


    return Rocket::create_rocket(std::move(booster),std::move(upper_stage),payload,earth);
};



