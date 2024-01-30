// src/OrderBook.cpp
#include "OrderBook.h"
#include <algorithm>

OrderBook::OrderBook(int maxDepth, int positionLimit)
    : maxOrderBookDepth(maxDepth), maxPositionLimit(positionLimit) {}

void OrderBook::setMaxOrderBookDepth(int maxDepth)
{
    std::lock_guard<std::mutex> lock(orderBookMutex);
    maxOrderBookDepth = maxDepth;
}

void OrderBook::prioritizeHiddenOrders(const std::vector<std::shared_ptr<Order>> &orders)
{
    std::stable_partition(orders.begin(), orders.end(),
                          [](const Order &order)
                          { return order.details->executionCondition == TradeExecutionCondition::HIDDEN; });
}

bool OrderBook::checkPositionLimits(const std::vector<std::shared_ptr<Order>> &orders, bool isBuyer)
{
    int totalQuantity = 0;

    for (const auto &orderPtr : orders)
    {
        totalQuantity += orderPtr->quantity;
    }

    if (isBuyer && totalQuantity > maxPositionLimit)
    {
        std::cout << "Buyer position limit exceeded. Order not placed.\n";
        return false;
    }
    else if (!isBuyer && totalQuantity > maxPositionLimit)
    {
        std::cout << "Seller position limit exceeded. Order not placed.\n";
        return false;
    }

    return true;
}

void OrderBook::executeTrade(Order &buyer, Order &seller)
{
    int tradedQuantity = std::min(buyer.quantity, seller.quantity);

    std::cout << "Trade Executed: " << tradedQuantity << " @ " << buyer.price << std::endl;

    buyer.quantity -= tradedQuantity;
    seller.quantity -= tradedQuantity;

    if (buyer.quantity == 0)
    {
        bids.erase(buyer.price);
    }

    if (seller.quantity == 0)
    {
        asks.erase(seller.price);
    }
}

void OrderBook::placeOrder(const std::vector<std::shared_ptr<Order>> &orders, bool isBuyer)
{
    std::lock_guard<std::mutex> lock(placeOrderMutex);

    if (!checkPositionLimits(orders, isBuyer))
    {
        return;
    }

    prioritizeHiddenOrders(orders);

    for (const auto &order : orders)
    {
        if (isBuyer)
        {
            bids[order->price] = order;
        }
        else
        {
            asks[order->price] = order;
        }
    }

    matchOrders();
}

void OrderBook::matchOrders()
{
    std::lock_guard<std::mutex> lock(matchOrdersMutex);

    auto bidIt = bids.rbegin();
    auto askIt = asks.begin();

    while (bidIt.base() != bids.end() && askIt != asks.end())
    {
        if (bidIt->first >= askIt->first)
        {
            executeTrade(*bidIt->second, *askIt->second);

            if (bidIt->second->quantity == 0)
            {
                bids.erase((++bidIt).base());
            }

            if (askIt->second->quantity == 0)
            {
                asks.erase(askIt++);
            }
        }
        else
        {
            break;
        }
    }
}

void OrderBook::displayOrderBook() const
{
    std::lock_guard<std::mutex> lock(orderBookMutex);

    std::cout << "Order Book (Depth: " << maxOrderBookDepth << ", Position Limit: " << maxPositionLimit << ")\n";
    displayOrders(bids, "Bids");
    displayOrders(asks, "Asks");
    std::cout << std::endl;
}

void OrderBook::displayOrders(const auto &orders, const std::string &label) const
{
    std::cout << label << ":\n";
    for (const auto &entry : orders)
    {
        const auto &order = entry.second;
        std::cout << "  Quantity: " << order->quantity << ", Price: " << entry.first
                  << ", Type: " << order->details->getOrderDescription() << std::endl;
    }
}

void OrderBook::displayOrdersWithDetails(const std::map<double, std::shared_ptr<Order>> &orders, const std::string &label) const
{
    std::cout << label << ":\n";
    for (const auto &entry : orders)
    {
        const auto &order = entry.second;
        order->displayOrderDetails(); // Use the new member function to display order details
    }
}

// Member function to execute trades based on certain conditions
void OrderBook::executeTrades(Order &buyer, Order &seller)
{
    int tradedQuantity = std::min(buyer.quantity, seller.quantity);

    std::cout << "Trade Executed: " << tradedQuantity << " @ " << buyer.price << std::endl;

    buyer.quantity -= tradedQuantity;
    seller.quantity -= tradedQuantity;

    if (buyer.quantity == 0)
    {
        bids.erase(buyer.price);
    }

    if (seller.quantity == 0)
    {
        asks.erase(seller.price);
    }

    // Additional logic for handling partially filled orders
    if (buyer.canPartiallyFill() && seller.canPartiallyFill() && buyer.quantity > 0 && seller.quantity > 0)
    {
        // Handle partial fill logic if needed
    }
}
using OrdersMap = std::map<double, std::shared_ptr<Order>, std::less<double>>;

bool OrderBook::cancelOrder(double price, bool isBuyer)
{
    std::lock_guard<std::mutex> lock(cancelOrderMutex);

    OrdersMap *ordersPtr = nullptr;

    if (isBuyer)
    {
        ordersPtr = &bids;
    }
    else
    {
        ordersPtr = &asks;
    }

    if (ordersPtr)
    {
        auto it = ordersPtr->find(price);

        if (it != ordersPtr->end())
        {
            std::cout << "Order at price " << price << " canceled.\n";
            ordersPtr->erase(it);
            return true;
        }
    }

    std::cout << "Order at price " << price << " not found for cancellation.\n";
    return false;
}
