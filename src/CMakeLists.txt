#########################################################################
### Qt 5 settings
if(WITH_QT)
    list(APPEND CMAKE_PREFIX_PATH ${BASE_DIR_QT5})
    include_directories(${BASE_DIR_QT5}/include)

    # Qt code generation settings
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)

    find_package(Qt5Core REQUIRED)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Gui REQUIRED)

    # Define Qt Libs
    set(QT_LIBS Qt5::Core)
    set(QT_LIBS ${QT_LIBS} Qt5::Widgets Qt5::Gui)
endif(WITH_QT)

#########################################################################
### Subdirectories
# 3rd party libraries
add_subdirectory(3rdparty)

# Snake game
add_subdirectory(snake)
include_directories(snake)

# RL - Q-learning
add_subdirectory(RL)
include_directories(RL)

# Add gui
if(WITH_QT)
    add_subdirectory(gui)
    include_directories(gui)
endif(WITH_QT)

#########################################################################
### CMake options
# Set c++ defines from cmake options
configure_file(config.h.in ../config.h)
include_directories(${PROJECT_BINARY_DIR})

#########################################################################
### Compilation settings
# Normal snake game
add_executable(Snake
    main.cpp

    # Snake Engine
    snake/snakeengine.cpp
)

if(WITH_QT)
    target_link_libraries(Snake ${QT_LIBS})
    target_link_libraries(Snake ${PROJECT_NAME}_gui)
endif(WITH_QT)

if(WITH_OPENCV)
    target_link_libraries(Snake ${OpenCV_LIBS})
endif(WITH_OPENCV)

# RL engine
if(WITH_RL)
    add_executable(SnakeRL
        RL/main.cpp

        # Snake Engine
        snake/snakeengine.cpp

        # Reinforcement Learning
        RL/agent.cpp
        RL/action.cpp
        RL/snakeactions.cpp
        RL/learningmethod.cpp
    )

    if(WITH_QT)
        target_link_libraries(SnakeRL ${QT_LIBS})
        target_link_libraries(SnakeRL ${PROJECT_NAME}_gui)
    endif(WITH_QT)

    if(WITH_OPENCV)
        target_link_libraries(SnakeRL ${OpenCV_LIBS})
    endif(WITH_OPENCV)
endif(WITH_RL)

