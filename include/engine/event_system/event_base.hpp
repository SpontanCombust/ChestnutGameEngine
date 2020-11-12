#ifndef __CHESTNUT_EVENT_BASE_H__
#define __CHESTNUT_EVENT_BASE_H__

namespace chestnut
{
    typedef void event_function;

    struct SEvent
    {
        // put here whathever you want in child struct

        // provide overriden name for debugging
        virtual const char* getName() { return "SEvent"; }
        virtual ~SEvent() {}
    };

    // struct SBaseEventData
    // {
    //     std::string eventName;
    //     bool wasHandled;
    // };
    
    // struct STimerEventData : SBaseEventData
    // {
    //     uint32_t deltaTime;
    //     bool isRepeating;
    // };

    // enum class EButtonInputContext { PRESSED, RELEASED };
    // struct SKeyboardInputEventData : SBaseEventData
    // {
    //     SDL_Keycode key;
    //     EButtonInputContext inputContext;
    // };



    // enum class EEventDataType
    // {
    //     BASE,
    //     TIMER,
    //     INPUT_KEYBOARD
    // };

    // union UEventData
    // {
    //     SBaseEventData base;
    //     STimerEventData timer;
    // };



    // struct SEvent
    // {
    //     EEventDataType type;
    //     UEventData data;
    // };

} // namespace chestnut


#endif // __CHESTNUT_EVENT_BASE_H__