#pragma once

namespace asteroidish {
    // Represents the current state of the game
    enum GameState {
        GAME_ACTIVE
    };

    class Game {
        public:
            // Game state
            GameState    state;	
            bool         keys[1024];
            unsigned int width, height;
            // Constructor/Destructor
            Game(unsigned int width, unsigned int height);
            ~Game();
            // Initialize game state (load all shaders/textures/levels)
            void init();
            // Game loop
            void process_input(float dt);
            void update(float dt);
            void render();
    };
}