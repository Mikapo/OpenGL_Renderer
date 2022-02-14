#pragma once

#include "UI_element.h"

template<typename... argtypes>
struct notify_object_interface
{
public:
    virtual void call(argtypes... args) = 0;
};

template<typename T, typename... argtypes>
struct notify_object : public notify_object_interface<argtypes...>
{
public:
    notify_object(T* obj, void (T::* f)(argtypes...)) : m_obj(obj), m_f(f) {}

    void call(argtypes... args) override
    {
        (m_obj->*m_f)(std::forward<argtypes>(args)...);
    }

private:
    T* m_obj;
    void (T::* m_f)(argtypes...);
};


template<typename... argtypes>
class UI_element_notify : public UI_element
{
public:
    UI_element_notify(const std::string& name) : UI_element(name) {}

    template<typename T>
    void add_notify(T* obj, void(T::* f)(argtypes...))
    {
        notifies[static_cast<void*>(obj)].reset(new notify_object<T, argtypes...>(obj, f));
    }

    template<typename T>
    void remove_notify(T* obj)
    {
        notifies.erase(static_cast<void*>(obj));
    }

protected:

    void notify(argtypes... args)
    {
        for (auto& notifie : notifies)
        {
            notifie.second->call(std::forward<argtypes>(args)...);
        }
    }

private:
    std::unordered_map<void*, std::unique_ptr<notify_object_interface<argtypes...>>> notifies;
};
