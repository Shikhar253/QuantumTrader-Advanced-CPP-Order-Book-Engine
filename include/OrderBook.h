// include/OrderBook.h
#pragma once

#include "Order.h"
#include <unordered_map>
#include <iostream>
#include <mutex>
#include <vector>
#include <map>

class OrderBook
{
public:
    OrderBook(int maxDepth, int positionLimit);

    void setMaxOrderBookDepth(int maxDepth);
    bool checkPositionLimits(const std::vector<std::shared_ptr<Order>> &orders, bool isBuyer);
    void executeTrade(Order &buyer, Order &seller);
    void placeOrder(const std::vector<std::shared_ptr<Order>> &orders, bool isBuyer);
    void prioritizeHiddenOrders(const std::vector<std::shared_ptr<Order>> &orders); // Updated parameter type
    void matchOrders();
    void displayOrderBook() const;
    bool cancelOrder(double price, bool isBuyer);
    void displayOrdersWithDetails(const std::map<double, std::shared_ptr<Order>> &orders, const std::string &label) const;
    void executeTrades(Order &buyer, Order &seller);
    void displayOrders(const auto &orders, const std::string &label) const;

    const std::map<double, std::shared_ptr<Order>, std::less<double>> &getBids() const
    {
        return bids;
    }

    const std::map<double, std::shared_ptr<Order>, std::less<double>> &getAsks() const
    {
        return asks;
    }

private:
    int maxOrderBookDepth;
    int maxPositionLimit;
    std::map<double, std::shared_ptr<Order>, std::less<double>> bids; // Using std::greater to get reverse order
    std::map<double, std::shared_ptr<Order>, std::less<double>> asks;

    mutable std::mutex orderBookMutex;
    mutable std::mutex matchOrdersMutex;
    mutable std::mutex placeOrderMutex;
    mutable std::mutex cancelOrderMutex;
};
