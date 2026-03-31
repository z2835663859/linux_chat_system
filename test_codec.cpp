#include "im_protocol.hpp"
#include <cstdio>
#include <vector>

int main() {
  im::Packet a{ (uint16_t)im::MsgType::CHAT, R"({"text":"hello"})" };
  im::Packet b{ (uint16_t)im::MsgType::CHAT, R"({"text":"world"})" };

  auto ba = im::Codec::encode(a);
  auto bb = im::Codec::encode(b);

  // 模拟“粘包”：两个包直接拼一起
  std::vector<uint8_t> stream;
  stream.insert(stream.end(), ba.begin(), ba.end());
  stream.insert(stream.end(), bb.begin(), bb.end());

  // 模拟“半包”：把 stream 切碎喂进去
  im::ByteBuffer buf;
  im::Packet out;

  size_t i = 0;
  std::vector<size_t> chunks = {3, 2, 7, 1, 100}; // 故意乱切
  size_t ci = 0;

  int decoded = 0;
  while (i < stream.size()) {
    size_t take = chunks[ci++ % chunks.size()];
    if (i + take > stream.size()) take = stream.size() - i;

    buf.append(stream.data() + i, take);
    i += take;

    while (im::Codec::try_decode(buf, out)) {
      decoded++;
      std::printf("decoded #%d type=%u body=%s\n", decoded, out.type, out.body.c_str());
    }
  }

  return 0;
}