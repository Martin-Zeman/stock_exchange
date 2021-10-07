#ifndef ITEM_H
#define ITEM_H

#include "currency.hpp"
#include "currency_converter.hpp"

#include <string>

namespace stock_exchange {

/**
 * @brief Represents an item that can be traded at the market
 *
 */
class Item {

public:
  /**
   * @brief Types of items traded at the market
   *
   */
  enum class Type : std::size_t {
    COW = 0,
    DONKEY = 1,
    GOAT = 2,
    HORSE = 3,
    ORANGES = 4,
    APPLES = 5,
    PLUMS = 6,
    NUM_TYPES = 7,
  };

  /**
   * @brief Construct a new Item object
   *
   * @param type - type of the item
   * @param owner - name of the owner
   */
  Item(Type type, std::string owner) : type_(type), owner_(owner) {}

  /**
   * @brief Changes ownership to a new owner
   *
   * @param new_owner - name of the new owner
   */
  inline void ChangeOwnershipTo(std::string new_owner) { owner_ = new_owner; }

  /**
   * @brief Get immutable access to the Owner string
   *
   * @return const std::string&
   */
  inline const std::string &GetOwner() const { return owner_; }

  /**
   * @brief Get the Item Type object
   *
   * @return Type
   */
  inline Type GetItemType() const { return type_; }

private:
  Type type_;
  std::string owner_;
};

} // namespace stock_exchange

#endif /* PRICE_H */
