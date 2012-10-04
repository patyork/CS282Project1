#include "simphys/particle.h"
#include <iostream>

namespace simphys {

  Particle::Particle()
    : pos{10.0f, 20.0f, 0.0f}
    , initial{true}
    , prvPos {10.0f, 20.0f, 0.0f}
    , vel{0.0f, 0.0f, 0.0f}
    , acc{0.0f, 0.0f, 0.0f}
    , accumulatedForces{0.0f, 0.0f, 0.0f}
    , damping{1.0f}
    , invMass{1.0f}
    , drag{0.8f} { }

  void Particle::setPosition(const vec3& newPos) {
    pos = newPos;
  }
    void Particle::setPrvPosition(const vec3& newPos) {
    prvPos = newPos;
  }

  void Particle::setVelocity(const vec3& newVel) {
    vel = newVel;
  }

  void Particle::setAcceleration(const vec3& newAcc) {
    acc = newAcc;
  }

  void Particle::setDamping(float d) {
    damping = d;
  }

  void Particle::setMass(float m) {
    if(m > 0 )
      invMass = 1.0f / m;
  }

  void Particle::setDrag(float d)
  {
    drag = d;
  }

  vec3 Particle::getPosition() const {
    return pos;
  }
   
  vec3 Particle::getPrvPosition() const {
    return prvPos;
  }

  vec3 Particle::getVelocity() const {
    return vel;
  }
  
  vec3 Particle::getAcceleration() const {
    return acc;
  }

  float Particle::getDamping() const {
    return damping;
  }
  
  float Particle::getMass() const {
    return 1.0f / invMass;
  }
  
  float Particle::getDrag() const
  {
    return drag;
  }

  void Particle::integrate(fseconds duration) {

    vec3 resultantAcc = acc;
    resultantAcc = resultantAcc + (invMass * accumulatedForces);
    acc = resultantAcc;
 
    vec3 placeholder;
    // don't move objects that have "infinite mass."
    if (invMass <= 0.0f) {
      return;
    }

    // update position using Verlet integration
    if(initial){
      prvPos=pos;   
    
      pos = pos + duration.count() * vel+.5f*acc*duration.count()*duration.count();

      initial = false;
    }
    else{
        placeholder = pos;
        pos = 2.0f*pos-prvPos+acc*duration.count()*duration.count();
        prvPos = placeholder;
    }  

    // update velocity using Euler integration
    vel = vel + duration.count() * resultantAcc;

    // incorporate damping
    vel = vel * damping;

    clearForces();
  }

  void Particle::clearForces() {
    accumulatedForces = vec3{0.0f, 0.0f, 0.0f};
  }

  void Particle::applyForce(const vec3& force) {
    accumulatedForces = accumulatedForces + force;
  }

}
