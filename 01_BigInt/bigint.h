#include <list>
#include <string>

class BigInt {
 private:
  std::list<int> number;
  int base_size = 9;
  int max_number = 1000000000;

 public:
  BigInt();                     // Default constructor
  BigInt(int value);            // Int constructor
  BigInt(std::string value);    // String constructor
  BigInt(const BigInt& other);  // Copy constructor
  ~BigInt();

  class Exception;

  bool operator<(const BigInt& other) const;
  bool operator<=(const BigInt& other) const;
  bool operator==(const BigInt& other) const;
  bool operator!=(const BigInt& other) const;
  bool operator>(const BigInt& other) const;
  bool operator>=(const BigInt& other) const;

  BigInt operator+(const BigInt& other) const;
  BigInt operator-(const BigInt& other) const;
  BigInt& operator+=(const BigInt& other);
  BigInt& operator-=(const BigInt& other);
  BigInt operator-() const;  // Unary minus

  BigInt& operator++();    // Prefix increment
  BigInt operator++(int);  // Postfix increment
  BigInt& operator--();
  BigInt operator--(int);

  BigInt& operator=(const BigInt& other);

  friend std::ostream& operator<<(std::ostream& os, const BigInt& number);
};

class BigInt::Exception {
 public:
  enum class ErrorCode { NO_ERROR, WRONG_INPUT };

 private:
  ErrorCode code;
  std::string msg;

 public:
  Exception(ErrorCode err_code, std::string err_msg)
      : code(err_code), msg(err_msg) {}
  std::string what() { return msg; }
  ErrorCode status() { return code; }
};