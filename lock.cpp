#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

mutex flexible_mutex;

void tarea_flexible(int id) {
    // 1. Crear el candado (no bloquea inmediatamente si le pasamos defer_lock)
    unique_lock<mutex> lock(flexible_mutex, defer_lock);
    
    cout << "Hilo " << id << " esperando...\n";
    
    // 2. Bloqueamos explícitamente cuando es necesario
    lock.lock();
    cout << "Hilo " << id << " ha adquirido el candado.\n";
    
    // 3. Tarea crítica
    this_thread::sleep_for(chrono::milliseconds(50));
    
    // 4. Liberamos el candado antes de que termine el ámbito
    lock.unlock();
    cout << "Hilo " << id << " ha liberado el candado para hacer otra cosa sin bloquear.\n";
    
    // 5. El lock_guard garantiza que, si no lo liberamos antes, se libera al salir de la función.
}


int main() {
    std::thread t1(tarea_flexible, 1);
    std::thread t2(tarea_flexible, 2);

    t1.join();
    t2.join();
    
    std::cout << "Uso de unique_lock completado.\n";
    return 0;
}
