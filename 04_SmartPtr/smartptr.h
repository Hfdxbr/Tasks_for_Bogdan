#include <string>

template <class T>
class UniquePtr {
 private:
  /* data */
 public:
  UniquePtr();                                 // Default constructor
  UniquePtr(T* ptr);                           // Capture pointer constructor
  UniquePtr(const UniquePtr& other) = delete;  // Copy constructor not exist
  UniquePtr(UniquePtr&& other);                // Move constructor
  ~UniquePtr();

  class Exception;

  bool operator==(const UniquePtr& other) const;
  bool operator!=(const UniquePtr& other) const;

  T& operator*() const;
  T* operator->() const;

  UniquePtr& operator=(const UniquePtr& other) = delete;
  UniquePtr& operator=(UniquePtr&& other);

  void Swap(UniquePtr& other);
  T* Get() const;
  T* Release();
  void Reset();
};

template <class T>
class UniquePtr<T>::Exception {
 public:
  enum class ErrorCode {
    NO_ERROR,
    /* Errors */
  };

 private:
  ErrorCode code;
  std::string msg;

 public:
  Exception(ErrorCode err_code, std::string err_msg);
  std::string what() { return msg; }
};

template <class T>
class SharedPtr {
 private:
  /* data */
 public:
  SharedPtr();                        // Default constructor
  SharedPtr(T* ptr);                  // Capture pointer constructor
  SharedPtr(const SharedPtr& other);  // Copy constructor
  SharedPtr(SharedPtr&& other);       // Move constructor
  ~SharedPtr();

  class Exception;

  bool operator==(const SharedPtr& other) const;
  bool operator!=(const SharedPtr& other) const;

  T& operator*() const;
  T* operator->() const;

  SharedPtr& operator=(const SharedPtr& other);
  SharedPtr& operator=(SharedPtr&& other);

  void Swap(SharedPtr& other);
  T* Get() const;
  size_t Count() const;  // Returns number of SharedPtrs with the same object
  void Reset();
};

template <class T>
class SharedPtr<T>::Exception {
 public:
  enum class ErrorCode {
    NO_ERROR,
    /* Errors */
  };

 private:
  ErrorCode code;
  std::string msg;

 public:
  Exception(ErrorCode err_code, std::string err_msg);
  std::string what() { return msg; }
};