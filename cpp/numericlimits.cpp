#include <limits>
#include <iostream>
#include <iomanip>
#include <string>

#define PRINT(T) print<T>(#T)
#define PUT(width, T, W) put(width, #W, std::numeric_limits<T>::W);
#define PUT_FUNC(width, T, W) put(width, #W, std::numeric_limits<T>::W());

bool print_header = true;

template<typename T> void put(int width, const char* header, T&& val)
{
  std::cout << std::setw(width);
  if (print_header) {
    std::cout << header;
  } else {
    std::cout << std::boolalpha << val;
  }
}

void put(int width, const char* header, char val) { put(width, header, int(val)); }
void put(int width, const char* header, signed char val) { put(width, header, int(val)); }
void put(int width, const char* header, unsigned char val) { put(width, header, int(val)); }
void put(int width, const char* header, wchar_t val) { put(width, header, int(val)); }

template<typename T> void print(const char* name)
{
  using namespace std::string_literals;
  put(20, "", name + ":"s);
  PUT_FUNC(22, T, min);
  PUT_FUNC(22, T, lowest);
  PUT_FUNC(22, T, max);
  PUT_FUNC(15, T, epsilon);
  PUT_FUNC(15, T, round_error);
  PUT_FUNC(15, T, infinity);
  PUT_FUNC(15, T, quiet_NaN);
  PUT_FUNC(15, T, signaling_NaN);
  PUT_FUNC(15, T, denorm_min);
  PUT(16, T, is_specialized);
  PUT(11, T, is_signed);
  PUT(12, T, is_integer);
  PUT(10, T, is_exact);
  PUT(14, T, has_infinity);
  PUT(15, T, has_quiet_NaN);
  PUT(19, T, has_signaling_NaN);
  PUT(12, T, has_denorm);
  PUT(17, T, has_denorm_loss);
  PUT(13, T, round_style);
  PUT(11, T, is_iec559);
  PUT(12, T, is_bounded);
  PUT(11, T, is_modulo);
  PUT( 8, T, digits);
  PUT(10, T, digits10);
  PUT( 7, T, radix);
  PUT(14, T, max_digits10);
  PUT(14, T, min_exponent);
  PUT(16, T, min_exponent10);
  PUT(14, T, max_exponent);
  PUT(16, T, max_exponent10);
  PUT( 7, T, traps);
  PUT(17, T, tinyness_before);

  std::cout << "\n";
}

int main()
{
  PRINT(int);
  print_header = false;

  PRINT(bool);
  PRINT(char);
  PRINT(signed char);
  PRINT(unsigned char);
  PRINT(wchar_t);
  PRINT(short);
  PRINT(unsigned short);
  PRINT(int);
  PRINT(unsigned int);
  PRINT(long);
  PRINT(unsigned long);
  PRINT(long long);
  PRINT(unsigned long long);
  PRINT(float);
  PRINT(double);
  PRINT(long double);
  // PRINT(char8_t);    // C++20 feature
  PRINT(char16_t);   // C++11 feature
  PRINT(char32_t);   // C++11 feature
}