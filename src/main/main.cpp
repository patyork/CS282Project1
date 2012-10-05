/*
  Main program.

  Time Flag Usage: Enter a float
				ex: ./project1 1.0
*/

#include <iostream>
#include <memory>

#include "simphys/sim_world.h"
#include "simphys/sim_engine.h"
#include "simphys/simobject.h"
#include "simphys/simobject2D.h"
#include "simphys/particle.h"
#include "simphys/vec3.h"
#include "simphys/gravity_force.h" 
#include "simphys/wind_force.h" 

int main(int argc, char **argv) {


  //define gravity
	simphys::vec3 gravity{0.0f, -9.81f, 0.0f};
  //define wind
	simphys::vec3 wind{-1.0f, 0.0f, 0.0f};

  // create a simulator
  simphys::SimEngine sim;

  auto clock_ptr = std::make_shared< simphys::Clock<fseconds> >(fseconds{0.0f});

  if( argc > 1 ) clock_ptr->setScale(atof(argv[1]));

  sim.setClock(clock_ptr);

  // create a world to simulate
  auto world_ptr = std::make_shared<simphys::SimWorld>(); 
  sim.setSimWorld(world_ptr);

  // create and initialize an object
  simphys::Particle p;
  simphys::Sprite s;
  simphys::SimObject2D testObject(p,s);
  auto obj_ptr = std::make_shared<simphys::SimObject2D>(testObject);
  auto objState = testObject.getState();
  objState->setPosition(simphys::vec3{10, 20, 0});
  objState->setVelocity(simphys::vec3{40.0, 100.0, 0});
  objState->setDrag(0.8f);

  //gravity generator
  auto grav = std::make_shared<simphys::GravityForce>(gravity);
  (sim.getPhysicsEngine())->addForcePair(grav, objState);

  //wind generator
  auto winds = std::make_shared<simphys::WindForce>(wind);
  (sim.getPhysicsEngine())->addForcePair(winds, objState);

  // add object to the world.
  world_ptr->add(obj_ptr);

  // initialize the simulator and run it.
  sim.init();
  sim.run();

}
