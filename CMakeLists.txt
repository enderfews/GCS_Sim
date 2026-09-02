# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Define the project name.
project ("GCS_Sim")

# Tell CMake where the Qt installation is located.
# This allows find_package() to locate the Qt installation
# without requiring Qt to be added to the global PATH.
#TODO: Change this so that we don't have to provide a hardcoded path
set(CMAKE_PREFIX_PATH "C:/Qt/6.11.2/msvc2022_64")

# Enable Qt automatic code generation
# AUTOMOC: handles signals and slots (Q_OBJECT macro).
set(CMAKE_AUTOMOC ON)
# AUTOUIC: handles .ui files (visual forms made in Qt Designer).
set(CMAKE_AUTOUIC ON)
# AUTORCC: handles .qrc files (resources, like icons or images).
set(CMAKE_AUTORCC ON)

# Find the Qt6 modules required by the application.
# REQUIRED means that CMake will stop with an error if
# any of these modules cannot be found.
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Network
    OpenGL
    OpenGLWidgets
)

# Automatically find all .cpp files inside the src directory
# and its subdirectories.
#
# Example:
#
# src/GCS_Sim.cpp
# src/application/TelemetryService.cpp
# src/domain/TelemetryInput.cpp
# src/infrastructure/Qt/QtUdpTelemetryInput.cpp
# src/presentation/MainWindow.cpp
#
# will all be included automatically.
# CONFIGURE_DEPENDS allows us to configure the project automatically IF we add new files
file(GLOB_RECURSE SOURCES
    CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Automatically find all .h files inside the src directory
# and its subdirectories.
#
# Header files are not strictly required here for compilation,
# but including them makes them visible in IDEs such as
# Visual Studio.
# CONFIGURE_DEPENDS allows us to configure the project automatically IF we add new files
file(GLOB_RECURSE HEADERS
    CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.h
)

# Create the GCS_Sim executable using all discovered
# source and header files.
add_executable(GCS_Sim
    ${SOURCES}
    ${HEADERS}
)

# Add the src directory to the compiler's include paths.
#
# This allows includes such as:
#
#     #include "domain/UAVTypes.h"
#     #include "application/TelemetryService.h"
#     #include "presentation/MainWindow.h"
#
# instead of using relative paths such as:
#
#     #include "../../domain/UAVTypes.h"
#
target_include_directories(GCS_Sim
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

# Link the Qt modules required by the application.
#
# Core          -> Qt basic functionality, QObject, containers, etc.
# Widgets       -> QWidget, QMainWindow, layouts, labels, etc.
# Network       -> QUdpSocket, QNetworkDatagram, etc.
# OpenGL        -> OpenGL integration.
# OpenGLWidgets -> QOpenGLWidget.
target_link_libraries(GCS_Sim PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)
