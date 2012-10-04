#ifndef PARTICLE_H
#define PARTICLE_H

#include <chrono>

#include "vec3.h"

typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

namespace simphys {
  
  /*
    A particle for a physics simulation.

    Based on Ch. 3 of Millington's Game Physics Engine Development.
  */
  class Particle {
  private:

    // current position
    vec3 pos;
    
    //first time flag
    bool initial;
    
    //previous position
    vec3 prvPos;
    
    // current velocity
    vec3 vel;

    // current acceleration
    vec3 acc;

    // accumulated force for the current time step
    vec3 accumulatedForces;

    // Damping parameter 
    float damping;

    // 1.0f / mass
    float invMass;

    // Drag Coefficient
    float drag;

  public:

    Particle();
    
    // setters
    void setPosition(const vec3& newPos);
    void setPrvPosition(const vec3& newPos);
    void setVelocity(const vec3& newVel);
    void setAcceleration(const vec3& newAcc);
    void setDamping(float d);
    void setMass(float m);
    void setDrag(float d);

    // getters
    vec3 getPosition() const;
    vec3 getPrvPosition() const;
    vec3 getVelocity() const;
    vec3 getAcceleration() const;
    float getDamping() const;
    float getMass() const;
    float getDrag() const;

    // Update the position and velocity of this particle.
    void integrate(fseconds duration);
    
    // clear the force accumulation vector
    void clearForces();

    // Apply a force to this particle
    void applyForce(const vec3& force);

  };

}

#endif // PARTICLE_H
