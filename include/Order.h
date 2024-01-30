// include/Order.h
#pragma once

#include "OrderType.h"
#include "OrderDetails.h"
#include <memory>
#include <utility>

class Order
{
public:
    int quantity;
    double price;
    std::shared_ptr<MyOrderDetails> details;
    std::string getOrderDescription() const;
    void displayOrderDetails() const;
    bool isMarketOrder() const;
    bool isValidOrder() const;
    bool canPartiallyFill() const;

    Order(int qty, double prc, OrderType orderType, TimeInForce timeInForce, TradeExecutionCondition condition)
        : quantity(qty), price(prc), details(std::make_shared<MyOrderDetails>(orderType, timeInForce, condition)) {}

    Order(Order &&other) noexcept
        : quantity(std::exchange(other.quantity, 0)),
          price(std::exchange(other.price, 0.0)),
          details(std::move(other.details)) {}

    Order &operator=(Order &&other) noexcept
    {
        if (this != &other)
        {
            quantity = std::exchange(other.quantity, 0);
            price = std::exchange(other.price, 0.0);
            details = std::move(other.details);
        }
        return *this;
    }
};
