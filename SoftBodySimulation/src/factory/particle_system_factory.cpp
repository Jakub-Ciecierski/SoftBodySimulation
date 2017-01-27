#include "factory/particle_system_factory.h"

#include <particle_system/particle.h>
#include "particle_system/particle_system.h"
#include <object/game_object.h>
#include <vector>
#include <particle_system/spring/spring_constraint.h>
#include <control_box.h>

ParticleSystemFactory::ParticleSystemFactory(){}
ParticleSystemFactory::~ParticleSystemFactory(){}

void ParticleSystemFactory::Init(
        std::shared_ptr<ParticleSystem> particle_system,
        std::shared_ptr<ControlBox> control_box){
    auto particles = CreateParticles(particle_system);
    AddParticles(particle_system, particles);
    CreateMutualConstraints(particle_system, particles);

    AddControlBoxConstraints(particle_system, control_box, particles);
}

std::vector<std::vector<std::vector<std::shared_ptr<Particle>>>>
        ParticleSystemFactory::CreateParticles(
        std::shared_ptr<ParticleSystem> particle_system){
    const int a = 4;
    const float box_length = 2;

    glm::vec3 init_position(-1, 1+2, -1);

    std::vector<std::vector<std::vector<std::shared_ptr<Particle>>>> particles;
    for(int i = 0; i < a; i++){
        std::vector<std::vector<std::shared_ptr<Particle>>> row;
        for(int j = 0; j < a; j++){
            std::vector<std::shared_ptr<Particle>> col;
            for(int k = 0; k < a; k++){
                auto particle = std::shared_ptr<Particle>(new Particle());
                particle->game_object()->moveTo(glm::vec3(
                        i/3.0f * box_length,
                        j/3.0f * box_length,
                        k/3.0f * box_length));
                particle->game_object()->move(init_position);
                col.push_back(particle);
            }
            row.push_back(col);
        }
        particles.push_back(row);
    }
    return particles;
}

void ParticleSystemFactory::AddParticles(
        std::shared_ptr<ParticleSystem> particle_system,
        std::vector<std::vector<std::vector<std::shared_ptr<Particle>>>>
        particles){

    const int a = 4;
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            for(int k = 0; k < a; k++){
                particle_system->AddParticle(particles[i][j][k]);
            }
        }
    }
/*
    particle_system->AddParticle(particles[0][0][0]);
    particle_system->AddParticle(particles[3][0][0]);
    particle_system->AddParticle(particles[0][0][3]);
    particle_system->AddParticle(particles[3][0][3]);
    particle_system->AddParticle(particles[0][3][0]);
    particle_system->AddParticle(particles[3][3][0]);
    particle_system->AddParticle(particles[0][3][3]);
    particle_system->AddParticle(particles[3][3][3]);*/
}

void ParticleSystemFactory::CreateMutualConstraints(
        std::shared_ptr<ParticleSystem> particle_system,
        std::vector<std::vector<std::vector<std::shared_ptr<Particle>>>>
        particles){
    int a = 4;
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            for(int k = 0; k < a; k++){
                int left = i - 1;
                int right = i + 1;
                int front = j + 1;
                int back = j - 1;
                int up = k + 1;
                int down = k - 1;

                if(CheckIndex(left))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[left][j][k]);
                if(CheckIndex(right))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[right][j][k]);
                if(CheckIndex(front))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[i][front][k]);
                if(CheckIndex(back))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[i][back][k]);
                if(CheckIndex(up))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[i][j][up]);
                if(CheckIndex(down))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[i][j][down]);

                // ...
                if(CheckIndex(left) && CheckIndex(front))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[left][front][k]);
                if(CheckIndex(left) && CheckIndex(back))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[left][back][k]);

                if(CheckIndex(right) && CheckIndex(front))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[right][front][k]);
                if(CheckIndex(right) && CheckIndex(back))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[right][back][k]);

                // ...
                if(CheckIndex(left) && CheckIndex(up))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[left][j][up]);
                if(CheckIndex(left) && CheckIndex(down))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[left][j][down]);

                if(CheckIndex(right) && CheckIndex(up))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[right][j][up]);
                if(CheckIndex(right) && CheckIndex(down))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[right][j][down]);

                // ...
                if(CheckIndex(front) && CheckIndex(up))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[i][front][up]);
                if(CheckIndex(front) && CheckIndex(down))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[i][front][down]);

                if(CheckIndex(back) && CheckIndex(up))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[i][back][up]);
                if(CheckIndex(back) && CheckIndex(down))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[i][back][down]);

                // ...
                if(CheckIndex(left) && CheckIndex(front) && CheckIndex(up))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[left][front][up]);
                if(CheckIndex(right) && CheckIndex(front) && CheckIndex(up))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[right][front][up]);

                if(CheckIndex(left) && CheckIndex(back) && CheckIndex(up))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[left][back][up]);
                if(CheckIndex(right) && CheckIndex(back) && CheckIndex(up))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[right][back][up]);

                if(CheckIndex(left) && CheckIndex(front) && CheckIndex(down))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[left][front][down]);
                if(CheckIndex(right) && CheckIndex(front) && CheckIndex(down))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[right][front][down]);

                if(CheckIndex(left) && CheckIndex(back) && CheckIndex(down))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[left][back][down]);
                if(CheckIndex(right) && CheckIndex(back) && CheckIndex(down))
                    MaybeAddConstrain(particle_system,
                                      particles[i][j][k],
                                      particles[right][back][down]);
            }
        }
    }
}

void ParticleSystemFactory::AddControlBoxConstraints(
        std::shared_ptr<ParticleSystem> particle_system,
        std::shared_ptr<ControlBox> control_box,
        std::vector<std::vector<std::vector<std::shared_ptr<Particle>>>>
        particles){
    auto control_particles = control_box->particles();
    for(auto& particle : control_particles){
        particle_system->AddParticle(particle);
    }
    auto spring1 = CreateSpring(particles[0][0][0], control_particles[0], true);
    auto spring2 = CreateSpring(particles[3][0][0], control_particles[1], true);
    auto spring3 = CreateSpring(particles[0][0][3], control_particles[2], true);
    auto spring4 = CreateSpring(particles[3][0][3], control_particles[3], true);
    auto spring5 = CreateSpring(particles[0][3][0], control_particles[4], true);
    auto spring6 = CreateSpring(particles[3][3][0], control_particles[5], true);
    auto spring7 = CreateSpring(particles[0][3][3], control_particles[6], true);
    auto spring8 = CreateSpring(particles[3][3][3], control_particles[7], true);

    particle_system->AddConstraint(spring1);
    particle_system->AddConstraint(spring2);
    particle_system->AddConstraint(spring3);
    particle_system->AddConstraint(spring4);
    particle_system->AddConstraint(spring5);
    particle_system->AddConstraint(spring6);
    particle_system->AddConstraint(spring7);
    particle_system->AddConstraint(spring8);
}

std::shared_ptr<SpringConstraint> ParticleSystemFactory::CreateSpring(
        std::shared_ptr<Particle> p1,
        std::shared_ptr<Particle> p2,
        bool rest_length){
    if(!rest_length){
        auto constraint = std::shared_ptr<SpringConstraint>(
                new SpringConstraint(p1, p2));
        return constraint;
    }else{
        auto constraint = std::shared_ptr<SpringConstraint>(
                new SpringConstraint(p1, p2, 0));
        return constraint;
    }

}

void ParticleSystemFactory::MaybeAddConstrain(
        std::shared_ptr<ParticleSystem> particle_system,
        std::shared_ptr<Particle> p1,
        std::shared_ptr<Particle> p2){
    auto& constraints = particle_system->constraints();
    for(auto& constraint : constraints){
        if((constraint->particle_a() == p1
            && constraint->particle_b() == p2)
           ||(constraint->particle_b() == p1
              && constraint->particle_a() == p2)){
            return;
        }

    }
    particle_system->AddConstraint(CreateSpring(p1, p2));
}

bool ParticleSystemFactory::CheckIndex(int i){
    return i >= 0 && i < 4;
}