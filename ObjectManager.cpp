// To practice lifetime management and smart pointers
// See also https://rachelnertia.github.io/programming/2016/11/16/weak-ptr-fun-times/

#include <iostream>
#include <memory>
#include <unordered_map>

// Class to track objects and their existence. Objects will stay in memory as
// long as they are in use, and will be reloaded when they are required again.
// For now only handles objects that can be constructed with one string 
// parameter, such as a filename to load the object from.
template <typename T>
class ObjectManager
{
private:
    std::unordered_map<std::string, std::weak_ptr<T>> data;

public:
    ObjectManager() 
    {
        std::cout << "Constructing Objectmanager for type " << typeid(T).name() << std::endl;
    }

    ~ObjectManager()
    {
        std::cout << "Desstructing Objectmanager " << typeid(T).name() << std::endl;
    }

    std::shared_ptr<T> addItem(const std::string key)
    {
        auto obj = std::make_shared<T>(key);
        data[key] = obj;
        return obj;
    }

    bool isKnown(const std::string key) const
    {
        return data.count(key) != 0;
    }

    bool isLoaded(const std::string key) const
    {
        return isKnown(key) && (data.at(key).expired() == false);
    }

    std::shared_ptr<T> getPointer(const std::string key)
    {
        if (isLoaded(key))
        {
            return data.at(key).lock(); // Create shared_ptr from weak_ptr
        }
        else
        {
            return addItem(key);
        }
    }
};

// Simple object for testing
class SimpleObj
{
private:
    const std::string name;

public:
    SimpleObj(const std::string &name) : name(name)
    {
        std::cout << "Contructing " << name << std::endl;
    }
    ~SimpleObj() 
    {
        std::cout << "Destructing " << name << std::endl;
    }
};

// Main funtion
int main(int, char **)
{
    SimpleObj obj1("obj1");
    ObjectManager<SimpleObj> objMgr;
    auto obj2 = objMgr.getPointer("Obj2");
}
