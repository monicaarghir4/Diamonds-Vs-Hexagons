#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace objects2D
{
    Mesh* CreateCenteredSquare(const std::string& name, glm::vec3 centeredPoint, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateNonCenteredSquare(const std::string& name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateCenteredDiamond(const std::string& name, glm::vec3 centeredPoint, float length, float height, float width, glm::vec3 color, bool fill = false);
    Mesh* CreateCenteredRectangle(const std::string& name, glm::vec3 centeredPoint, float height, float width, glm::vec3 color, bool fill = false);
    Mesh* CreateCenteredStar(const std::string& name, glm::vec3 centeredPoint, float size, glm::vec3 color, bool fill = false);
    Mesh* CreateCenteredHexagon(const std::string& name, glm::vec3 centeredPoint, float size, glm::vec3 colorBig, glm::vec3 colorLittle, bool fill = false);
}
