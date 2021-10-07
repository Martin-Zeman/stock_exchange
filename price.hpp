#ifndef PRICE_H
#define PRICE_H

#include "currency.hpp"
#include "currency_converter.hpp"

namespace stock_exchange {

class Price {

public:
  Price(double value, Currency currency = Currency::USD)
      : value_(value), currency_(currency) {}

  inline double Get() const { return value_; }
  double Get(Currency currency) const;

  bool operator>(const Price &other);
  bool operator<(const Price &other);
  bool operator>=(const Price &other);

private:
  Currency currency_;
  double value_;
};

} // namespace stock_exchange
#endif /* PRICE_H */
