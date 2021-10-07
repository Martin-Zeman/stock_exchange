#ifndef SELL_ORDER_H
#define SELL_ORDER_H

#include "order.hpp"
#include "price.hpp"

#include <memory>

namespace stock_exchange {

/**
 * @brief Represents either a buy or a sell order
 *
 */
class SellOrder : public Order {

public:
  /**
   * @brief Construct a new Order object
   *
   * @param price - price for which the item is to be sold or bought
   * @param cycle_limit - maximum cycle duration of the order
   * @param item - item to be either sold or bought
   */
  SellOrder(const Price &price, std::uint8_t cycle_limit,
            const std::shared_ptr<Item> &item)
      : Order(price, cycle_limit), item_(item) {}

  /**
   * @brief Changes the ownership of the order's item to the owner
   *
   * @param new_owner
   */
  inline void ChangeOrderItemOwnershipTo(std::string new_owner) {
    item_->ChangeOwnershipTo(new_owner);
  }

  inline std::string GetOrderOwner() { return item_->GetOwner(); }

  /**
   * @brief Get the Order Item Type object
   *
   * @return Item::Type
   */
  virtual Item::Type GetOrderItemType() const override {
    return item_->GetItemType();
  }

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

private:
  std::shared_ptr<Item> item_;
};

} // namespace stock_exchange

#endif /* SELL_ORDER_H */
