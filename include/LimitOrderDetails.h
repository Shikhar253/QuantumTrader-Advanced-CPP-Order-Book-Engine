// include/LimitOrderDetails.h
#pragma once
#include "OrderDetails.h"
#include <chrono> // For std::chrono types

class LimitOrderDetails : public OrderDetails
{
private:
    std::chrono::steady_clock::time_point creationTime;
    std::chrono::seconds validityDuration;

public:
    LimitOrderDetails(OrderType orderType, TimeInForce timeInForce, TradeExecutionCondition condition,
                      std::chrono::seconds validityDuration)
        : OrderDetails(orderType, timeInForce, condition),
          creationTime(std::chrono::steady_clock::now()),
          validityDuration(validityDuration) {}

    // Check if the order is still valid based on its time-in-force and validity duration
    bool isOrderStillValid() const
    {
        if (tif == TimeInForce::GTC)
        {
            return true; // Good 'til Cancelled orders are always valid
        }
        else
        {
            // Check if the order is still within its validity duration
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - creationTime);
            return elapsedTime <= validityDuration;
        }
    }

    // Additional methods or attributes for real-world scenarios can be added here
};
