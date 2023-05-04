//Файл main.cpp
#include <iostream>
#include <future>
#include "finegrainedqueue.h"

int main(){
   FineGrainedQueue fineq(10);
   std::cout << "Before: " << std::endl;
   fineq.show();

   //Создаем фьючерсы
   std::future<void> f1 = std::async(std::launch::async, [&fineq](){ fineq.insertIntoMiddle(1, 10);});
   std::future<void> f2 = std::async(std::launch::async, [&fineq](){ fineq.insertIntoMiddle(2, 20);});
   std::future<void> f3 = std::async(std::launch::async, [&fineq](){ fineq.insertIntoMiddle(3, 5);});
   std::future<void> f4 = std::async(std::launch::async, [&fineq](){ fineq.insertIntoMiddle(4, 5);});
   std::future<void> f5 = std::async(std::launch::async, [&fineq](){ fineq.insertIntoMiddle(5, 6);});
   f1.get();
   f2.get();
   f3.get();
   f4.get();
   f5.get();

   std::cout << std::endl << "After: " << std::endl;
   fineq.show();
   return 0;
}
