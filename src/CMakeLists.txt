set(SOURCES main.cpp
            input_dispatcher.cpp
            input_receiver.cpp
            factory.cpp
            game_object.cpp
            component.cpp
            graphics_component.cpp
            update_component.cpp
            sound_engine.cpp
)

add_library(main_obj OBJECT ${SOURCES})