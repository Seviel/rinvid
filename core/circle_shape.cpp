#include <algorithm>
#include <cmath>

#include "core/include/rinvid_gfx.h"
#include "include/circle_shape.h"
#include "util/include/math_utils.h"
#include "util/include/vector3.h"

#define GL_GLEXT_PROTOTYPES

#include <SFML/OpenGL.hpp>

namespace rinvid
{

CircleShape::CircleShape(Vector2 center, float radius)
{
    float angle{};
    for (std::uint32_t i{0}; i < number_of_vertices_; ++i)
    {
        angle        = i * (DEGREES_IN_A_CIRCLE / number_of_vertices_);
        verts_.at(i) = Vector2{center.x + std::cos(DEGREES_TO_RADIANS(angle)) * radius,
                               center.y + std::sin(DEGREES_TO_RADIANS(angle)) * radius};
    }
}

void CircleShape::draw()
{
    FixedPolygonShape::draw();
    draw_arrays(GL_POLYGON);
}

} // namespace rinvid
