#include "market.hpp"

#include <algorithm>
#include <utility>

namespace stock_exchange {

Market::Market() {

  // Initialize buy&sell lists for all item types
  for (std::size_t i = 0U; i < static_cast<std::size_t>(Item::Type::NUM_TYPES);
       ++i) {
    market_lists_.insert(
        std::make_pair(static_cast<Item::Type>(i), buy_sell_list()));
  }
}

template <typename ListType, typename OrderType>
void Market::PlaceOrderOntoList(ListType &list,
                                const std::shared_ptr<OrderType> &order) {

  using ListOrderType = typename ListType::value_type;
  if (list.size() == 0) {
    list.push_front(order);

  } else {
    Price price = order->GetOrderPrice();
    auto price_larger = [&price](const ListOrderType &o) {
      return o->GetOrderPrice() >= price;
    };

    auto it = std::find_if(list.begin(), list.end(), price_larger);
    if (it != list.end()) {
      list.insert(it, order);
    } else {
      list.push_back(order);
    }
  }
}

void Market::Buy(const std::shared_ptr<BuyOrder> &order) {
  auto &buy_list =
      market_lists_[static_cast<Item::Type>(order->GetOrderItemType())].first;

  PlaceOrderOntoList(buy_list, order);
}

void Market::Sell(const std::shared_ptr<SellOrder> &order) {
  auto &sell_list =
      market_lists_[static_cast<Item::Type>(order->GetOrderItemType())].second;

  PlaceOrderOntoList(sell_list, order);
}

template <typename ListType> void Market::RemoveExpiredOrders(ListType &list) {
  using OrderType =
      typename std::remove_pointer<typename ListType::value_type>::type;
  auto expired = [](const OrderType &o) {
    if (!o->IsStillValid()) {
    }

    return !o->IsStillValid();
  };
  list.remove_if(expired);
}

void Market::Cycle() {

  for (std::size_t i = 0U; i < static_cast<std::size_t>(Item::Type::NUM_TYPES);
       ++i) {
    std::list<std::shared_ptr<BuyOrder>> &buy_list =
        market_lists_[static_cast<Item::Type>(i)].first;
    std::list<std::shared_ptr<SellOrder>> &sell_list =
        market_lists_[static_cast<Item::Type>(i)].second;
    RemoveExpiredOrders(buy_list);
    RemoveExpiredOrders(sell_list);
    auto buy_it = buy_list.begin();
    auto sell_it = sell_list.begin();

    for (auto &order : sell_list) {
      order->ShortenLifespan();
    }

    // Close all transactions where the asking price is lower or equal to the
    // buying price
    while ((buy_it != buy_list.end()) && (sell_it != sell_list.end())) {
      if ((*buy_it)->GetOrderPrice() < (*sell_it)->GetOrderPrice()) {
        (*sell_it)->ChangeOrderItemOwnershipTo((*buy_it)->GetOrderOwner());
        (*sell_it)->SetAsClosed();
        (*buy_it)->SetAsClosed();
        sell_it++;
      }
      (*buy_it)->ShortenLifespan();
      buy_it++;
    }

    while (sell_it != sell_list.end()) {
      (*sell_it)->ShortenLifespan();
      sell_it++;
    }
  }
}

} // namespace stock_exchange