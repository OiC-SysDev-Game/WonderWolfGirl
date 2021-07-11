#ifndef U22_GRAPHICS_VERTEX_H
#define U22_GRAPHICS_VERTEX_H


#include <vector>

#include "../Common/Common.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"


namespace u22::graphics {
struct ColorVertex {
    //! à íu
    u22::math::Vector3F position;
    //! êF
    u22::math::Vector4F color;
};
struct SpriteVertex {
    //! à íu
    u22::math::Vector3F position;
    //! UV
    u22::math::Vector2F texcoord;
};

static std::vector<SpriteVertex> kSpriteVertices = {
    {glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 0.0f)}, // top left
    {glm::vec3(-0.5f,-0.5f, 0.0f), glm::vec2(0.0f, 1.0f)}, // bottom left
    {glm::vec3( 0.5f,-0.5f, 0.0f), glm::vec2(1.0f, 1.0f)}, // bottom right
    {glm::vec3( 0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 0.0f)}, // top right
};
static std::vector<std::uint32_t> kSpriteIndices = {
    0, 1, 2 , 2, 3, 0
};
}
#endif // !U22_GRAPHICS_VERTEX_H