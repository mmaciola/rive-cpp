#ifndef _RIVE_PLAYABLE_HPP_
#define _RIVE_PLAYABLE_HPP_

#include "rive/animation/linear_animation.hpp"
#include "rive/animation/state_machine.hpp"
#include "rive/core_context.hpp"
#include "rive/generated/artboard_base.hpp"
#include "rive/hit_info.hpp"
#include "rive/message.hpp"
#include "rive/pointer_event.hpp"
#include "rive/math/aabb.hpp"
#include "rive/renderer.hpp"
#include "rive/shapes/shape_paint_container.hpp"

#include <queue>
#include <vector>

namespace rive {

    class Playable {
    private:

    public:
        ~Playable();

        // Information about the Playable
    
        std::string name() const;
        Vec2D dimensions() const;
        double durationSeconds() const;  // returns -1 for continuous

        // Animating and drawing the Playable

        bool advance(double elapsedSeconds);    // returns true if draw() should be called
        void draw(Renderer*);

        // Forwarding events to the Playable
        // - pointer(s)
        // - key(s) (in the future)
    
        enum class PointerState {
            kDown,      // pointer changed from 'up' to 'down'
            kUp,        // pointer changed from 'down' to 'up'
            kMoved,     // pointer position changed
        };
        void pointerEvent(Vec2D, PointerState);

        // Receiving messages from the Playable

        bool hasMessages() const;
        std::unique_ptr<Message> nextMessage();
    };

} // namespace rive

#endif
