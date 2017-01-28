#ifndef PROJECT_PARTICLE_SYSTEM_FACTORY_H
#define PROJECT_PARTICLE_SYSTEM_FACTORY_H

#include <memory>
#include <vector>

class ParticleSystem;
class SpringConstraint;
class ParticleSystem;
class Particle;
class ControlBox;

class ParticleSystemFactory {
public:
    ParticleSystemFactory();
    ~ParticleSystemFactory();

    void Init(std::shared_ptr<ParticleSystem> particle_system,
              std::shared_ptr<ControlBox> control_box);
private:
    std::vector<std::vector<std::vector<std::shared_ptr<Particle>>>>
            CreateParticles();
    void AddParticles(
            std::shared_ptr<ParticleSystem> particle_system,
            std::vector<std::vector<std::vector<std::shared_ptr<Particle>>>>
            particles);
    void CreateMutualConstraints(
            std::shared_ptr<ParticleSystem> particle_system,
            std::vector<std::vector<std::vector<std::shared_ptr<Particle>>>>
                            particles);
    void AddControlBoxConstraints(
            std::shared_ptr<ParticleSystem> particle_system,
            std::shared_ptr<ControlBox> control_box,
            std::vector<std::vector<std::vector<std::shared_ptr<Particle>>>>
            particles);
    std::shared_ptr<SpringConstraint> CreateSpring(
            std::shared_ptr<Particle> p1,
            std::shared_ptr<Particle> p2,
            bool rest_length = false,
            bool draw = false);

    void MaybeAddConstrain(
            std::shared_ptr<ParticleSystem> particle_system,
            std::shared_ptr<Particle> p1,
            std::shared_ptr<Particle> p2,
            bool draw = false);

    void SetDefaultParameters(std::shared_ptr<ParticleSystem> particle_system,
                              std::shared_ptr<ControlBox> control_box);
    void SetDefaultParticleMass(
            std::shared_ptr<ParticleSystem> particle_system);
    void SetDefaultDamping(
            std::shared_ptr<ParticleSystem> particle_system);
    void SetDefaultSpringCoefficient1(
            std::shared_ptr<ParticleSystem> particle_system);
    void SetDefaultSpringCoefficient2(
            std::shared_ptr<ControlBox> control_box);

    bool CheckIndex(int i);
};


#endif //PROJECT_PARTICLE_SYSTEM_FACTORY_H
