#pragma once

#include <cstdint>
#include <vector>

#include "disable_warnings_push.hpp"
#include "wels/codec_api.h"
#include "disable_warnings_pop.hpp"

#include "packet.hpp"
#include "primitives/image.hpp"

namespace shar::codecs::h264 {
  
class Encoder {
public:
  Encoder(Size frame_size, std::size_t bitrate);
  Encoder(const Encoder&) = delete;
  Encoder(Encoder &&) = delete; // TODO: implement
  ~Encoder();

  std::vector<Packet> encode(const Image& image);

private:
  SEncParamBase m_params;
  ISVCEncoder*  m_encoder;
  size_t m_frame_ind;
};

}