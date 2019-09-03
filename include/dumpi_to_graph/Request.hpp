#ifndef D2G_REQUEST_H
#define D2G_REQUEST_H

#include <string>
#include <iostream>

#include "Channel.hpp"

// Request types:
// 0 - MPI_Isend
// 1 - MPI_Irecv
// 2 - MPI_Send_init
// 3 - MPI_Recv_init
class Request
{
public:
  Request() {}
  Request( int type, int id );
  Request( int type, int id, const Channel& channel );
  int get_type() const;
  int get_id() const;
  Channel get_channel() const;
  bool is_active() const;
  bool is_cancelled() const;
  void activate();
  void deactivate();
  void cancel();
  void set_channel(const Channel& channel);
  Request operator=(const Request& rhs) 
  {
    if (this == &rhs) {
      return *this;
    } else {
      this->type = rhs.get_type();
      this->id = rhs.get_id();
      this->active = rhs.is_active();
      this->cancelled = rhs.is_cancelled();
      this->channel = rhs.get_channel();
      return *this;
    }
  }

  friend std::ostream& operator<< ( std::ostream& out, const Request& request )
  {
    out << "Type: " << request.get_type()
        << ", ID: " << request.get_id()
        << ", Active?: " << request.is_active()
        << ", Cancelled?: " << request.is_cancelled();
    return out;
  }
private:
  int id;
  int type;
  bool active;
  bool cancelled = false;
  Channel channel; 
};



//// Representation of an MPI_Request handle:
//// Each MPI_Request is generated by and associated with a call of an MPI 
//// communication function (e.g., MPI_Isend or MPI_Irecv) that return immediately
//// and is later completed explicitly by passing the associated MPI_Request 
//// handle to another function, such as MPI_Wait. 
//// We store information about the initial call (e.g., an MPI_Irecv) in the 
//// Request so that later on, when we encounter the record of its completing call
//// (e.g., an MPI_Wait) in the trace, we can look up which communication channel
//// the message was in
//class Request
//{
//public:
//  Request() {}
//  Request( int id ) : id(id) {}
//  virtual ~Request() {}
//  int get_id() const;
//  //friend std::ostream& operator<<( std::ostream& out, const Request& rhs )
//  //{
//  //  out << "Request: ID: " << rhs.get_id();
//  //  return out;
//  //}
//
//  virtual void print( std::ostream& out ) const
//  {
//  }
//private:
//  int id;
//};
//
//inline std::ostream& operator<< (std::ostream& out, const Request& request)
//{
//  request.print(out);
//  return out;
//}
//
//class NonblockingCommunicationRequest : public Request
//{
//public:
//  NonblockingCommunicationRequest(int id, const Channel& channel) :
//    Request(id),
//    channel(channel)
//    {}
//  virtual ~NonblockingCommunicationRequest() {}
//  // Accessors
//  const Channel& get_channel() const;
//  bool is_cancelled() const;
//  // Request cancellation
//  void cancel();
//
//  virtual void print( std::ostream& out ) const
//  {
//  }
//protected:
//  Channel channel;
//  bool cancelled = false;
//};
//
//class IsendRequest : public NonblockingCommunicationRequest
//{
//public:
//  IsendRequest(int id, const Channel& channel) :
//    NonblockingCommunicationRequest(id, channel)
//    {}
//  //friend std::ostream& operator<<( std::ostream& out, const IsendRequest& rhs )
//  //{
//  //  out << "Isend Request: ID: " << rhs.get_id() 
//  //      << ", Channel: " << rhs.get_channel();
//  //  return out;
//  //}
//  void print( std::ostream& out ) const
//  {
//    out << "Isend Request: ID: " << this->get_id()
//        << ", Channel: " << this->get_channel();
//  }
//private:
//};
//
//class IrecvRequest : public NonblockingCommunicationRequest
//{
//public:
//  IrecvRequest( int id, const Channel& channel) :
//    NonblockingCommunicationRequest(id, channel)
//    {}
//  //friend std::ostream& operator<<( std::ostream& out, const IrecvRequest& rhs )
//  //{
//  //  out << "Irecv Request: ID: " << rhs.get_id() 
//  //      << ", Channel: " << rhs.get_channel();
//  //  return out;
//  //}
//  void print( std::ostream& out ) const
//  {
//    out << "Irecv Request: ID: " << this->get_id()
//        << ", Channel: " << this->get_channel();
//  }
//private:
//};


#endif // D2G_REQUEST_H 
