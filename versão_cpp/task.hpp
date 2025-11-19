#ifndef TASK_HPP
#define TASK_HPP

#include <string>
#include <vector>
#include <iostream>

struct Task {
    int id;
    std::string description;
    int priority; // 1 (Baixa) a 3 (Alta)
    bool completed;
};

class TaskManager {
private:
    std::vector<Task> tasks;
    int nextId = 1;

    // Algoritmo de Ordenação (QuickSort) - Interno
    void quickSort(std::vector<Task>& arr, int low, int high);
    int partition(std::vector<Task>& arr, int low, int high);

public:
    void addTask(std::string desc, int priority);
    
    // Algoritmo de Busca (Busca Binária ou Linear)
    int findTaskIndexById(int id); 

    // Algoritmo de Seleção (Filtrar e remover)
    void removeTask(int id);
    void completeTask(int id);

    // Exibição
    void listTasks(bool showCompleted);
    void sortTasksByPriority(); // Chama o QuickSort
};

#endif