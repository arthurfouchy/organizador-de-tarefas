#include "Task.hpp"
#include "TaskManager.cpp" // Em projetos maiores, compilaríamos separadamente, mas aqui incluímos para facilitar testes rápidos.
#include <limits>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    TaskManager tm;
    int option;
    
    // Dados iniciais para teste
    tm.addTask("Estudar C++", 3);
    tm.addTask("Comprar leite", 1);
    tm.addTask("Pagar internet", 2);

    do {
        // Exibir listas automaticamente
        tm.listTasks(false); // Pendentes
        tm.listTasks(true);  // Concluidas

        std::cout << "\n=== TaskMaster Pro ===\n";
        std::cout << "1. Adicionar Tarefa\n";
        std::cout << "2. Concluir Tarefa\n";
        std::cout << "3. Remover Tarefa\n";
        std::cout << "4. Ordenar por Prioridade (QuickSort)\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha: ";
        std::cin >> option;

        if(std::cin.fail()) { clearInput(); continue; }

        switch(option) {
            case 1: {
                std::string desc;
                int prio;
                std::cout << "Descricao: ";
                clearInput();
                std::getline(std::cin, desc);
                std::cout << "Prioridade (1-3): ";
                std::cin >> prio;
                tm.addTask(desc, prio);
                break;
            }
            case 2: {
                int id;
                std::cout << "ID da tarefa a concluir: ";
                std::cin >> id;
                tm.completeTask(id);
                break;
            }
            case 3: {
                int id;
                std::cout << "ID da tarefa a remover: ";
                std::cin >> id;
                tm.removeTask(id);
                break;
            }
            case 4: tm.sortTasksByPriority(); break;
            case 0: std::cout << "Encerrando...\n"; break;
            default: std::cout << "Opcao invalida!\n";
        }
    } while (option != 0);

    return 0;
}