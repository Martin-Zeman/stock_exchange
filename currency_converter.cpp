#include "currency_converter.hpp"

namespace stock_exchange {

const CurrencyConverter::conversion_table_type
    CurrencyConverter::conversion_table{
        {{{1, 0.82, 21.47}}, {{1.22, 1, 26.13}}, {{0.047, 0.038, 1}}}};

double CurrencyConverter::Convert(double value, Currency from, Currency to) {
  return value * CurrencyConverter::conversion_table
                     [static_cast<conversion_table_type::size_type>(from)]
                     [static_cast<conversion_table_type::size_type>(to)];
}

} // namespace stock_exchange