#include "simphys/gravity_force.h"

#include <memory>
#include <chrono>

#include "simphys/vec3.h"
#include "simphys/particle.h"

namespace simphys {
  
  using std::shared_ptr;
  typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;

  GravityForce::GravityForce(vec3 newAccel)
    : accel{newAccel} { }

  void GravityForce::setAccel(vec3 newAccel) {
    accel = newAccel;
  }

  void GravityForce::update(shared_ptr<Particle> p, fsecond dt) {
    p->applyForce(accel*p->getMass());
  }  

}
