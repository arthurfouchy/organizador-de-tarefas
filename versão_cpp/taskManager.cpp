#include "Task.hpp"
#include <algorithm> // Apenas para swap se necessário
#include <iomanip>

// --- Algoritmo de Ordenação: QuickSort (Por Prioridade Decrescente) ---
void TaskManager::quickSort(std::vector<Task>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int TaskManager::partition(std::vector<Task>& arr, int low, int high) {
    int pivot = arr[high].priority; 
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // Ordenando do maior para o menor (Prioridade alta primeiro)
        if (arr[j].priority > pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void TaskManager::sortTasksByPriority() {
    if (tasks.empty()) return;
    quickSort(tasks, 0, tasks.size() - 1);
    std::cout << ">> Tarefas ordenadas por prioridade (Algoritmo QuickSort aplicado).\n";
}

// --- Lógica de Gerenciamento ---

void TaskManager::addTask(std::string desc, int priority) {
    Task t;
    t.id = nextId++;
    t.description = desc;
    t.priority = priority;
    t.completed = false;
    tasks.push_back(t);
    std::cout << ">> Tarefa criada com ID " << t.id << ".\n";
}

// --- Algoritmo de Busca: Busca Linear ---
// Nota: Usamos Linear pois a lista pode ser reordenada por prioridade,
// o que quebraria a lógica da Busca Binária por ID.
int TaskManager::findTaskIndexById(int id) {
    for (size_t i = 0; i < tasks.size(); ++i) {
        if (tasks[i].id == id) {
            return i; // Retorna o índice
        }
    }
    return -1; // Não encontrado
}

void TaskManager::completeTask(int id) {
    int index = findTaskIndexById(id); // Aplicação da Busca
    if (index != -1) {
        tasks[index].completed = true;
        std::cout << ">> Tarefa " << id << " marcada como concluida.\n";
    } else {
        std::cout << ">> Erro: ID nao encontrado.\n";
    }
}

// --- Algoritmo de Seleção (Remoção) ---
void TaskManager::removeTask(int id) {
    int index = findTaskIndexById(id);
    if (index != -1) {
        tasks.erase(tasks.begin() + index);
        
        // Reorganizar IDs para manter a sequencia (1, 2, 3...)
        for (size_t i = 0; i < tasks.size(); ++i) {
            tasks[i].id = i + 1;
        }
        nextId = tasks.size() + 1;

        std::cout << ">> Tarefa removida com sucesso. IDs reorganizados.\n";
    } else {
        std::cout << ">> Erro: Tarefa nao encontrada.\n";
    }
}

void TaskManager::listTasks(bool showCompleted) {
    std::cout << "\n--- LISTA DE TAREFAS (" << (showCompleted ? "CONCLUIDAS" : "PENDENTES") << ") ---\n";
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(15) << "Prioridade" 
              << std::setw(30) << "Descricao" << "\n";
    std::cout << "-----------------------------------------------\n";

    bool found = false;
    // Algoritmo de Seleção simples (Filtragem para exibição)
    for (const auto& task : tasks) {
        if (task.completed == showCompleted) {
            std::cout << std::left << std::setw(5) << task.id 
                      << std::setw(15) << task.priority 
                      << std::setw(30) << task.description << "\n";
            found = true;
        }
    }
    if (!found) std::cout << "(Nenhuma tarefa encontrada neste status)\n";
    std::cout << "-----------------------------------------------\n";
}