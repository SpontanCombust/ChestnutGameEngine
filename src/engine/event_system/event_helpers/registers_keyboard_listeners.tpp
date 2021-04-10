namespace chestnut
{    
    template< class T >
    listenerid_t CRegistersKeyboardListeners::registerKeyboardListener( event_function ( T::*membFunc )( const SKeyboardEvent& ),
                                                                        SDL_Keycode button, 
                                                                        bool checkIfPressedDown, 
                                                                        bool shouldBePressedDown, 
                                                                        bool checkModifiers, 
                                                                        uint16_t modifiers )
    {
        listenerid_t id = m_eventManagerRef.registerListener( ( T* )this, membFunc );
        m_eventManagerRef.constrainListenerByID( id, keyboardEventConstraintFunc( button, checkIfPressedDown, shouldBePressedDown, checkModifiers, modifiers ) );

        m_vecListeners.push_back( id );

        return id;
    }

} // namespace chestnut
