#ifndef ORDER_H
#define ORDER_H

#include "item.hpp"
#include "price.hpp"

#include <memory>

namespace stock_exchange {

/**
 * @brief Pure virtual class. Represents a generic order to be inherited from
 *
 */
class Order {

public:
  /**
   * @brief Construct a new Order object
   *
   * @param price - price for which the item is to be sold or bought
   * @param cycle_limit - maximum cycle duration of the order
   */
  Order(const Price &price, std::uint8_t cycle_limit)
      : price_(price), cycles_remaining_(cycle_limit) {}

  /**
   * @brief Get the price of the Order
   *
   * @return Price
   */
  inline Price GetOrderPrice() const { return price_; }

  /**
   * @brief Returns true if the order is still valid
   *
   * @return true if the order is stil valid
   * @return false if the order has already expired
   */
  inline bool IsStillValid() const { return cycles_remaining_ > 0; }

  /**
   * @brief Set the order as closed (either bought or sold)
   *
   */
  inline void SetAsClosed() { cycles_remaining_ = 0; }

  inline void ShortenLifespan() { --cycles_remaining_; }

  virtual Item::Type GetOrderItemType() const = 0;

protected:
  Price price_;
  std::int32_t cycles_remaining_ = 1U;
};

} // namespace stock_exchange

#endif /* ORDER_H */
