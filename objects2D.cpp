#include "objects2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

// Creating a square where the starting point is the center of the square
Mesh* objects2D::CreateCenteredSquare(
    const std::string& name,
    glm::vec3 centeredPoint,
    float length,
    glm::vec3 color,
    bool fill)
{
    // adding the points used to draw the triangles
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(centeredPoint, color), //0
        VertexFormat(centeredPoint + glm::vec3(-length / 2.0f, -length / 2.0f, 0), color),   //1
        VertexFormat(centeredPoint + glm::vec3(length / 2.0f, -length / 2.0f, 0), color),   //2
        VertexFormat(centeredPoint + glm::vec3(length / 2.0f, length / 2.0f, 0), color),    //3
        VertexFormat(centeredPoint + glm::vec3(-length / 2.0f, length / 2.0f, 0), color)    //4

    };

    // setting the order for drawing the triangles 
    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,1
    };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        square->SetDrawMode(GL_TRIANGLES);
    }

    square->InitFromData(vertices, indices);
    return square;
}

// Creating a square where the starting point is the corner of the left bottom
Mesh* objects2D::CreateNonCenteredSquare(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}


// Creating the gun element by making a diamond shape with a rectangle attached
Mesh* objects2D::CreateCenteredDiamond(
    const std::string& name,
    glm::vec3 centeredPoint,
    float diagonalLength,
    float height,
    float width,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(centeredPoint, color), //0

        // the vertices of the diamond
        VertexFormat(centeredPoint + glm::vec3(0, -diagonalLength, 0), color),   //1
        VertexFormat(centeredPoint + glm::vec3(diagonalLength / 2.0f, 0, 0), color),   //2
        VertexFormat(centeredPoint + glm::vec3(0, diagonalLength, 0), color),    //3
        VertexFormat(centeredPoint + glm::vec3(-diagonalLength / 2.0f, 0, 0), color),    //4

        // the vertices of the rectangle
        VertexFormat(centeredPoint + glm::vec3(0, -height, 0), color),    //5
        VertexFormat(centeredPoint + glm::vec3(width, -height, 0), color),    //6
        VertexFormat(centeredPoint + glm::vec3(width, height, 0), color),    //7
        VertexFormat(centeredPoint + glm::vec3(0, height, 0), color)    //8
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,1,
        5,6,8,
        6,7,8
    };

    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        diamond->SetDrawMode(GL_TRIANGLES);
    }

    diamond->InitFromData(vertices, indices);
    return diamond;
}

// Creating a rectangle with its center in the middle of the rectangle
Mesh* objects2D::CreateCenteredRectangle(
    const std::string& name,
    glm::vec3 centeredPoint,
    float height,
    float width,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
         VertexFormat(centeredPoint, color), //0
         VertexFormat(centeredPoint + glm::vec3(-width / 2.0f, -height / 2.0f, 0), color),   //1
         VertexFormat(centeredPoint + glm::vec3(width / 2.0f, -height / 2.0f, 0), color),   //2
         VertexFormat(centeredPoint + glm::vec3(width / 2.0f, height / 2.0f, 0), color),    //3
         VertexFormat(centeredPoint + glm::vec3(-width / 2.0f, height / 2.0f, 0), color)    //4
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,1
    };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        rectangle->SetDrawMode(GL_TRIANGLES);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

// Creating a star shape with its center in the middle
Mesh* objects2D::CreateCenteredStar(
    const std::string& name,
    glm::vec3 centeredPoint,
    float size,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
         VertexFormat(centeredPoint, color), //0

         // the vertices of the star
         VertexFormat(centeredPoint + glm::vec3(-0.6f * size, -0.8 * size, 0), color),   //1
         VertexFormat(centeredPoint + glm::vec3(0.6f * size, -0.8 * size, 0), color),   //2
         VertexFormat(centeredPoint + glm::vec3(0.9f * size, 0.3f * size, 0), color),    //3
         VertexFormat(centeredPoint + glm::vec3(0, size, 0), color),    //4
         VertexFormat(centeredPoint + glm::vec3(-0.9f * size, 0.3f * size, 0), color),    //5

         // the vertices of the pentagon from inside the star
         VertexFormat(centeredPoint + glm::vec3(0, -0.3f * size, 0), color),    //6
         VertexFormat(centeredPoint + glm::vec3(0.3f * size, -0.1f * size, 0), color),    //7
         VertexFormat(centeredPoint + glm::vec3(0.2f * size, 0.3f * size, 0), color),    //8
         VertexFormat(centeredPoint + glm::vec3(-0.2f * size, 0.3f * size, 0), color),    //9
         VertexFormat(centeredPoint + glm::vec3(-0.3f * size, -0.1f * size, 0), color)    //10
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = {
        0,4,1,
        0,2,4,
        0,1,6,
        0,6,2,
        0,7,3, 
        0,3,8,
        0,9,5,
        0,5,10
    };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        star->SetDrawMode(GL_TRIANGLES);
    }

    star->InitFromData(vertices, indices);
    return star;
}

// Creating a big hexagon with a little one inside with its center in the middle
Mesh* objects2D::CreateCenteredHexagon(
    const std::string& name,
    glm::vec3 centeredPoint,
    float size,
    glm::vec3 colorBig,
    glm::vec3 colorLittle,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
         // little hexagon
         VertexFormat(centeredPoint, colorLittle), //0
         VertexFormat(centeredPoint + glm::vec3(-size / 2.0f, -1.7f * size / 2.0f, 0), colorLittle),   //1
         VertexFormat(centeredPoint + glm::vec3(size / 2.0f, -1.7f * size / 2.0f, 0), colorLittle),   //2
         VertexFormat(centeredPoint + glm::vec3(size, 0, 0), colorLittle),    //3
         VertexFormat(centeredPoint + glm::vec3(size / 2.0f, 1.7f * size / 2.0f, 0), colorLittle),    //4
         VertexFormat(centeredPoint + glm::vec3(-size / 2.0f, 1.7f * size / 2.0f, 0), colorLittle),    //5
         VertexFormat(centeredPoint + glm::vec3(-size, 0, 0), colorLittle),    //6

         // big hegaxon
         VertexFormat(centeredPoint, colorBig), //7
         VertexFormat(centeredPoint + glm::vec3(-size, -1.7f * size, 0), colorBig),   //8
         VertexFormat(centeredPoint + glm::vec3(size, -1.7f * size, 0), colorBig),   //9
         VertexFormat(centeredPoint + glm::vec3(size * 2, 0, 0), colorBig),    //10
         VertexFormat(centeredPoint + glm::vec3(size, 1.7f * size, 0), colorBig),    //11
         VertexFormat(centeredPoint + glm::vec3(-size, 1.7f * size, 0), colorBig),    //12
         VertexFormat(centeredPoint + glm::vec3(-size * 2, 0, 0), colorBig),    //13
    };

    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices = {
        // little hexagon
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,1,

        // big hexagon
        7,8,9,
        7,9,10,
        7,10,11,
        7,11,12,
        7,12,13,
        7,13,8
    };

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        hexagon->SetDrawMode(GL_TRIANGLES);
    }

    hexagon->InitFromData(vertices, indices);
    return hexagon;
}