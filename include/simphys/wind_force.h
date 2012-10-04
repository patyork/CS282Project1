#ifndef WIND_FORCE_H
#define WIND_FORCE_H

#include <memory>
#include <chrono>
#include "simphys/vec3.h"
#include "simphys/force_generator.h"

namespace simphys {

  class Particle;
  //class vec3;
  typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;
  using std::shared_ptr;

  class WindForce : public ForceGenerator {
  private:
    vec3 accel;

  public:
    WindForce(vec3 newAccel);
    void setAccel(vec3 newAccel);
    void update(shared_ptr<Particle> p, fsecond dt);
  };

}

#endif // Wind_FORCE_H
