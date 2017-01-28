#include "bezier_cube.h"

#include <particle_system/particle_system.h>
#include <particle_system/particle.h>
#include <object/game_object.h>
#include <graphics/factory/render_object_factory.h>
#include <resources/resources.h>
#include <graphics/shaders/loaders/program_loader.h>
#include <graphics/factory/model_factory.h>

#include <game/scene_container.h>
#include <graphics/model/patch/patch.h>
#include <graphics/factory/texture_factory.h>
#include <graphics/model/mesh.h>
#include <graphics/model/model.h>

BezierCube::BezierCube(std::shared_ptr<ParticleSystem> particle_system)
        :
        particle_system_(particle_system),
        game_object_(nullptr),
        show_(true){
    //UpdateGameObject();
}
BezierCube::~BezierCube(){
    if(game_object_)
        particle_system_->scene()->Remove(game_object_);
}
/*
void BezierCube::UpdateGameObject(){
    ifx::Resources& resources = ifx::Resources::GetInstance();
    std::string vertex_path =
            resources.GetResourcePath("bezier_cube/main.vs",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("bezier_cube/main.fs",
                                      ifx::ResourceType::SHADER);
    auto program = ProgramLoader().CreateProgram(vertex_path, fragment_path);
    auto model = ifx::ModelFactory::LoadCubeModel();
    auto render_object = std::shared_ptr<ifx::RenderObject>(
            new ifx::RenderObject(ObjectID(0), model));
    render_object->addProgram(program);
    render_object->SetBeforeRender([&](const Program* program){
        auto& particles = particle_system_->particles();
        int i = 0;
        for(auto& particle : particles){
            if(!particle->detect_collision())
                continue;
            auto& position = particle->position();
            std::string gl_location_str = "ControlPoints[";
            gl_location_str += std::to_string(i);
            gl_location_str += "]";

            GLint gl_location = glGetUniformLocation(program->getID(),
                                                     gl_location_str.c_str());
            glUniform3f(gl_location, position.x, position.y, position.z);

            i++;
        }
    });
    render_object->SetAfterRender([](const Program* program){

    });

    game_object_ = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());

    game_object_->Add(render_object);
    particle_system_->scene()->Add(game_object_);
}
*/

void BezierCube::UpdateGameObject(){
    if(game_object_)
        particle_system_->scene()->Remove(game_object_);
    if(!show_)
        return;

    std::vector<std::unique_ptr<ifx::Mesh>> meshes;
    meshes.push_back(CreateMesh(CreateBackFace()));
    meshes.push_back(CreateMesh(CreateFrontFace()));

    meshes.push_back(CreateMesh(CreateTopFace()));
    meshes.push_back(CreateMesh(CreateDownFace()));

    meshes.push_back(CreateMesh(CreateLeftFace()));
    meshes.push_back(CreateMesh(CreateRightFace()));


    auto model = ifx::Model::MakeModel(ifx::NO_FILEPATH, std::move(meshes));

    auto render_object = std::shared_ptr<ifx::RenderObject>(
            new ifx::RenderObject(ObjectID(0), model));
    render_object->addProgram(LoadProgram());

    game_object_ = std::shared_ptr<ifx::GameObject>(new ifx::GameObject());
    game_object_->Add(render_object);
    particle_system_->scene()->Add(game_object_);
}

BezierPoints BezierCube::CreateBackFace(){
    BezierPoints points;

    auto& particle_matrix = particle_system_->particle_matrix();
    float a = 4;
    int i = 0;
    for(int j = 0; j < a; j++){
        for(int k = 0; k < a; k++){
            auto& position = particle_matrix[i][j][k]->position();
            points.X[j][k] = position.x;
            points.Y[j][k] = position.y;
            points.Z[j][k] = position.z;
        }
    }

    return points;
}

BezierPoints BezierCube::CreateFrontFace(){
    BezierPoints points;

    auto& particle_matrix = particle_system_->particle_matrix();
    float a = 4;
    int i = 3;
    for(int j = 0; j < a; j++){
        for(int k = 0; k < a; k++){
            auto& position = particle_matrix[i][j][k]->position();
            points.X[j][k] = position.x;
            points.Y[j][k] = position.y;
            points.Z[j][k] = position.z;
        }
    }

    return points;
}

BezierPoints BezierCube::CreateDownFace(){
    BezierPoints points;

    auto& particle_matrix = particle_system_->particle_matrix();
    float a = 4;
    int j = 0;
    for(int i = 0; i < a; i++){
        for(int k = 0; k < a; k++){
            auto& position = particle_matrix[i][j][k]->position();
            points.X[i][k] = position.x;
            points.Y[i][k] = position.y;
            points.Z[i][k] = position.z;
        }
    }

    return points;
}

BezierPoints BezierCube::CreateTopFace(){
    BezierPoints points;

    auto& particle_matrix = particle_system_->particle_matrix();
    float a = 4;
    int j = 3;
    for(int i = 0; i < a; i++){
        for(int k = 0; k < a; k++){
            auto& position = particle_matrix[i][j][k]->position();
            points.X[i][k] = position.x;
            points.Y[i][k] = position.y;
            points.Z[i][k] = position.z;
        }
    }

    return points;
}


BezierPoints BezierCube::CreateLeftFace(){
    BezierPoints points;

    auto& particle_matrix = particle_system_->particle_matrix();
    float a = 4;
    int k = 0;
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            auto& position = particle_matrix[i][j][k]->position();
            points.X[i][j] = position.x;
            points.Y[i][j] = position.y;
            points.Z[i][j] = position.z;
        }
    }

    return points;
}
BezierPoints BezierCube::CreateRightFace() {
    BezierPoints points;

    auto& particle_matrix = particle_system_->particle_matrix();
    float a = 4;
    int k = 3;
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            auto& position = particle_matrix[i][j][k]->position();
            points.X[i][j] = position.x;
            points.Y[i][j] = position.y;
            points.Z[i][j] = position.z;
        }
    }

    return points;
}

std::unique_ptr<ifx::Mesh> BezierCube::CreateMesh(BezierPoints points){
    const int M = 4;
    std::vector<Vertex> vertices;
    vertices.resize(M*M);
    int id_i = 0;
    int id_j = 0;
    int n = 0;
    int m = 0;

    int l = 0;
    for(int i = 0; i < M; i++){
        for(int j = 0; j < M; j++){
            vertices[l++] = Vertex{glm::vec3(points.X[i][j],
                                             points.Y[i][j],
                                             points.Z[i][j]),
                                   glm::vec3(0.0f, 0.0f, -1.0f),
                                   glm::vec2(0.0f, 0.0f)};
        }
    }

    // Indices for Patch
    std::vector <GLuint> indices = {
            0, 1, 2, 3,
            4, 5, 6, 7,
            8, 9, 10, 11,
            12, 13, 14, 15
    };

    auto mesh = std::unique_ptr<ifx::Mesh>(
            new ifx::Patch(vertices, indices,
                           ifx::TesselationParams{
                                   2.0f, 2.0f, vertices.size(),
                                   id_i, id_j, n, m}));
    auto material = std::make_shared<ifx::Material>();
    material->diffuse = ifx::TextureFactory().LoadContainerDiffuse();
    material->specular = ifx::TextureFactory().LoadContainerSpecular();
    mesh->material(material);

    return mesh;
}

std::shared_ptr<Program> BezierCube::LoadProgram(){
    ifx::Resources& resources = ifx::Resources::GetInstance();
    std::string vertex_path =
            resources.GetResourcePath("bezier_cube/tessellation/tess.vs",
                                      ifx::ResourceType::SHADER);
    std::string fragment_path =
            resources.GetResourcePath("bezier_cube/tessellation/tess.fs",
                                      ifx::ResourceType::SHADER);
    std::string tcs_path =
            resources.GetResourcePath("bezier_cube/tessellation/tess.tcs",
                                      ifx::ResourceType::SHADER);
    std::string tes_path =
            resources.GetResourcePath("bezier_cube/tessellation/tess.tes",
                                      ifx::ResourceType::SHADER);

    return ProgramLoader().CreateProgram(vertex_path, fragment_path,
                                         tcs_path, tes_path);
}
