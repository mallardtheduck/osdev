#ifndef UTIL_NONCOPYABLE
#define UTIL_NONCOPYABLE

class noncopyable {
protected:
  noncopyable() = default;
  ~noncopyable() = default;

  noncopyable(noncopyable const &) = delete;
  noncopyable &operator=(noncopyable const &) = delete;
};

class nonmovable : public noncopyable {
protected:
  nonmovable() = default;
  ~nonmovable() = default;

  nonmovable(nonmovable &&) = delete;
  nonmovable &operator=(nonmovable &&) = delete;
};

#endif