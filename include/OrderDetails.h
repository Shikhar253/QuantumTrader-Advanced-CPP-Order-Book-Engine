#pragma once

#include "OrderType.h"

class OrderDetails
{
public:
    OrderType type;
    TimeInForce tif;
    TradeExecutionCondition executionCondition;

    virtual std::string getOrderDescription() const = 0;
    std::string getTimeInForceDescription() const;

    OrderDetails(OrderType orderType, TimeInForce timeInForce, TradeExecutionCondition condition)
        : type(orderType), tif(timeInForce), executionCondition(condition) {}

    virtual ~OrderDetails() = default;
};

class MyOrderDetails : public OrderDetails
{
public:
    MyOrderDetails(OrderType orderType, TimeInForce timeInForce, TradeExecutionCondition condition)
        : OrderDetails(orderType, timeInForce, condition) {}

    std::string getOrderDescription() const override
    {
        // Implement the specific logic for getOrderDescription() in this derived class
        return "MyOrder: " + getTimeInForceDescription();
    }
};
