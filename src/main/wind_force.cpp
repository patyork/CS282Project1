#include "simphys/wind_force.h"

#include <memory>
#include <chrono>

#include "simphys/vec3.h"
#include "simphys/particle.h"

namespace simphys {
  
  using std::shared_ptr;
  typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;

  WindForce::WindForce(vec3 newAccel)
    : accel{newAccel} { }

  void WindForce::setAccel(vec3 newAccel) {
    accel = newAccel;
  }

  void WindForce::update(shared_ptr<Particle> p, fsecond dt) {
    p->applyForce(accel*p->getMass()*p->getDrag());
  }  

}
