// include/OrderType.h
#pragma once

#include <string>

enum class OrderType
{
    LIMIT,
    MARKET
};

enum class TimeInForce
{
    GTC, // Good 'til Cancelled
    IOC, // Immediate or Cancel
    FOK  // Fill or Kill
};

enum class TradeExecutionCondition
{
    NONE,
    HIDDEN,
    POST_ONLY,
    ALL_OR_NONE
};
