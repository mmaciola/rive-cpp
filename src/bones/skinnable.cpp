#include "rive/bones/skinnable.hpp"
#include "rive/shapes/points_path.hpp"
#include "rive/shapes/mesh.hpp"

using namespace rive;

Skinnable* Skinnable::from(Component* component) {
    switch (component->coreType()) {
        case PointsPath::typeKey:
            return component->as<PointsPath>();
            break;
        case Mesh::typeKey:
            return component->as<Mesh>();
            break;
    }
    return nullptr;
}

void Skinnable::skin(Skin* skin) { m_Skin = skin; }