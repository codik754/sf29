//Файл finegrainedqueue.cpp
#include "finegrainedqueue.h"

#include <iostream>
#include <ctime>

//Конструктор по умолчанию
FineGrainedQueue::FineGrainedQueue(const int amount) : head(nullptr), queue_mutex(new std::mutex), amount_(amount){
   //Если передан ноль 
   if(amount_ == 0){
      return;
   }
   //Устанавливаем току, с которой начинается генерация
   srand(time(NULL));
   
   //Создаем первый элемент
   head = new Node;
   head->value = rand() % 100000;
   head->next = nullptr;

   Node *temp = head;//Указатель. указывает на первый элемент
   
   //Добавляем еще узлов
   for(int i = 1; i < amount_; ++i){
      temp->next = new Node;
      temp = temp->next;
      temp->value = rand() % 100000;
      temp->next = nullptr;
   }
}

//Деструктор
FineGrainedQueue::~FineGrainedQueue(){
   //Освобождаем память выделенную под мьютекс
   delete queue_mutex;
   
   //Если указатель на первый элемент не равен nullptr
   if(head){
      Node *temp1 = head;//указатель указывает на первый элемент
      Node *temp2 = nullptr;//указатель. Будет указывать на предыдущий элемент
      //Обходим весь список
      while(temp1){
         //Присваиваем указатель
         temp2 = temp1;
         //Переходим на следующий элемент
         temp1 = temp1->next;
         //Освобождаем память
         delete temp2;
      }
   }
  
}

//Метод, который нужно реализовать
void FineGrainedQueue::insertIntoMiddle(int value, int pos){
   
   //Считываем значения количества элементов 
   //Блокируем очередь
   queue_mutex->lock();
   int amount = amount_;
   ++amount_;//сразу увеличиваем количество элементов
   //Разблокируем очередь
   queue_mutex->unlock(); 

   //Если позиция больше количества элементов в списке
   if(pos >= amount){
      Node *cur;//текущий элемент
       
      //Блокируем очередь
      queue_mutex->lock();
      cur = head;//curr указывает на начало списка
      //Разблокируем очередь
      queue_mutex->unlock(); 
      
      //Если cur не равен nullptr
      if(cur){
         //Блокируем элемент и идем дальше
         cur->node_mutex->lock();
      }

      //Доходим до предпоследнего элемента списка
      while(cur->next){
         Node *old = cur;//указатель. будет хранить предыдущее значение
         cur = cur->next;//переходим на следующий элемент
         old->node_mutex->unlock();//разблокируем предыдущий
         //Если не равен nullptr  
         if(cur){
            cur->node_mutex->lock();//блокируем элемент
         }
      }
      //Создаем новый элемент
      cur->next = new Node;
      Node *old = cur;//указатель.будет хранить предыдущее значение
      cur = cur->next;//переходим на новый элемент
      cur->node_mutex->lock();//блокируем текущий
      old->node_mutex->unlock();//разблокируем предыдущий
      cur->value = value;//присваиваем значение
      cur->next = nullptr;//следующий элемент это конец списка
      cur->node_mutex->unlock();//разблокируем элемент
   }
   else{
      Node *cur;//текущий элемент
       
      //Блокируем очередь
      queue_mutex->lock();
      cur = head;//curr указывает на начало списка
      //Разблокируем очередь
      queue_mutex->unlock(); 
      
      //Если cur не равен nullptr
      if(cur){
         //Блокируем элемент и идем дальше
         cur->node_mutex->lock();
      }
      
      int i = 0;//переменная. Нужна для подсчета позиции
      //Доходим до предпоследнего элемента списка
      while(cur->next){
         //Если нужная позиция 
         if(i == pos - 1){
            break;//выходим из цикла
         }
         Node *old = cur;//указатель. будет хранить предыдущее значение
         cur = cur->next;//переходим на следующий элемент
         old->node_mutex->unlock();//разблокируем предыдущий
         //Если не равен nullptr  
         if(cur){
            cur->node_mutex->lock();//блокируем элемент
         }
         ++i;//увеличиваем на 1
      }
      Node *old1 = cur->next;//указатель.будет хранить следующий элемент в списке 
      Node *old2 = cur;//указатель.будет хранить предыдущий элемент
      cur->next = new Node;//Создаем новый элемент
      cur = cur->next;//переходим на новый элемент
      cur->node_mutex->lock();//блокируем текущий
      old2->node_mutex->unlock();//разблокируем предыдущий
      cur->value = value;//присваиваем значение
      cur->next = old1;//следующий элемент это конец списка
      cur->node_mutex->unlock();//разблокируем элемент
   }
}

//Вывести список
void FineGrainedQueue::show(){
   //Если количество элементов равно 0
   if(amount_ == 0){
      return;
   }

   Node* temp = head;//указатель. Указывает на начало списка
   
   //Обходим весь список
   while(temp){
     //Выводим значение
     std::cout << temp->value << " ";
     //Переходем на чледующий узел
     temp = temp->next;
   }

   std::cout << std::endl;
}
