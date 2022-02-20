#ifndef _RIVE_RAW_PATH_HPP_
#define _RIVE_RAW_PATH_HPP_

#include "rive/span.hpp"
#include "rive/math/aabb.hpp"
#include "rive/math/mat2d.hpp"
#include "rive/math/vec2d.hpp"

#include <cmath>
#include <stdio.h>
#include <cstdint>
#include <vector>

namespace rive {

enum class PathDirection {
    cw,
    ccw,
    // aliases
    clockwise = cw,
    counterclockwise = ccw,
};

enum class PathVerb : uint8_t {
    move,
    line,
    quad,
    cubic,
    close,
};

class RawPath {
public:
    std::vector<Vec2D> m_Points;
    std::vector<PathVerb> m_Verbs;
    
    RawPath() {}
    ~RawPath() {}

    bool empty() const { return m_Points.empty(); }
    AABB bounds() const;

    void moveTo(Vec2D);
    void lineTo(Vec2D);
    void quadTo(Vec2D, Vec2D);
    void cubicTo(Vec2D, Vec2D, Vec2D);
    void close();
    
    RawPath transform(const Mat2D&) const;
    void transformInPlace(const Mat2D&);
    
    Span<const Vec2D> points() const { return toSpan(m_Points); }
    Span<Vec2D> points() { return toSpan(m_Points); }

    Span<const PathVerb> verbs() const { return toSpan(m_Verbs); }
    Span<PathVerb> verbs() { return toSpan(m_Verbs); }

    // Helpers for adding new contours

    void addRect(const AABB&, PathDirection = PathDirection::cw);
    void addOval(const AABB&, PathDirection = PathDirection::cw);
    void addPoly(const Vec2D[], int count, bool isClosed);

    // Syntactic sugar for x,y -vs- vec2d

    void moveTo(float x, float y) { moveTo({x, y}); }
    void lineTo(float x, float y) { lineTo({x, y}); }
    void quadTo(float x, float y, float x1, float y1) {
        quadTo({x, y}, {x1, y1});
    }
    void cubicTo(float x, float y, float x1, float y1, float x2, float y2) {
        cubicTo({x, y}, {x1, y1}, {x2, y2});
    }
};

} // namespace rive

#endif
