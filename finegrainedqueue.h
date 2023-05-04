//finegrainedqueue.h
#pragma once

#include "node.h"
#include <mutex>

class FineGrainedQueue{
   Node *head;
   std::mutex *queue_mutex;
   int amount_;//количество элементов в списке
public:
   //Конструктор по умолчанию
   FineGrainedQueue() : head(nullptr), queue_mutex(new std::mutex), amount_(0) {}

   //Конструктор по умолчанию
   FineGrainedQueue(const int amount);

   //Деструктор
   ~FineGrainedQueue();

   //Метод, который нужно реализовать
   void insertIntoMiddle(int value, int pos);
   
   //Вывести список
   void show();

};  
