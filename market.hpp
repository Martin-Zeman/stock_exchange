#ifndef MARKET_H
#define MARKET_H

#include "buy_order.hpp"
#include "item.hpp"
#include "order.hpp"
#include "sell_order.hpp"

#include <list>
#include <memory>
#include <tuple>
#include <type_traits>
#include <unordered_map>

namespace stock_exchange {

class Market {

  struct EnumClassHash {
    template <typename T> std::size_t operator()(T t) const {
      return static_cast<std::size_t>(t);
    }
  };

  using buy_item_list = std::list<std::shared_ptr<BuyOrder>>;
  using sell_item_list = std::list<std::shared_ptr<SellOrder>>;
  using buy_sell_list = std::pair<buy_item_list, sell_item_list>;
  using MarketListMap =
      std::unordered_map<Item::Type, buy_sell_list, EnumClassHash>;

public:
  /**
   * @brief Construct a new Market object
   *
   */
  Market();

  /**
   * @brief Places a buy order
   *
   * @param order
   */
  void Buy(const std::shared_ptr<BuyOrder> &order);

  /**
   * @brief Places a sell order
   *
   * @param order
   */
  void Sell(const std::shared_ptr<SellOrder> &order);

  /**
   * @brief Triggers a cycle of matching supply and demand
   *
   */
  void Cycle();

protected:
  /**
   * @brief Get immutable access the Market Lists object for the purposes of
   * testing
   *
   * @return const MarketListMap&
   */
  const MarketListMap &GetMarketLists() const { return market_lists_; }

private:
  /**
   * @brief Places an order onto a given list at the right location in ascending
   * order of price.
   *
   * @tparam ListType  - either a buy or a sell item list
   * @tparam OrderType  - either a buy or a sell order
   * @param list - list to be placed onto
   * @param order - order to be placed
   */
  template <typename ListType, typename OrderType>
  void PlaceOrderOntoList(ListType &list,
                          const std::shared_ptr<OrderType> &order);

  /**
   * @brief Removes all expired orders from a given list
   *
   * @tparam ListType  - either a buy or a sell item list
   * @param list - list from which expired orders are to be removed
   */
  template <typename ListType> void RemoveExpiredOrders(ListType &list);

  MarketListMap market_lists_;
};

} // namespace stock_exchange

#endif /* MARKET_H */
