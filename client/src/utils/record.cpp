#include <chrono>
#include <thread>

#include "runner.hpp"
#include "signal_handler.hpp"
#include "channels/bounded.hpp"
#include "processors/screen_capture.hpp"
#include "processors/frame_file_writer.hpp"


int main() {
  auto logger  = shar::Logger("record.log");

  if (!shar::SignalHandler::setup()) {
    logger.error("Failed to register signal handler");
    return EXIT_FAILURE;
  }

  auto[frames_sender, frames_receiver] = shar::channel::bounded<shar::Frame>(120);
  auto metrics = std::make_shared<shar::Metrics>(20, logger);

  auto context = shar::ProcessorContext {
      "",
      logger,
      metrics
  };

  using namespace std::chrono_literals;
  std::size_t fps      = 30;
  auto        interval = 1000ms / fps;
  sc::Monitor monitor  = sc::GetMonitors().front();

  auto capture = std::make_shared<shar::ScreenCapture>(
      context.with_name("Capture"),
      interval,
      monitor,
      std::move(frames_sender)
  );
  auto writer  = std::make_shared<shar::FrameFileWriter>(
      context.with_name("FileWriter"),
      "example.bgra",
      std::move(frames_receiver)
  );

  shar::Runner capture_runner {std::move(capture)};
  shar::Runner writer_runner {std::move(writer)};

  shar::SignalHandler::wait_for_sigint();
  capture_runner.stop();

  return EXIT_SUCCESS;
}