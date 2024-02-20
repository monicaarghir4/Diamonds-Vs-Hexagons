#include "Tema1.h"

#include <iostream>

#include "transformers2D.h"
#include "objects2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

// Function that calculates the distance between two things using the Euclidean distance formula
float calculateDistance(float obj1X, float obj1Y, float obj2X, float obj2Y) {
    float deltaX = obj1X - obj2X;
    float deltaY = obj1Y - obj2Y;

    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    // setting the important parameters for the game
    timer = 0;
    chances = 3;
    money = 5;
    moveGun = false;

    // setting the corner for the grid and the length of the squares
    corner = glm::vec3(0, 0, 0);
    length = 100;

    // initializing the grid
    for (int i = 0; i < 9; i++) {
        playSquares[i].length = length;
        playSquares[i].isOccupied = false;
    }

    // calculating the positions of each square of the grid 
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int index = i * 3 + j;
            playSquares[index].posX = playSquareOffsetX + j * (playSquares[index].length + playSpacing);
            playSquares[index].posY = playSquareOffsetY + i * (playSquares[index].length + playSpacing);
        }
    }

    // creating the mesh of the play squares
    Mesh* playSquareObj = objects2D::CreateCenteredSquare("playSquareObj", corner, length, glm::vec3(1, 0.6, 0.6), true);
    AddMeshToList(playSquareObj);

    // setting the dimensions of the red rectangle
    height = 380;
    width = 60;

    // creating the mesh for the red rectangle
    Mesh* rectangle = objects2D::CreateCenteredRectangle("rectangle", corner, height, width, glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle);

    // initializing the empty squares where our guns will be displayed
    for (int i = 0; i < 4; i++) {
        gunSquares[i].length = length;
        gunSquares[i].posY = 600.0f;
    }

    for (int i = 0; i < 4; ++i) {
        gunSquares[i].posX = gunSquareOffsetX + i * (gunSquares[i].length + gunSpacing);
    }

    // creating the mesh for the squares of the guns
    Mesh* gunSquareObj = objects2D::CreateNonCenteredSquare("gunSquareObj", corner, length, glm::vec3(1, 0.7, 0.8), false);
    AddMeshToList(gunSquareObj);

    // initializing the squares of the health of the player
    length = 80;

    for (int i = 0; i < 3; i++) {
        healthSquares[i].length = length;
        healthSquares[i].posY = 650.0f;
    }

    for (int i = 0; i < 3; ++i) {
        healthSquares[i].posX = healthSquareOffsetX + i * (healthSquares[i].length + healthSpacing);
    }

    // creating the mesh for the squares of health
    Mesh* healthSquareObj = objects2D::CreateCenteredSquare("healthSquareObj", corner, length, glm::vec3(1, 0.1, 0.4), true);
    AddMeshToList(healthSquareObj);

    // initializing the guns we have
    length = 45;
    height = 10;
    width = 40;
    corner = glm::vec3(0, 0, 3);

    Mesh* gun1 = objects2D::CreateCenteredDiamond("gun1", corner, length, height, width, atackColors[0], true);
    AddMeshToList(gun1);

    guns[0].color = atackColors[0];
    guns[0].price = 1;
    guns[0].posX = gunSquares[0].posX + gunSquares[0].length / 2.0f;
    guns[0].posY = gunSquares[0].posY + gunSquares[0].length / 2.0f;

    Mesh* gun2 = objects2D::CreateCenteredDiamond("gun2", corner, length, height, width, atackColors[1], true);
    AddMeshToList(gun2);

    guns[1].color = atackColors[1];
    guns[1].price = 2;
    guns[1].posX = gunSquares[1].posX + gunSquares[1].length / 2.0f;
    guns[1].posY = gunSquares[1].posY + gunSquares[1].length / 2.0f;

    Mesh* gun3 = objects2D::CreateCenteredDiamond("gun3", corner, length, height, width, atackColors[2], true);
    AddMeshToList(gun3);

    guns[2].color = atackColors[2];
    guns[2].price = 2;
    guns[2].posX = gunSquares[2].posX + gunSquares[2].length / 2.0f;
    guns[2].posY = gunSquares[2].posY + gunSquares[2].length / 2.0f;

    Mesh* gun4 = objects2D::CreateCenteredDiamond("gun4", corner, length, height, width, atackColors[3], true);
    AddMeshToList(gun4);

    guns[3].color = atackColors[3];
    guns[3].price = 3;
    guns[3].posX = gunSquares[3].posX + gunSquares[3].length / 2.0f;
    guns[3].posY = gunSquares[3].posY + gunSquares[3].length / 2.0f;

    // initializing the vector for the positions where the hexagons should appear
    hexagonsPosY = glm::vec3(playSquares[0].posY, playSquares[3].posY, playSquares[6].posY);

    // initializing the parameters for the hexagons
    sizeElements = 20;
    corner = glm::vec3(0, 0, 1);
    colorOfMiniHexagon = glm::vec3(0.9, 0.7, 0.6);

    // creating the meshes for the hexagons
    Mesh* hexagon1 = objects2D::CreateCenteredHexagon("hexagon1", corner, sizeElements, atackColors[0], colorOfMiniHexagon, true);
    AddMeshToList(hexagon1);

    Mesh* hexagon2 = objects2D::CreateCenteredHexagon("hexagon2", corner, sizeElements, atackColors[1], colorOfMiniHexagon, true);
    AddMeshToList(hexagon2);

    Mesh* hexagon3 = objects2D::CreateCenteredHexagon("hexagon3", corner, sizeElements, atackColors[2], colorOfMiniHexagon, true);
    AddMeshToList(hexagon3);

    Mesh* hexagon4 = objects2D::CreateCenteredHexagon("hexagon4", corner, sizeElements, atackColors[3], colorOfMiniHexagon, true);
    AddMeshToList(hexagon4);

    // calculating the positions for the costs of each gun
    costs[0].posX = gunSquares[0].posX + 15;
    costs[0].posY = gunSquares[0].posY - 15;

    for (int i = 1; i < 3; i++) {
        costs[i].posX = gunSquares[1].posX + (i - 1) * 30 + 15;
        costs[i].posY = gunSquares[1].posY - 15;
    }

    for (int i = 3; i < 5; i++) {
        costs[i].posX = gunSquares[2].posX + (i - 3) * 30 + 15;
        costs[i].posY = gunSquares[2].posY - 15;
    }

    for (int i = 5; i < 8; i++) {
        costs[i].posX = gunSquares[3].posX + (i - 5) * 30 + 15;
        costs[i].posY = gunSquares[3].posY - 15;
    }

    // setting the parameters for the little star
    corner = glm::vec3(0, 0, 0);
    sizeElements = 15;

    // creating the mesh for the little star
    Mesh* littleStar = objects2D::CreateCenteredStar("littleStar", corner, sizeElements, glm::vec3(0.9, 0.6, 0.7), true);
    AddMeshToList(littleStar);

    // setting the parameters for the stars we need to collect
    corner = glm::vec3(0, 0, 2);
    sizeElements = 25;

    // creating the mesh for the stars we have to collect
    Mesh* catchStar = objects2D::CreateCenteredStar("catchStar", corner, sizeElements, glm::vec3(0.9, 0.1, 0.3), true);
    AddMeshToList(catchStar);

    // setting the parameters for the projectiles we will throw
    corner = glm::vec3(0, 0, 5);
    sizeElements = 30;

    // creating the meshes for the projectiles
    Mesh* starProjectile1 = objects2D::CreateCenteredStar("starProjectile1", corner, sizeElements, atackColors[0], true);
    AddMeshToList(starProjectile1);

    Mesh* starProjectile2 = objects2D::CreateCenteredStar("starProjectile2", corner, sizeElements, atackColors[1], true);
    AddMeshToList(starProjectile2);

    Mesh* starProjectile3 = objects2D::CreateCenteredStar("starProjectile3", corner, sizeElements, atackColors[2], true);
    AddMeshToList(starProjectile3);

    Mesh* starProjectile4 = objects2D::CreateCenteredStar("starProjectile4", corner, sizeElements, atackColors[3], true);
    AddMeshToList(starProjectile4);
}

void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::RenderScene() {

}

void Tema1::Update(float deltaTimeSeconds)
{
    // starting to increase the timer with each update of the game
    timer += 1;

    // drawing the grid
    for (int i = 0; i < 9; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformers2D::Translate(playSquares[i].posX, playSquares[i].posY);

        RenderMesh2D(meshes["playSquareObj"], shaders["VertexColor"], modelMatrix);
    }

    // drawing the red rectangle
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformers2D::Translate(playSpacing, playSquares[3].posY);

    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);

    // drawing the squares where the guns will be displayed
    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformers2D::Translate(gunSquares[i].posX, gunSquares[i].posY);

        RenderMesh2D(meshes["gunSquareObj"], shaders["VertexColor"], modelMatrix);
    }

    // drawing the squares that tells us how many chances we have left
    for (int i = 0; i < chances; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformers2D::Translate(healthSquares[i].posX, healthSquares[i].posY);

        RenderMesh2D(meshes["healthSquareObj"], shaders["VertexColor"], modelMatrix);
    }

    // drawing the guns
    modelMatrix = glm::mat3(1);
    modelMatrix *= transformers2D::Translate(guns[0].posX, guns[0].posY);

    RenderMesh2D(meshes["gun1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformers2D::Translate(guns[1].posX, guns[1].posY);

    RenderMesh2D(meshes["gun2"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformers2D::Translate(guns[2].posX, guns[2].posY);

    RenderMesh2D(meshes["gun3"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transformers2D::Translate(guns[3].posX, guns[3].posY);

    RenderMesh2D(meshes["gun4"], shaders["VertexColor"], modelMatrix);

    // drawing the costs of each gun
    for (int i = 0; i < 8; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformers2D::Translate(costs[i].posX, costs[i].posY);

        RenderMesh2D(meshes["littleStar"], shaders["VertexColor"], modelMatrix);
    }

    // drawing the money we have
    for (int i = 0; i < money; i++) {
        // calculating the positions for each
        int x, y;

        x = healthSquares[0].posX - healthSquares[0].length / 2.0f + 30 * i + 15;
        y = healthSquares[0].posY - healthSquares[0].length / 2.0f - 15;

        modelMatrix = glm::mat3(1);
        modelMatrix *= transformers2D::Translate(x, y);

        RenderMesh2D(meshes["littleStar"], shaders["VertexColor"], modelMatrix);
    }

    // creating a new hexagon each time the timer hits 404
    if (timer % 404 == 0) {

        // initializing the hexagon
        hexagon new_hexagon;
        new_hexagon.posX = 1300;

        // picking a random position for the row
        new_hexagon.posY = hexagonsPosY[std::rand() % 3];
        new_hexagon.health = 3;

        // picking a random color
        new_hexagon.color = atackColors[std::rand() % 4];
        new_hexagon.deleteThis = false;
        new_hexagon.scaleX = 1;
        new_hexagon.scaleY = 1;

        // adding the new hexagon to the list of hexagons that attack
        hexagons.push_back(new_hexagon);
    }

    // going through the hexagons to move them across the game
    for (int i = 0; i < hexagons.size(); i++) {
        hexagons[i].posX -= 50 * deltaTimeSeconds;

        // checking if they reached the end of the line and losing a chance each time they do
        if (hexagons[i].posX <= 100.0f) {
            hexagons.erase(hexagons.begin() + i);
            chances -= 1;
        }

        // if we lost all of our chances the game closes
        if (chances == 0) {
            window->Close();
        }
    }

    // going through the hexagons to render them in the game
    for (const auto& hexagon : hexagons) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformers2D::Translate(hexagon.posX, hexagon.posY);

        // scaling them when we have to make them disappear
        modelMatrix *= transformers2D::Scale(hexagon.scaleX, hexagon.scaleY);

        if (hexagon.color == atackColors[0]) {
            RenderMesh2D(meshes["hexagon1"], shaders["VertexColor"], modelMatrix);

        }
        else if (hexagon.color == atackColors[1]) {
            RenderMesh2D(meshes["hexagon2"], shaders["VertexColor"], modelMatrix);

        }
        else if (hexagon.color == atackColors[2]) {
            RenderMesh2D(meshes["hexagon3"], shaders["VertexColor"], modelMatrix);

        }
        else if (hexagon.color == atackColors[3]) {
            RenderMesh2D(meshes["hexagon4"], shaders["VertexColor"], modelMatrix);

        }
    }

    // making the three stars we need to catch each time the timer hits 303
    if (timer % 303 == 0) {
        star new_star[3]{};

        for (int i = 0; i < 3; i++) {
            // placing the stars at random positions
            new_star[i].posX = rand() % 1200;
            new_star[i].posY = rand() % 610;

            // putting them in the list of stars
            starsToCatch.push_back(new_star[i]);
        }
    }

    // going through the stars that will be catched
    for (const auto& star : starsToCatch) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformers2D::Translate(star.posX, star.posY);

        RenderMesh2D(meshes["catchStar"], shaders["VertexColor"], modelMatrix);
    }

    // if we selected a gun we make it follow the cursor
    if (moveGun) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformers2D::Translate(gunInMotion.posX, gunInMotion.posY);

        if (gunInMotion.color == atackColors[0]) {
            RenderMesh2D(meshes["gun1"], shaders["VertexColor"], modelMatrix);

        }
        else if (gunInMotion.color == atackColors[1]) {
            RenderMesh2D(meshes["gun2"], shaders["VertexColor"], modelMatrix);

        }
        else if (gunInMotion.color == atackColors[2]) {
            RenderMesh2D(meshes["gun3"], shaders["VertexColor"], modelMatrix);

        }
        else if (gunInMotion.color == atackColors[3]) {
            RenderMesh2D(meshes["gun4"], shaders["VertexColor"], modelMatrix);

        }
    }

    // going through the guns we added to the grid
    for (const auto& gun : gunsAdded) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transformers2D::Translate(gun.posX, gun.posY);

        // scaling them in case they have to disappear
        modelMatrix *= transformers2D::Scale(gun.scaleX, gun.scaleY);

        if (gun.color == atackColors[0]) {
            RenderMesh2D(meshes["gun1"], shaders["VertexColor"], modelMatrix);

        }
        else if (gun.color == atackColors[1]) {
            RenderMesh2D(meshes["gun2"], shaders["VertexColor"], modelMatrix);

        }
        else if (gun.color == atackColors[2]) {
            RenderMesh2D(meshes["gun3"], shaders["VertexColor"], modelMatrix);

        }
        else if (gun.color == atackColors[3]) {
            RenderMesh2D(meshes["gun4"], shaders["VertexColor"], modelMatrix);

        }
    }

    // going through the guns in order to see if we have to throw stars at the hexagons
    for (auto& gun : gunsAdded) {
        gun.throwStars = false;

        // looking for a hexagon of its color and on its row
        for (auto& hexagon : hexagons) {
            if (gun.color == hexagon.color && gun.posY == hexagon.posY) {
                gun.throwStars = true;
                break;
            }
        }

        // if we found a hexagon we start throwing stars at him
        if (gun.throwStars) {
  
            // creating the first projectile of the diamond
            if (gun.starsProjectiles.size() == 0 && !gun.first) {
                gun.first = true;

                star starProjectile;
                starProjectile.color = gun.color;
                starProjectile.size = 40;
                starProjectile.posX = gun.posX;
                starProjectile.posY = gun.posY;
                starProjectile.angularStep = 0;
                starProjectile.deleteThis = false;

                gun.starsProjectiles.push_back(starProjectile);
            }
            // if its not the first projectile, but the array goes back to 0, it means the hexagon got too close
            // and we stop throwing stars
            else if (gun.starsProjectiles.size() == 0) {
                for (auto& hexagon : hexagons) {
                    if (gun.color == hexagon.color && gun.posY == hexagon.posY) {
                        if (calculateDistance(gun.posX, gun.posY, hexagon.posX, hexagon.posY) >= 150.0f) {
                       
                            star starProjectile;
                            starProjectile.color = gun.color;
                            starProjectile.size = 40;
                            starProjectile.posX = gun.posX;
                            starProjectile.posY = gun.posY;
                            starProjectile.angularStep = 0;
                            starProjectile.deleteThis = false;

                            gun.starsProjectiles.push_back(starProjectile);
                            break;
                        }
                    }
                }
            }
            // we check that the last projectile we threw got far enough so we can send the next one
            else {
                if (calculateDistance(gun.posX, gun.posY,
                    gun.starsProjectiles[gun.starsProjectiles.size() - 1].posX, gun.starsProjectiles[gun.starsProjectiles.size() - 1].posY) >= 150.0f) {

                    star starProjectile;
                    starProjectile.color = gun.color;
                    starProjectile.size = 40;
                    starProjectile.posX = gun.posX;
                    starProjectile.posY = gun.posY;
                    starProjectile.angularStep = 0;
                    starProjectile.deleteThis = false;

                    gun.starsProjectiles.push_back(starProjectile);
                }
            }
        }
    }
    
    // increasing the positon of the X in order to make the star go to the hexagon
    for (auto& gun : gunsAdded) {
        for (auto& star : gun.starsProjectiles) {
            star.posX += 50 * deltaTimeSeconds;
        }
    }

    // rendering the stars throwed by each gun if the gun has to throw them
    for (auto& gun : gunsAdded) {
        for (auto& star : gun.starsProjectiles) {

            if (gun.throwStars) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transformers2D::Translate(star.posX, star.posY);

                // rotating the star
                star.angularStep -= 5 * deltaTimeSeconds;
                modelMatrix *= transformers2D::Rotate(star.angularStep);

                if (star.color == atackColors[0]) {
                    RenderMesh2D(meshes["starProjectile1"], shaders["VertexColor"], modelMatrix);

                }
                else if (star.color == atackColors[1]) {
                    RenderMesh2D(meshes["starProjectile2"], shaders["VertexColor"], modelMatrix);

                }
                else if (star.color == atackColors[2]) {
                    RenderMesh2D(meshes["starProjectile3"], shaders["VertexColor"], modelMatrix);

                }
                else if (star.color == atackColors[3]) {
                    RenderMesh2D(meshes["starProjectile4"], shaders["VertexColor"], modelMatrix);

                }
            }
        }
    }

    // checking if we have to delete the projectiles and erasing them
    for (auto& gun : gunsAdded) {
        for (int i = 0; i < gun.starsProjectiles.size(); i++) {
            if (gun.starsProjectiles[i].deleteThis) {
                gun.starsProjectiles.erase(gun.starsProjectiles.begin() + i);
            }
        }
    }

    // going through each guns projectiles and checking if they hit the hexagons on their line and of the same color
    for (auto& gun : gunsAdded) {
        for (int j = 0; j < gun.starsProjectiles.size(); j++) {
            for (int i = 0; i < hexagons.size(); i++) {
                if (gun.starsProjectiles[j].color == hexagons[i].color && gun.starsProjectiles[j].posY == hexagons[i].posY) {

                    // calculating the distance between the 2 elements to decide their collision
                    if (calculateDistance(gun.starsProjectiles[j].posX, gun.starsProjectiles[j].posY, hexagons[i].posX, hexagons[i].posY)
                        <= gun.starsProjectiles[j].size + 20) {

                        // if they collide we take one from the hexagons health and delete the projectile
                        hexagons[i].health -= 1;
                        gun.starsProjectiles[j].deleteThis = true;

                        // if the hexagon doesn't have anymore health, we delete it and stop throwing stars
                        if (hexagons[i].health == 0) {
                            hexagons[i].deleteThis = true;
                            gun.throwStars = false;
                            break;
                        }
                    }
                }
            }
        }
    }

    // when the hexagons need to be deleted we scale them until they reach 0, and then delete them
    for (int i = 0; i < hexagons.size(); i++) {
        if (hexagons[i].deleteThis) {
            hexagons[i].scaleX -= 3.0 * deltaTimeSeconds;
            hexagons[i].scaleY -= 3.0 * deltaTimeSeconds;

            if (hexagons[i].scaleX <= 0) {
                hexagons.erase(hexagons.begin() + i);
            }
        }
    }

    // same for the guns
    for (int i = 0; i < gunsAdded.size(); i++) {
        if (gunsAdded[i].deleteThis) {
            gunsAdded[i].scaleX -= 3.0 * deltaTimeSeconds;
            gunsAdded[i].scaleY -= 3.0 * deltaTimeSeconds;

            if (gunsAdded[i].scaleX <= 0) {
                gunsAdded.erase(gunsAdded.begin() + i);
            }
        }
    }

    // if the guns collide with a hexagon, we delete the gun
    for (int i = 0; i < gunsAdded.size(); i++) {
        for (const auto& hexagon : hexagons) {
            if (gunsAdded[i].posY == hexagon.posY) {
                if (calculateDistance(gunsAdded[i].posX, gunsAdded[i].posY, hexagon.posX, hexagon.posY) <= 50.0f) {
                    gunsAdded[i].deleteThis = true;
                }
            }
        }
    }
}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{

}


void Tema1::OnKeyRelease(int key, int mods)
{

}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // if we are moving a gun, we set the guns positions where the cursor is
    if (moveGun) {
        gunInMotion.posX = mouseX;
        gunInMotion.posY = 720 - mouseY;
    }
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // if we click the left button of the mouse
    if (button == 1) {

        // we're checking if we're clicking on a star that we need to catch
        for (int i = 0; i < starsToCatch.size(); i++) {

            // calculating the distance between the cursor and each star
            if (calculateDistance(starsToCatch[i].posX, starsToCatch[i].posY, mouseX, 720 - mouseY) < 25) {
                // increasing the money once we click on a star and erasing it
                money += 1;
                starsToCatch.erase(starsToCatch.begin() + i);

            }
        }

        // checking if we have clicked on a gun in order to place her on the grid
        for (const auto& gun : guns) {
            if (calculateDistance(gun.posX, gun.posY, mouseX, 720 - mouseY) < 45) {
                // setting the motion variable on true so that we know we selected a gun
                moveGun = true;

                // saving the gun that is moving
                gunInMotion = gun;
            }
        }
    }

    // if we click on the right button of the mouse
    else if (button == 2) {

        // going through the guns added in the grid to check if we have clicked on one of them
        for (int i = 0; i < gunsAdded.size(); i++) {
            if (calculateDistance(gunsAdded[i].posX, gunsAdded[i].posY, mouseX, 720 - mouseY) < 45) {

                // going through the squares to see which one we have to set back to free
                for (auto& square : playSquares) {
                    if (gunsAdded[i].posX == square.posX && gunsAdded[i].posY == square.posY) {
                        square.isOccupied = false;
                    }
                }
                // deleting the gun
                gunsAdded[i].deleteThis = true;
            }
        }
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // if we have the gun in motion
    if (moveGun) {
        // we're going through the squares to verify if we have placed our gun in a play square
        for (auto& square : playSquares) {
            if (calculateDistance(gunInMotion.posX, gunInMotion.posY, square.posX, square.posY) < square.length / 2.0f) {

                // if the square isn't already occupied, we place our gun there if we have enough money for it
                if (!square.isOccupied) {
                    if (money >= gunInMotion.price) {
                        square.isOccupied = true;

                        gunInMotion.posX = square.posX;
                        gunInMotion.posY = square.posY;
                        gunInMotion.throwStars = false;
                        gunInMotion.deleteThis = false;
                        gunInMotion.scaleX = 1;
                        gunInMotion.scaleY = 1;
                        gunInMotion.first = false;

                        gunsAdded.push_back(gunInMotion);

                        money -= gunInMotion.price;
                    }
                }
            }
        }
        // we have placed the gun and release it from moving
        moveGun = false;
    }
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
