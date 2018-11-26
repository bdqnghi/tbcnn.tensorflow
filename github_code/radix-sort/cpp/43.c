void radix_sort(std::vector<int>* array) {
  std::vector<std::vector<int>> buckets(0xf + 1);
  for (size_t byte = 0; byte < sizeof(int); ++byte) {
    unsigned int offset = byte * 4;
    unsigned int mask = 0xf << offset;
    for (auto& val: *array) {
      auto bucket = (mask & val) >> offset;
      buckets[bucket].push_back(val);
    }
    size_t index = 0;
    for (auto& bucket: buckets) {
      for (auto& val: bucket) {
        array->at(index++) = val;
      }
      bucket.clear();
    }
  }
}

