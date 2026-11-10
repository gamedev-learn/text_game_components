#include <iostream>
#include "../headers/door.hpp"

void OnOpened();
void OnClosed();
void OnLocked();
void OnUnlocked();
void OnCompletelyUnlocked();

void selector(int s,Door* d){
  std::string pass="codePass";
  int key=4;

  switch(s){
    case 1:std::cout<<static_cast<int>(d->open(OnOpened))<<"\n"; break;
    case 2:std::cout<<static_cast<int>(d->close(OnClosed))<<"\n"; break;
    case 3:std::cout<<static_cast<int>(d->lock(OnLocked))<<"\n"; break;
    case 31:std::cout<<static_cast<int>(d->lock(pass,OnLocked))<<"\n"; break;
    case 32:std::cout<<static_cast<int>(d->lock(key,OnLocked))<<"\n"; break;
    case 4:std::cout<<static_cast<int>(d->unlock(OnUnlocked,OnCompletelyUnlocked))<<"\n"; break;
    case 41:std::cout<<static_cast<int>(d->unlock(pass,OnUnlocked,OnCompletelyUnlocked))<<"\n"; break;
    case 42:std::cout<<static_cast<int>(d->unlock(key,OnUnlocked,OnCompletelyUnlocked))<<"\n"; break;
    case 5:std::cout<<" isOpened: "<<d->isOpened()<<"\n"; break;
    case 6:std::cout<<" isClosed: "<<d->isClosed()<<"\n"; break;
    case 7:std::cout<<" isLocked: "<<d->isLocked()<<"\n"; break;
    case 8:std::cout<<" isCodeLock: "<<d->isCodeLock()<<"\n"; break;
    case 9:std::cout<<" isKeyLock: "<<d->isKeyLock()<<"\n"; break;
    case 10:std::cout<<" isButtonLock: "<<d->isButtonLock()<<"\n"; break;
    case 11:d->show_info(); break;
    case 12:system("clear"); break;
  }
}
void menu(){
  std::cout<<" 1 open\n";
  std::cout<<" 2 close\n";
  std::cout<<" 3 btn_lock\n";
  std::cout<<" 31 code_lock\n";
  std::cout<<" 32 key_lock\n";
  std::cout<<" 4 btn_unlock\n";
  std::cout<<" 41 code_unlock\n";
  std::cout<<" 42 key_unlock\n";
  std::cout<<" 5 check open\n";
  std::cout<<" 6 check close\n";
  std::cout<<" 7 check lock\n";
  std::cout<<" __________\n";
  std::cout<<" 8 check isCodeLock\n";
  std::cout<<" 9 check isKeyLock\n";
  std::cout<<" 10 check isButtonLock\n";
  std::cout<<" __________\n";
  std::cout<<" 11 info\n";
  std::cout<<" 12 clear\n";
}

int main(){
  Door* d=new Door(DoorState::CLOSED);
  int s=0;
  do{
    menu();
    std::cin>>s;
    selector(s,d); 
  }while(s!=0);
  delete d;
  return 0;
}

void OnOpened(){
  std::cout<<"main opened\n";
}
void OnClosed(){
  std::cout<<"main closed\n";
}
void OnLocked(){
  std::cout<<"main locked\n";
}
void OnUnlocked(){
  std::cout<<"main unlocked\n";
}
void OnCompletelyUnlocked(){
  std::cout<<"main completely unlocked\n";
}
