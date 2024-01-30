// Order.cpp
#include "Order.h"
#include <iostream>
// Member function to get the order description
std::string Order::getOrderDescription() const
{
    return details->getOrderDescription();
}

// Member function to display order details
void Order::displayOrderDetails() const
{
    std::cout << "Order Details - Quantity: " << quantity << ", Price: " << price << ", Type: " << getOrderDescription() << std::endl;
}

// Member function to check if the order is a market order
bool Order::isMarketOrder() const
{
    return details->type == OrderType::MARKET;
}

// Member function to check if the order is valid based on time-in-force
bool Order::isValidOrder() const
{
    switch (details->tif)
    {
    case TimeInForce::GTC:
        return true; // Good 'til Cancelled orders are always valid
    case TimeInForce::IOC:
        return false; // Immediate or Cancel orders are valid only if they can be executed immediately
    case TimeInForce::FOK:
        return (quantity == 0); // Fill or Kill orders are valid only if they can be fully executed immediately
    default:
        return false;
    }
}

// Member function to check if the order can be partially filled
bool Order::canPartiallyFill() const
{
    return details->executionCondition == TradeExecutionCondition::ALL_OR_NONE;
}
