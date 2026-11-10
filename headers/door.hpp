#ifndef DOOR_HPP
#define DOOR_HPP
#include <string.h>

enum class DoorState{
  LOCKED=1,
  OPENED=2,
  CLOSED=4
};

enum class Result{
  FAIL=0,
  SUCCESS=1
};

enum class LockType{
  CODE=1,
  KEY=2,
  BUTTON=4
};

class Door{
  public:
    Door(DoorState);
    ~Door();
    Result open(void());
    Result close(void());
    Result lock(void());
    Result lock(std::string,void());
    Result lock(int,void());

    Result unlock(void(),void());
    Result unlock(std::string,void(),void());
    Result unlock(int,void(),void());
    void show_info();
    bool isOpened();
    bool isClosed();
    bool isLocked();
    bool isCodeLock();
    bool isKeyLock();
    bool isButtonLock();
  private:
    LockType lockType;
    DoorState state;
    std::string lockCode;
    int lockKey;
    int lockTypeMain;
    int stateMain;
    int lock_amount;

    void add_lock(LockType);
    void remove_lock(LockType,void(),void());
    void add_state(DoorState);
    void remove_state(DoorState);
    bool is_code_success(std::string);
    bool is_key_success(int);
};

#endif
