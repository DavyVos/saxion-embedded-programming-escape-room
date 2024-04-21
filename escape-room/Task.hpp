#ifndef TASK_H
#define TASK_H

class GameContext;

class Task {
private:
  void (*func)(GameContext*);
  GameContext* context;

public:
  Task() = default;
  Task(void (*f)(GameContext*), GameContext *context);

  void execute();
};

#endif //TASK_H