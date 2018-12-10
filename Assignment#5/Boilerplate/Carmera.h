#pragma once
#include <iostream>
using namespace std;

class Carmera{
    public:
        glm::vec3 eye, center, up;
        float theta, phi;
        float r;
        // eye ----- carmera position
        // center ------ where the carmera looking at, world vec3(0, 0, 0)
        // up ----- up vector, usually vec3(0, 1, 0);

        void theta_up() {
            theta += 1;
            if (theta > 360) {
                theta = 0;
            }
        }

        void theta_down() {
            theta -= 1;
            if (theta < -360) {
                theta = 0;
            }
        }

        void phi_up() {
            phi += 1;
            if (phi > 360) {
                phi = 0;
            }
        }

        void phi_down() {
            phi -= 1;
            if (phi < -360) {
                phi = 0;
            }
        }

        void r_up() {
            if (r <= 22) {
                r += 1;
            }
        }

        void r_down() {
            if (r > 3) {
                r -= 1;
            }
        }

        void update() {
            float temp_theta = theta * 3.14f / 180.f;
            float temp_phi = phi * 3.14f / 180.f;

            // float x = r * sin(temp_theta) * sin(temp_phi);
            // float y = r * cos(temp_theta);
            // float z = r * sin(temp_theta) * cos(temp_phi);

            float x = r * cos(temp_theta) * cos(temp_phi);
            float y = r * sin(temp_theta);
            float z = r * cos(temp_theta) * sin(temp_phi);

            glm::vec3 temp_eye = glm::vec3(x, y, z);

            if (cos(temp_theta) > 0) {
                up = glm::vec3(0, 1, 0);
            }else {
                up = glm::vec3(0, -1, 0);
            }
            eye = temp_eye;
        }
};
