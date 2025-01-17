#include <rive/core/binary_reader.hpp>
#include <rive/file.hpp>
#include <rive/node.hpp>
#include <rive/bones/bone.hpp>
#include <rive/shapes/shape.hpp>
#include <rive/math/transform_components.hpp>
#include "no_op_renderer.hpp"
#include "rive_file_reader.hpp"
#include "rive_testing.hpp"
#include <cstdio>

TEST_CASE("scale constraint updates world transform", "[file]") {
    RiveFileReader reader("../../test/assets/scale_constraint.riv");

    auto artboard = reader.file()->artboard();

    REQUIRE(artboard->find<rive::TransformComponent>("target") != nullptr);
    auto target = artboard->find<rive::TransformComponent>("target");

    REQUIRE(artboard->find<rive::TransformComponent>("rect") != nullptr);
    auto rectangle = artboard->find<rive::TransformComponent>("rect");

    artboard->advance(0.0f);

    rive::TransformComponents targetComponents;
    rive::Mat2D::decompose(targetComponents, target->worldTransform());
    rive::TransformComponents rectComponents;
    rive::Mat2D::decompose(rectComponents, rectangle->worldTransform());

    REQUIRE(targetComponents.scaleX() == rectComponents.scaleX());
    REQUIRE(targetComponents.scaleY() == rectComponents.scaleY());
}
