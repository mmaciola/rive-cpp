#include <rive/core/binary_reader.hpp>
#include <rive/file.hpp>
#include <rive/node.hpp>
#include <rive/shapes/clipping_shape.hpp>
#include <rive/shapes/rectangle.hpp>
#include <rive/shapes/shape.hpp>
#include "no_op_renderer.hpp"
#include <catch.hpp>
#include <cstdio>

TEST_CASE("cloning an ellipse works", "[instancing]") {
    FILE* fp = fopen("../../test/assets/circle_clips.riv", "rb");
    REQUIRE(fp != nullptr);

    fseek(fp, 0, SEEK_END);
    const size_t length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    uint8_t* bytes = new uint8_t[length];
    REQUIRE(fread(bytes, 1, length, fp) == length);
    auto reader = rive::BinaryReader(bytes, length);
    auto file = rive::File::import(reader);

    REQUIRE(file != nullptr);
    REQUIRE(file->artboard() != nullptr);

    auto node = file->artboard()->find<rive::Shape>("TopEllipse");
    REQUIRE(node != nullptr);

    auto clonedNode = node->clone()->as<rive::Shape>();
    REQUIRE(node->x() == clonedNode->x());
    REQUIRE(node->y() == clonedNode->y());

    delete clonedNode;
    delete[] bytes;
}

TEST_CASE("instancing artboard clones clipped properties", "[instancing]") {
    FILE* fp = fopen("../../test/assets/circle_clips.riv", "rb");
    REQUIRE(fp != nullptr);

    fseek(fp, 0, SEEK_END);
    const size_t length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    uint8_t* bytes = new uint8_t[length];
    REQUIRE(fread(bytes, 1, length, fp) == length);
    auto reader = rive::BinaryReader(bytes, length);
    auto file = rive::File::import(reader);

    REQUIRE(file != nullptr);
    REQUIRE(file->artboard() != nullptr);
    REQUIRE(!file->artboard()->isInstance());

    auto artboard = file->artboardDefault();

    REQUIRE(artboard->isInstance());

    auto node = artboard->find("TopEllipse");
    REQUIRE(node != nullptr);
    REQUIRE(node->is<rive::Shape>());

    auto shape = node->as<rive::Shape>();
    REQUIRE(shape->clippingShapes().size() == 2);
    REQUIRE(shape->clippingShapes()[0]->source()->name() == "ClipRect2");
    REQUIRE(shape->clippingShapes()[1]->source()->name() == "BabyEllipse");

    artboard->updateComponents();

    rive::NoOpRenderer renderer;
    artboard->draw(&renderer);

    delete[] bytes;
}

TEST_CASE("instancing artboard doesn't clone animations", "[instancing]") {
    FILE* fp = fopen("../../test/assets/juice.riv", "rb");
    REQUIRE(fp != nullptr);

    fseek(fp, 0, SEEK_END);
    const size_t length = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    uint8_t* bytes = new uint8_t[length];
    REQUIRE(fread(bytes, 1, length, fp) == length);
    auto reader = rive::BinaryReader(bytes, length);
    auto file = rive::File::import(reader);

    REQUIRE(file != nullptr);
    REQUIRE(file->artboard() != nullptr);

    auto artboard = file->artboardDefault();

    REQUIRE(file->artboard()->animationCount() == artboard->animationCount());
    REQUIRE(file->artboard()->firstAnimation() == artboard->firstAnimation());

    rive::LinearAnimation::deleteCount = 0;
    // Make sure no animations were deleted by deleting the instance.
    REQUIRE(rive::LinearAnimation::deleteCount == 0);

    int numberOfAnimations = file->artboard()->animationCount();
    file.reset(nullptr);
    // Now the animations should've been deleted.
    REQUIRE(rive::LinearAnimation::deleteCount == numberOfAnimations);

    delete[] bytes;
}
