Task description:
------------------------------------------------------------------------------------------------------------------
Design and implement a Market library for trading animals, fruits all under one roof.

 

Public interface example ( pseudo code ):

class Market

{

public:

     Item Buy(ItemType , price);

     void Sell(“What is being sold”, price);

};

 

Assumptions:

Animals are traded for price per head ( example 1 cow sells for 125.25$ )  
Fruit is traded with price per kilo ( 1kg of oranges sells for 10.70$ )
Other currencies should be also possible, but limit the tests to Dollar and Euro
For the sake of exercise it’s enough to focus on 2 examples in unit tests
 

Parameters:

Please use C++14 or C++17 ( gcc or clang),
Provide fully buildable solution.
Please provide unit tests which prove various parts of functionality.
In case you run out of time, it’s okay to present only part of the solution.
Don’t use library which does all the work for you because we want to see your code.

Solution:
------------------------------------------------------------------------------------------------------------------

# How to use:
# 1) mkdir build
# 2) cd build
# 3) cmake ..
# 4) make
# 5) make runtests

Please note that you need to have CMake of version at least 3.10.2 available.