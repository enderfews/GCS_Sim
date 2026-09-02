# Ground Control Station simulator
Qt6/C++ Ground Control Simulator — portfolio project built in preparation for Indra's GCS UAV program

## Tech stack

- C++17
- Qt6 (Widgets, Network, OpenGL, OpenGLWidgets)
- CMake
- Git / GitHub / Fork

## Arquitecture design

GCS is implemented by following the hexagonal architecture. All base entities, interfaces (aka ports), events, etc, are in the "domain" folder, which contains the core. Following the next layer, we have the "application" folder, which contains the use cases. Each use case, represented in classes (Ex: TelemetryService), uses the different ports defined in the domain or core of the application. Then we have the "Infrastructure" folder, where we can find the implementations (aka adapters) of the ports. The "presentation" folder contains the Qt application and their implementations. When the Qt app uses the services defined, It provides the specific adapters or implementations by templated functions, so that we can change the implementations on demand. We can implement options in the GUI or presentation layer to change which adapters the services & repositories use on demand.

## Test infrastructure

In order to test we get the telemetry, we've defined tools in the "tools" folders. For now, we have a python script which sends the data to the localhost, so we can test the program It's receiving and processing the data. The next step will be implementing a tool to send datagrams from a different system.
