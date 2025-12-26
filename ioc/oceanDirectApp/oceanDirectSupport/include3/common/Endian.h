#ifndef OCEANENDIANCHECKER_H
#define OCEANENDIANCHECKER_H
#include <cstdint>
#include <vector>
namespace oceandirect {
    // Return true if the computer stores integer values in big endian format
    bool IsBigEndian();
    std::vector<std::uint8_t> ToNetworkByteOrder(const std::uint32_t networkAddress);
    std::uint32_t FromNetworkByteOrder(const uint8_t addressAsBytes[4]);
}
#endif // !OCEANENDIANCHECKER_H

