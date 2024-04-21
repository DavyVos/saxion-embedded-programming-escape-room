#include "Task.hpp"
#include "../.build/sketch/GameContext.hpp"

Task::Task(void (*f)(GameContext*), GameContext* context) : func(f), context(context) {}

void Task::execute()
{
    if (func)
    {
        func(this->context);
    }
}