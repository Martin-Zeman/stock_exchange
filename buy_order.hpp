#ifndef BUY_ORDER_H
#define BUY_ORDER_H

#include "order.hpp"

#include <memory>
#include <string>

namespace stock_exchange {

/**
 * @brief Represents a generic order to be inherited from
 *
 */
class BuyOrder : public Order {

public:
  /**
   * @brief Construct a new Order object
   *
   * @param price - price for which the item is to be sold or bought
   * @param cycle_limit - maximum cycle duration of the order
   * @param order_owner - owner of the buy order
   */
  BuyOrder(const Price &price, std::uint8_t cycle_limit, Item::Type type,
           std::string order_owner)
      : Order(price, cycle_limit), item_type_(type), order_owner_(order_owner) {
  }

  virtual Item::Type GetOrderItemType() const override { return item_type_; }

  /**
   * @brief Get immutable access to the order's owner
   *
   * @return std::string - owner's name
   */
  inline const std::string &GetOrderOwner() const { return order_owner_; }

private:
  Item::Type item_type_;
  std::string order_owner_;
};

} // namespace stock_exchange

#endif /* BUY_ORDER_H */
