#pragma once

namespace asteroidish {
    class Ship {
        public:
            inline Ship() {};
            float* get_vertices();
            int get_vertices_size();
            unsigned int* get_indices();
            int get_indices_size();
        private:
            static float vertices[];
            static unsigned int indices[];
            static int vertices_size;
            static int indices_size;
    };
}