#ifndef FORCE_GENERATOR_H
#define FORCE_GENERATOR_H

/*
  Interface for a force generating class.

  Based on the force generator concept described in Millington, ch. 5.
  
  \author Richard Kelley
*/

#include <memory>
#include <chrono>

namespace simphys {
  
  class Particle;
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;

  using std::shared_ptr;
  
  class ForceGenerator {

    /* 
       Override this function to apply a specific type of force to the
       given particle.
    */
public:
    virtual void update(shared_ptr<Particle> p, fsecond dt)=0;
  };
    
}

#endif // FORCE_GENERATOR_H
