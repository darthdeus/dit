#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <vector>

class Buffer {
 public:
  std::vector<std::string> lines;
  size_t x = 0;
  size_t y = 0;
};

#endif /* BUFFER_H */
