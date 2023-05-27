/*Clase implementada en el h porque al ser template y estar en el primer
proyecto que se compila, al compilarse nadie la llama y no genera ninguna
instancia. */

#pragma once
#ifndef __UTILS_SINGLETON
#define __UTILS_SINGLETON

#include <memory>
#include <typeinfo>
#include <iostream>

template<class T>
/**
Ensures there is only one instance of a class, and offers global access to it.
@tparam T is the class made a singleton
*/
class Singleton {
private:
    //The only instance of class T
    static std::unique_ptr<T> MInstance;
    
protected:
    Singleton() {};

public:
    Singleton<T>& operator=(const Singleton<T>& o) = delete;
    Singleton(const Singleton<T>& o) = delete;
    virtual ~Singleton() {}

    /**
    Constructs the instance of class T.
    @tparam Arguments to pass to class T constructor.
    */
    template<typename ...Targs>
    static T* Init(Targs &&...args) {
        if (MInstance.get() == nullptr)
            MInstance.reset(new T(std::forward<Targs>(args)...));

        return MInstance.get();
    }

    /**
    Returns the class T instance. If it does not exits, creates it with
    the default constructor and returns it.
    @return Reference to the only instance of class T.
    */
    static T* Instance() {
        if (MInstance.get() == nullptr)
            return Init();
        return MInstance.get();
    }

    static void Shutdown() {
        if (MInstance.get() != nullptr)
            delete MInstance.release();
    }
};

template<class T>
std::unique_ptr<T> Singleton<T>::MInstance;

#endif