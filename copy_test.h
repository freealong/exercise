/* c++ primer 4th P417 消息处理示例 */

#include<iostream>
#include<set>
#include<string>

class Message;
/* Folder */
class Folder {
private:
  static int id_count;
  int id;
  std::set<Message*> messages;

  friend Message;
  void put_Fldr_in_Messages(const std::set<Message*>&);
  void remove_Fldr_in_Messages();

public:
  Folder(): id(id_count++) {}
  Folder(const Folder&);
  Folder& operator=(const Folder&);
  ~Folder();

  void add_mes(Message*);
  void rem_mes(Message*);
  void show() const;
};

int Folder::id_count = 1;

/* private member function */


/* public member function */
Folder::Folder(const Folder &fldr): messages(fldr.messages)
{
  id = id_count++;
  put_Fldr_in_Messages(messages);
}

Folder& Folder::operator=(const Folder &fldr)
{
  if ( this != &fldr){
    remove_Fldr_in_Messages();
    messages = fldr.messages;
    id = id_count++;
    put_Fldr_in_Messages(messages);
  }
  return *this;
}

Folder::~Folder()
{
  remove_Fldr_in_Messages();
}

void Folder::add_mes(Message *mes)
{
  messages.insert(mes);
}

void Folder::rem_mes(Message *mes)
{
  messages.erase(mes);
}


/* Message */
class Message {
private:
  std::string contents;
  std::set<Folder*> folders;
  void put_mes_in_folders(const std::set<Folder*> &);
  void remove_mes_from_folders();

public:
  Message(const std::string &str = ""): contents(str) {}
  Message(const Message &);
  Message& operator=(const Message&);
  ~Message();
  void add_fldr(Folder *);
  void rem_fldr(Folder *);
  void save(Folder&);
  void remove(Folder&);
  void show_contents() const;
  void show() const;
};

void Folder::put_Fldr_in_Messages(const std::set<Message*>& mes)
{
  for(std::set<Message*>::const_iterator iter = mes.begin();
      iter != mes.end(); ++iter)
    (*iter)->add_fldr(this);
}

void Folder::remove_Fldr_in_Messages()
{
  for(std::set<Message*>::const_iterator iter = messages.begin();
      iter != messages.end(); ++iter)
    (*iter)->rem_fldr(this);
}

void Folder::show() const
{
  std::cout<<"id:"<<id<<std::endl;
  for(std::set<Message*>::const_iterator iter = messages.begin();
       iter != messages.end(); ++iter)
    (*iter)->show_contents();
}

/* private member function */
void Message::put_mes_in_folders(const std::set<Folder*> &f)
{
  for (std::set<Folder*>::const_iterator iter = f.begin();
       iter != f.end(); ++iter)
    (*iter)->add_mes(this);
}

void Message::remove_mes_from_folders()
{
  for(std::set<Folder*>::const_iterator iter = folders.begin();
      iter != folders.end(); ++iter)
    (*iter)->rem_mes(this);
}


/* public member function */
Message::Message(const Message &mes):
contents(mes.contents), folders(mes.folders)
{
  put_mes_in_folders(folders);
}

Message& Message::operator=(const Message &mes)
{
  if(this != &mes){
    remove_mes_from_folders();
    contents = mes.contents;
    folders = mes.folders;
    put_mes_in_folders(mes.folders);
  }
  return *this;
}

Message:: ~Message()
{
  remove_mes_from_folders();
}

void Message::add_fldr(Folder *fldr)
{
  folders.insert(fldr);
}

void Message::rem_fldr(Folder *fldr)
{
  folders.erase(fldr);
}

void Message::save(Folder &f)
{
  add_fldr(&f);
  f.add_mes(this);
}

void Message::remove(Folder &f)
{
  rem_fldr(&f);
  f.rem_mes(this);
}

void Message::show_contents() const
{
  std::cout<<"contents:"<<contents<<std::endl;
}

void Message::show() const
{
  show_contents();
  for(std::set<Folder*>::const_iterator iter = folders.begin();
      iter != folders.end(); ++iter)
    std::cout<<"id:"<<(*iter)->id<<std::endl;
}
