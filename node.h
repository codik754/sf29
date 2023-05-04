//Файл node.h
#pragma once

#include <mutex>

struct Node{
   int value;
   Node *next;
   std::mutex *node_mutex;

   //Конструктор по умолчанию
   Node() : value(0), next(nullptr), node_mutex(new std::mutex){}

   //Деструктор
   ~Node(){
      delete node_mutex;
   }
};
