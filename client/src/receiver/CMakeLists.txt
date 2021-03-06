add_executable(receiver
               main.cpp
               options.cpp
               options.hpp
               ../texture.cpp
               ../texture.hpp
               ../window.cpp
               ../window.hpp
               ../network/packet.cpp
               ../network/packet.hpp
               ../network/packet_parser.cpp
               ../network/packet_parser.hpp
               ../metrics.cpp
               ../metrics.hpp
               ../metrics_reporter.cpp
               ../metrics_reporter.hpp
               ../codecs/convert.cpp
               ../codecs/convert.hpp
               ../codecs/ffmpeg/decoder.cpp
               ../codecs/ffmpeg/decoder.hpp
               ../processors/packet_receiver.cpp
               ../processors/packet_receiver.hpp
               ../processors/h264decoder.cpp
               ../processors/h264decoder.hpp
               ../processors/display.cpp
               ../processors/display.hpp
               ../primitives/frame.cpp
               ../primitives/frame.hpp
               )

target_include_directories(receiver
                           PRIVATE ..
                           PRIVATE SYSTEM ${CONAN_INCLUDE_DIRS_GLFW}
                           PRIVATE SYSTEM ${CONAN_INCLUDE_DIRS_BOOST}
                           PRIVATE SYSTEM ${CONAN_INCLUDE_DIRS_SPDLOG}
                           )

target_link_libraries(receiver
                      ${OPENGL_gl_LIBRARY}
                      ${CONAN_LIBS_GLFW}
                      ${CONAN_LIBS_FFMPEG}
                      ${CONAN_LIBS_LIBX264}
                      ${CONAN_LIBS_BOOST}
                      ${CONAN_LIBS_FMT}
                      )

target_compile_options(receiver PRIVATE ${SHAR_COMPILE_OPTIONS})
target_compile_definitions(receiver PRIVATE ${SHAR_COMPILE_DEFINITIONS})
