#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <memory>
#include <chrono>
#include "simphys/force_generator.h"
#include <vector>

namespace simphys {

  class SimWorld;
  using std::shared_ptr;
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

  typedef std::vector< std::pair<shared_ptr<ForceGenerator>, 
    shared_ptr<Particle> > > ForceRegistry;

  class PhysicsEngine {
  private:
    shared_ptr<SimWorld> sw;
    ForceRegistry reg;
    fseconds lastTick;

  public:
    PhysicsEngine()
      : lastTick{fseconds{0.016}} { }

    /*
      Update state.
    */
    void tick(fseconds dt);

    void setSimWorld(shared_ptr<SimWorld> simworld);
    shared_ptr<SimWorld> getSimWorld() const;

    void addForcePair(shared_ptr<ForceGenerator> fg, shared_ptr<Particle> p);

  };

}

#endif // PHYSICS_ENGINE_H
