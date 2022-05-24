#include <iostream>
#include <string>
#include <memory>

struct Worker {
    std::string name;
    int salary;

    friend std::ostream& operator<<(std::ostream& out, const Worker& worker) {
        return out << worker.name << " " << worker.salary << "\n";
    }
};

class WorkerManager {
    std::unique_ptr<Worker> worker_ptr;

public:
    WorkerManager(const std::string& name, const int salary) {
        this->worker_ptr = std::make_unique<Worker>(Worker{name, salary});
    }

    WorkerManager(const WorkerManager &wm) {
        this->worker_ptr = std::make_unique<Worker>(Worker{wm.worker_ptr->name, wm.worker_ptr->salary});
    }

    WorkerManager& operator=(const WorkerManager& other) {
        if (this == &other) {
            return *this;
        }

        auto name = other.worker_ptr->name;
        auto age = other.worker_ptr->salary;
        worker_ptr = std::make_unique<Worker>(Worker{name, age});
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const WorkerManager& wm) {
        return out << *wm.worker_ptr;
    }
};

int main() {
    WorkerManager wm1("IZA", 20);
    std::cout << wm1;

    WorkerManager wm2 = wm1;
    std::cout << wm2;

    wm1 = wm2;
    std::cout << wm1;

    return 0;
}