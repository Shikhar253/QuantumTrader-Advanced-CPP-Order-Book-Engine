// src/main.cpp
#include "Order.h"
#include "OrderBook.h"
#include "OrderType.h"
#include <iostream>

int main()
{
    // Create an instance of the OrderBook with a maximum depth of 10 and a position limit of 1000
    OrderBook orderBook(10, 1000);

    // Sample limit orders
    std::shared_ptr<Order> limitOrder1 = std::make_shared<Order>(10, 100.0, OrderType::LIMIT, TimeInForce::GTC, TradeExecutionCondition::NONE);
    std::shared_ptr<Order> limitOrder2 = std::make_shared<Order>(15, 98.5, OrderType::LIMIT, TimeInForce::GTC, TradeExecutionCondition::NONE);

    // Sample market orders
    std::shared_ptr<Order> marketOrder1 = std::make_shared<Order>(8, 0.0, OrderType::MARKET, TimeInForce::IOC, TradeExecutionCondition::NONE);
    std::shared_ptr<Order> marketOrder2 = std::make_shared<Order>(12, 0.0, OrderType::MARKET, TimeInForce::GTC, TradeExecutionCondition::NONE);

    // Place orders in the order book
    orderBook.placeOrder({limitOrder1, limitOrder2}, true);    // Place buy (bid) orders
    orderBook.placeOrder({marketOrder1, marketOrder2}, false); // Place sell (ask) orders

    // Display the initial order book with order details
    std::cout << "Initial Order Book with Details:\n";
    orderBook.displayOrdersWithDetails(orderBook.getBids(), "Bids");
    orderBook.displayOrdersWithDetails(orderBook.getAsks(), "Asks");
    std::cout << std::endl;

    // Execute trades based on certain conditions
    orderBook.executeTrades(*marketOrder1, *limitOrder2);
    // Display the updated order book
    std::cout << "\nOrder Book after trade execution:\n";
    orderBook.displayOrderBook();

    // Cancel an order
    double canceledPrice = 98.5;
    bool canceled = orderBook.cancelOrder(canceledPrice, true);
    if (canceled)
    {
        std::cout << "Order at price " << canceledPrice << " canceled successfully.\n";
    }
    else
    {
        std::cout << "Order at price " << canceledPrice << " not found.\n";
    }

    // Display the updated order book
    std::cout << "\nOrder Book after cancellation:\n";
    orderBook.displayOrderBook();

    // Set a new maximum order book depth
    int newMaxDepth = 5;
    orderBook.setMaxOrderBookDepth(newMaxDepth);
    std::cout << "\nOrder Book after setting new max depth:\n";
    orderBook.displayOrderBook();

    // Test additional scenarios based on your requirements

    return 0;
}
