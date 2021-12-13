
#include <unistd.h>

#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <functional>

#include <boost/asio.hpp>
#include <boost/thread.hpp>


//#include <iostream>

//#include <boost/asio/io_context.hpp>
class event
{
public:
  explicit
  event(boost::asio::io_service& io_service) 
    : timer_(io_service)
  {
    timer_.expires_at(boost::posix_time::pos_infin);
  }

  template <typename WaitHandler>
  void async_wait(WaitHandler handler)
  {
    timer_.async_wait(boost::bind(handler));
  }

  void notify_one() 
  {
    timer_.cancel_one();
  }

  void notify_all() 
  {
    timer_.cancel();
  }

private:
  boost::asio::deadline_timer timer_;
};

using namespace std::chrono_literals;

void on_event() 
{ 
  int counter = 0;
  std::cout << "on_event" << ++counter << std::endl;
}

int main()
{
  boost::asio::io_service io_service;
  
  event event(io_service);

  event.async_wait(&on_event);

  boost::thread thread(boost::bind(&boost::asio::io_service::run,
                       &io_service));

  int counter = 0;
  for(int i = 1; i <= 10; i++) {
    event.async_wait(std::function<void()>([&counter]() {
      ++counter;
    }));
    event.notify_one();
  }

  event.notify_all();
  thread.join();  
  std::cout << counter << "\n";
}


int main1()
{
  std::cout<<"test reactor\n";

  boost::asio::io_context io_context;


  return 0;
}

/*
 
   boost::asio

   1. существует три контекста ввода вывода:
    - boost::asio::io_context
 
    - boost::asio::thread_pool
 
    - boost::asio:
 



*/




