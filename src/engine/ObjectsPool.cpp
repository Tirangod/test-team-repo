#include <engine/ObjectsPool.hpp>

ObjectsPool *ObjectsPool::instance = nullptr;

ObjectsPool& ObjectsPool::init(int reserveNumber) {
    if (instance != nullptr)
        delete instance;
    instance = new ObjectsPool;
    instance->objects.reserve(reserveNumber);
    instance->buffer.reserve(reserveNumber);
    instance->indexes.reserve(reserveNumber);
    return *instance;
}

ObjectsPool& ObjectsPool::get() {
    if (instance == nullptr)
        throw "ObjectsPool has to be inited first!";
    return *instance;
}

void ObjectsPool::addObject(GameObject *object) {
    object->_init();
    get().buffer.push_back(object);
}

void ObjectsPool::killObject(GameObject *object) {
    auto &self = get();

    for (int i = 0; i < self.objects.size(); i++) {
        if (self.objects[i] == object) {
            self.indexes.push_back(i);
            object->onKilled();
            return;
        }
    }
    self.objects.remove(object);

    object->onKilled();
}

void ObjectsPool::clearObjects() {
    auto &self = get();

    for (int i = 0; i < self.indexes.size(); i++) {
        int index = self.indexes[i];
        auto objPos = self.objects.begin();
        auto obj = &(*objPos);
        self.objects.erase(objPos);
        delete *obj;
    }
    self.indexes.clear();
    
    // LOGGING
    cout << "ObjectsPool::clearObjects" << endl;
}

void ObjectsPool::flush() {
    auto &self = get();

    if (self.buffer.size() <= 0)
        return;

    for (auto it = self.buffer.begin(); it != self.buffer.end(); ++it) {
        self.objects.push_back(*it);
    }
    self.buffer.clear();
    
}

ObjectsVector ObjectsPool::getObjects() { return get().objects; }
