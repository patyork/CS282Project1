  
#include "simphys/physics_engine.h"
#include "simphys/sim_world.h"

#include <memory>
#include <chrono>
#include <iostream>

namespace simphys {

  using std::shared_ptr;
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

  void PhysicsEngine::tick(fseconds dt) {

    if (dt - lastTick > fseconds{0.0}) {
      lastTick = dt;
      auto objects = sw->getObjects();


	 for (auto& r : reg) {
	   auto fg = r.first;
	   auto p2 = r.second;
	
	  // apply the generated forces
	  fg->update(p2, dt);

	  // really cheap way of testing for collisions with ground.
	  if (p2->getPosition().getY() > 0.0f) 
	    p2->integrate(dt);
	 } // end for
    } //end if
  } // end tick

  void PhysicsEngine::setSimWorld(shared_ptr<SimWorld> simworld) {
    sw = simworld;
  }

  shared_ptr<SimWorld> PhysicsEngine::getSimWorld() const {
    return sw;
  }



  void PhysicsEngine::addForcePair(shared_ptr<ForceGenerator> fg, shared_ptr<Particle> p) {
    reg.push_back(std::make_pair(fg, p));
  }

} //end namespace
