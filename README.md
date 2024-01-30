# Financial Order Book Management System

This project implements a sophisticated financial order book management system in C++. The system facilitates the management of buy (bids) and sell (asks) orders for a financial instrument, incorporating various features and concepts.

## Features

- **Order Placement:**
  - Place new buy or sell orders with specified quantities and prices.
- **Order Matching:**
  - Match buy and sell orders to execute trades based on specified conditions.
- **Order Cancellation:**
  - Cancel a previously placed buy or sell order.
- **Dynamic Order Book Depth:**
  - Adjust the maximum depth of the order book dynamically to adapt to market conditions.
- **Priority-Based Matching:**
  - Implement advanced matching algorithms that prioritize hidden orders for enhanced order execution.
- **Risk Management Enhancements:**
  - Set and enforce a maximum position limit per trader to manage risk exposure.
  - Validate order placements against position limits to prevent excessive risk.

## Usage

1. Build the project using CMake.
2. Run the executable generated.

### Sample Usage (main.cpp)

```cpp
#include "order_book.h"

int main() {
    OrderBook orderBook;

    orderBook.placeOrder(Order(10, 50.0), true);
    orderBook.placeOrder(Order(5, 51.0), true);
    orderBook.placeOrder(Order(8, 49.0), false);
    orderBook.placeOrder(Order(12, 50.5), false);

    orderBook.displayOrderBook();

    // Cancel an order
    orderBook.cancelOrder(51.0, true);

    orderBook.displayOrderBook();

    return 0;
}
## Build Instructions

To build the project, use the following commands:

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
cd bin
./MDSTEST.exe
```

# C++ Order Book Project Overview

## Features and Concepts Used

### 1. Object-Oriented Programming (OOP)

- **Classes and Objects:** Used classes like `Order`, `OrderDetails`, and `OrderBook` to model entities and their behaviors.

### 2. Enums

- **OrderType Enum:**
  - Represents order types (`LIMIT` and `MARKET`).
- **TimeInForce Enum:**
  - Represents time-in-force options (`GTC`, `IOC`, and `FOK`).
- **TradeExecutionCondition Enum:**
  - Represents trade execution conditions (`NONE`, `HIDDEN`, `POST_ONLY`, and `ALL_OR_NONE`).

### 3. Smart Pointers

- **std::shared_ptr:**
  - Used smart pointers to manage memory for orders (`std::shared_ptr<Order>`).

### 4. Multithreading

- **std::mutex:**
  - Implemented mutexes (`std::mutex`) to ensure thread safety in concurrent sections of the code.

### 5. STL Containers

- **std::unordered_map:**
  - Used unordered maps to store bids and asks efficiently.
- **std::priority_queue:**
  - Utilized priority queues for maintaining order book prices.

### 6. Exception Handling

- **std::runtime_error:**
  - Threw runtime errors for exceptional conditions (e.g., order not found for cancellation).

### 7. File Organization

- **Header Files (.h):**
  - Used for class and function declarations.
- **Implementation Files (.cpp):**
  - Contain the actual implementations of declared classes and functions.

### 8. CMake for Build Configuration

- **CMakeLists.txt:**
  - Configuration file specifying how the project should be built.

### 9. Git Version Control

- **.gitignore:**
  - Ignored files and directories for version control.

## Additional Features 
### 1. Dynamic Order Book Depth

- **setMaxOrderBookDepth Function:**
  - Dynamically adjusts the order book depth based on market conditions.

### 2. Advanced Matching Algorithms

- **prioritizeHiddenOrders Function:**
  - Implements priority-based matching by placing hidden orders first in the order book.

### 3. Risk Management Enhancements

- **maxPositionLimit Variable:**
  - Sets a maximum position limit per trader to control risk exposure.
- **checkPositionLimits Function:**
  - Validates order placements against position limits.

---

Feel free to adapt and extend this code for further enhancements and scenarios based on your requirements.


