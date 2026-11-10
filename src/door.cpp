#include <iostream>
#include "../headers/door.hpp"

Door::Door(DoorState s){
  stateMain=0;
  lockTypeMain=0;
  add_state(s);

  std::cout<<" init\n";
}

Door::~Door(){}

Result Door::open(void(*OnOpened)()){
  if(isClosed() && !isLocked()){
      remove_state(DoorState::CLOSED);
      add_state(DoorState::OPENED);
      OnOpened();
      return Result::SUCCESS;
  }
  return Result::FAIL;
}

Result Door::close(void(*OnClosed)()){
  if(isOpened()){
    remove_state(DoorState::OPENED);
    add_state(DoorState::CLOSED);
    OnClosed();
    return Result::SUCCESS;
  }
  return Result::FAIL;
}

Result Door::lock(void(*lock)()){
  if(isClosed() && !isButtonLock()){
    add_lock(LockType::BUTTON);
    lock();
    return Result::SUCCESS;
  }
  return Result::FAIL;
}

Result Door::lock(std::string code,void(*lock)()){
  if(isClosed() && !isCodeLock()){
    lockCode=code;
    add_lock(LockType::CODE);
    lock();
    return Result::SUCCESS;
  }
  return Result::FAIL;
}

Result Door::lock(int key,void(*lock)()){
  if(isClosed() && !isKeyLock()){
    lockKey=key;
    add_lock(LockType::KEY);
    lock();
    return Result::SUCCESS;
  }
  return Result::FAIL;
}

Result Door::unlock(void (*unlock)(), void (*fullUnlock)()){
  if(isLocked() && isButtonLock()){
    remove_lock(LockType::BUTTON,unlock,fullUnlock);
    return Result::SUCCESS;
  }
  std::cout<<"Fail to unlock button lock\n";
  return Result::FAIL;
}

Result Door::unlock(std::string code,void (*codeUnlock)(), void (*fullUnlock)()){
  if(isLocked() && isCodeLock() && is_code_success(code)){
    remove_lock(LockType::CODE,codeUnlock,fullUnlock);
    return Result::SUCCESS;
  }
  std::cout<<"Fail to unlock code lock\n";
  return Result::FAIL;
}

Result Door::unlock(int key, void (*keyUnlock)(), void (*fullUnlock)()){
  if(isLocked() && is_key_success(key)){
    remove_lock(LockType::KEY,keyUnlock,fullUnlock);
    return Result::SUCCESS;
  }
  std::cout<<"Fail to unlock key lock\n";
  return Result::FAIL;
}

void Door::show_info(){
  const char* stateInfo=isLocked()?"locked":isOpened()?"opened":"closed";
  
  std::cout<<" lock: ";
  if(isLocked()){
    if(isCodeLock()) std::cout<<"code ";
    if(isButtonLock()) std::cout<<"button ";
    if(isKeyLock()) std::cout<<"key ";
  }
  else{
    std::cout<<"none";
  }
  std::cout<<"\n state: "<<stateInfo<<"\n";
}

bool Door::isOpened(){
  return stateMain & static_cast<int>(DoorState::OPENED);
}

bool Door::isClosed(){
  return stateMain & static_cast<int>(DoorState::CLOSED);
}

bool Door::isLocked(){
  return stateMain & static_cast<int>(DoorState::LOCKED);
}

bool Door::isCodeLock(){
  return lockTypeMain & static_cast<int>(LockType::CODE);
}

bool Door::isKeyLock(){
  return lockTypeMain & static_cast<int>(LockType::KEY);
}

bool Door::isButtonLock(){
  return lockTypeMain & static_cast<int>(LockType::BUTTON);
}

void Door::add_state(DoorState s){
  stateMain|=static_cast<int>(s);
}

void Door::remove_state(DoorState s){
  stateMain&=~static_cast<int>(s);
}

void Door::add_lock(LockType lt){
  if(!isLocked())
    add_state(DoorState::LOCKED);
  lockTypeMain|=static_cast<int>(lt);
  lock_amount++;
}

void Door::remove_lock(LockType lt,void(*OnUnlocked)(),void(*OnUnlockedCompletely)()){
  lock_amount--;
  lockTypeMain&=~static_cast<int>(lt);
  OnUnlocked();
  if(lock_amount<=0){
    remove_state(DoorState::LOCKED);
    OnUnlockedCompletely();
  }
}

bool Door::is_code_success(std::string code){
  return code==lockCode;
}

bool Door::is_key_success(int key){
  return key==lockKey;
}
