# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GCS_Sim")

# Include sub-projects.
#add_subdirectory ("GCS_Sim")

set(CMAKE_PREFIX_PATH "C:/Qt/6.11.2/msvc2022_64")

# Enable Qt automatic code generation
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Network
    OpenGL
    OpenGLWidgets
)

add_executable (GCS_Sim "src/GCS_Sim.cpp"
            "src/GCS_Sim.h"
            "src/presentation/MainWindow.h"
            "src/presentation/MainWindow.cpp")

target_link_libraries(GCS_Sim PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)
