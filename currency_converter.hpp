#ifndef CURRENCY_CONVERTER_H
#define CURRENCY_CONVERTER_H

#include "currency.hpp"
#include <array>
#include <cstdint>

namespace stock_exchange {

class CurrencyConverter {

  using conversion_table_type = std::array<std::array<double, 3>, 3>;

  static const conversion_table_type conversion_table;

public:
  static double Convert(double value, Currency from, Currency to);
};

} // namespace stock_exchange

#endif /* CURRENCY_CONVERTER_H */
