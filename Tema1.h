#pragma once

#include "components/simple_scene.h"

struct square {
    float posX;
    float posY; 
    float length;
    bool isOccupied;
};

struct star {
    float posX;
    float posY;
    glm::vec3 color;
    float size;
    float angularStep;
    bool deleteThis;
};

struct hexagon {
    float posX;
    float posY;
    glm::vec3 color;
    int health;
    bool deleteThis;
    float scaleX;
    float scaleY;
};

struct diamond {
    float posX;
    float posY;
    glm::vec3 color;
    int price;
    std::vector<star> starsProjectiles;
    bool throwStars;
    bool first;
    bool deleteThis;
    float scaleX;
    float scaleY;
};

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderScene();
    protected:
        glm::mat3 modelMatrix;
        float length, height, width;
        glm::vec3 corner;
        int sizeElements;

        int chances;
        int timer;
        int money;
        bool moveGun;

        glm::vec3 hexagonsPosY;
        std::vector<hexagon> hexagons;
        glm::vec3 colorOfMiniHexagon;

        square playSquares[9]{};
        square gunSquares[4]{};
        square healthSquares[3]{};

        star costs[8]{};

        std::vector<star> starsToCatch;

        const float playSpacing = 40.0f;
        const float gunSpacing = 80.0f;
        const float healthSpacing = 30.0f;

        const float playSquareOffsetX = 150.0f;
        const float playSquareOffsetY = 60.0f;
        const float gunSquareOffsetX = 70.0f;
        const float healthSquareOffsetX = 870.0f;

        glm::vec3 atackColors[4]{
            glm::vec3(0.9, 0.6, 0),
            glm::vec3(0.9, 0.1, 0.9),
            glm::vec3(0.2, 0.2, 1),
            glm::vec3(0.1, 1, 0.1)
        };

        diamond guns[4]{};
        std::vector<diamond> gunsAdded;
        diamond gunInMotion;
    };
}   // namespace m1

