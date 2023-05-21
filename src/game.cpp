#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

using namespace asteroidish;

// Game-related state data
SpriteRenderer *renderer;

Game::Game(unsigned int width, unsigned int height) 
    : state(GAME_ACTIVE), keys(), width(width), height(height) {}

Game::~Game() {
    delete renderer;
}

void Game::init() {
    // Load shaders
    ResourceManager::load_shader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");
    // Configure shaders
    glm::mat4 projection = glm::ortho(0.0f,
                                      static_cast<float>(this->width), 
                                      static_cast<float>(this->height),
                                      0.0f,
                                      -1.0f,
                                      1.0f);
    ResourceManager::get_shader("sprite").use().set_integer("image", 0);
    ResourceManager::get_shader("sprite").set_matrix4("projection", projection);
    // Set render-specific controls
    Shader sprite_shader = ResourceManager::get_shader("sprite");
    renderer = new SpriteRenderer(sprite_shader);
}

void Game::update(float dt) {}

void Game::process_input(float dt) {}

void Game::render() {
    renderer->draw_sprite(glm::vec2(200.0f, 200.0f),
                          glm::vec2(200.0f, 200.0f),
                          0.0f,
                          glm::vec3(1.0f, 1.0f, 1.0f));
}