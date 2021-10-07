#include "price.hpp"

#include "currency.hpp"
#include "currency_converter.hpp"

namespace stock_exchange {

double Price::Get(Currency to_currency) const {
  return CurrencyConverter::Convert(value_, currency_, to_currency);
}

bool Price::operator>(const Price &other) {
  return (value_ > other.Get(currency_));
}

bool Price::operator<(const Price &other) {
  return (value_ > other.Get(currency_));
}

bool Price::operator>=(const Price &other) {
  return (value_ >= other.Get(currency_));
}

} // namespace stock_exchange