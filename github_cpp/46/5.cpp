template<typename T, typename FnT>
class SegmentTree {
  public:
    explicit SegmentTree(FnT const &app, T const &un, size_t size):
      SegmentTree(app, un, std::vector<T>(size, un)) {
    }
    explicit SegmentTree(FnT const &app, T const &un, std::vector<T> const &v):
      append(app), unit(un), N(1 << log2(v.size())), dat(2*N-1) {
      std::copy(begin(v), end(v), begin(dat)+N-1);
      for (size_t k = N - 1; k > 0; --k) {
        dat[k-1] = append(dat[2*k-1], dat[2*k]);
      }
    }
    void update(size_t k, T x) {
      k += N - 1;
      dat[k] = x;
      while (k > 0) {
        k = (k - 1) / 2;
        dat[k] = append(dat[2*k+1], dat[2*k+2]);
      }
    }
    T at(size_t k) const {
      return dat[k+N-1];
    }
    T query(size_t a, size_t b, size_t k, size_t l, size_t r) const {
      if (r <= a || b <= l) { return unit; }
      if (a <= l && r <= b) { return dat[k]; }
      const auto mid = (l + r) / 2;
      const auto vl = query(a, b, 2*k+1, l, mid);
      const auto vr = query(a, b, 2*k+2, mid, r);
      return append(vl, vr);
    }
    T query(size_t a, size_t b) const {
      return query(a, std::min(b, N), 0, 0, N);
    }
    T query() const {
      return query(0, N, 0, 0, N);
    }
  private:
    FnT const append;
    T const unit;
    size_t const N;
    std::vector<T> dat;

    static size_t log2(size_t n) {
      size_t p = 1;
      while ((1 << p) < n) { ++p; }
      return p;
    }
};
