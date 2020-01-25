#include <string>

class Fraction {
 private:
  /* data */
 public:
  Fraction();                                // Default constructor
  Fraction(int numerator, int denominator);  // Num/Denom constructor
  Fraction(int value);                       // Int value constructor
  Fraction(double value);                    // Double value constructor
  Fraction(const Fraction& other);           // Copy constructor
  ~Fraction();

  class Exception;

  bool operator<(const Fraction& other) const;
  bool operator<=(const Fraction& other) const;
  bool operator==(const Fraction& other) const;
  bool operator!=(const Fraction& other) const;
  bool operator>(const Fraction& other) const;
  bool operator>=(const Fraction& other) const;

  Fraction operator+(const Fraction& other) const;
  Fraction operator-(const Fraction& other) const;
  Fraction& operator+=(const Fraction& other);
  Fraction& operator-=(const Fraction& other);
  Fraction operator-() const;  // Unary minus

  Fraction operator*(const Fraction& other) const;
  Fraction operator/(const Fraction& other) const;
  Fraction& operator*=(const Fraction& other);
  Fraction& operator/=(const Fraction& other);

  Fraction& operator=(const Fraction& other);

  friend std::ostream& operator<<(std::ostream& os, const Fraction& number);
};

class Fraction::Exception {
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