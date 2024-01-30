// LimitOrderDetails.cpp
#include "LimitOrderDetails.h"

LimitOrderDetails::LimitOrderDetails(OrderType orderType, TimeInForce timeInForce,
                                     TradeExecutionCondition condition, std::chrono::seconds validityDuration)
    : OrderDetails(orderType, timeInForce, condition),
      creationTime(std::chrono::steady_clock::now()),
      validityDuration(validityDuration) {}

// No need to define getOrderDescription() in LimitOrderDetails, let it be inherited

bool LimitOrderDetails::isOrderStillValid() const
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
