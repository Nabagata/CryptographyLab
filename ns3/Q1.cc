#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "rsa.cpp"

using namespace ns3;

string publicKey,privateKey;

NS_LOG_COMPONENT_DEFINE ("SocketBoundRoutingExample");

void SendStuff (char *data,Ptr<Socket> sock, Ipv4Address dstaddr, uint16_t port)
{
  Ptr<Packet> p = Create<Packet> ();
  uint8_t buffer[1000];
  bzero((char*)buffer,100);
  uint32_t size;
  strcpy((char*)buffer,data);
  size = strlen((char*)buffer);
  // cout<<"APPLE:"<<size<<endl;
  Ptr<Packet> p1 = Create<Packet> (buffer,size);
  p->AddAtEnd(p1);
  sock->SendTo (p, 0, InetSocketAddress (dstaddr,port));
  return;
}

void srcSocketRecv (Ptr<Socket> socket)
{
  Address from;

  Ptr<Packet> packet = socket->RecvFrom (from);
  cout<<"Packet:"<<*packet<<endl;
  packet->RemoveAllPacketTags ();
  packet->RemoveAllByteTags ();
  unsigned char buffer[1000];
  packet->CopyData(buffer,1000);
  string msg = string((char*)buffer);
  cout<<"Source Received " << packet->GetSize () << " bytes from " << InetSocketAddress::ConvertFrom (from).GetIpv4 () << " Data: " << msg <<endl;
  string message = decrypt(privateKey,msg);
  cout<<"Decrypting...."<<endl;
  cout<<"Message: "<<message<<endl;
}

void dstSocketRecv (Ptr<Socket> socket)
{
  Address from;
  Ptr<Packet> packet = socket->RecvFrom (from);
  cout<<"Packet:"<<*packet<<" SIZE:"<<packet->GetSize()<<endl;
  packet->RemoveAllPacketTags ();
  packet->RemoveAllByteTags ();
  unsigned char buffer[1000];
  packet->CopyData(buffer,packet->GetSize());
  InetSocketAddress address = InetSocketAddress::ConvertFrom (from);
  cout<<"Destination Received " << packet->GetSize () << " bytes from " << address.GetIpv4 () << " Data:" <<buffer<<endl;
  cout<<"Sending Encrypted Message to Source..."<<endl;
  string src_pubKey = string((char*)buffer);
  cout<<"Public Key: "<<src_pubKey<<"_a"<<endl;
  string Message = "My Name Is Rishu!";
  string Cipher = encrypt(src_pubKey,Message);
  cout<<"Cipher: "<<Cipher<<endl;
  char data[1000];
  strcpy(data,Cipher.c_str());
  cout<<"data: "<<data<<endl;
  SendStuff (data, socket, address.GetIpv4 (), address.GetPort ());
}

int main (int argc, char *argv[])
{
  
  keygen(publicKey,privateKey);
  cout<<"Public Key: "<<publicKey<<"\tPrivate Key: "<<privateKey<<endl;
  string Message = "Hello World!";
  string Cipher = encrypt(publicKey,Message);
  cout<<"CIPHER:: "<<Cipher<<endl;
  string PlainText = decrypt(privateKey,Cipher);
  cout<<"PlainText::: "<<PlainText<<endl;

 /*-------------KEYGEN END-----------------*/

  CommandLine cmd;
  cmd.Parse (argc, argv);
  
  Time::SetResolution (Time::NS);
  // LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  // LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  //Config::SetDefault("ns3::Ipv4GlobalRouting::RandomEcmpRouting",BooleanValue(ECMProuting));

  NodeContainer nodes;
  nodes.Create (3);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer dev1,dev2;
  dev1 = pointToPoint.Install (nodes.Get(0),nodes.Get(1));
  dev2 = pointToPoint.Install (nodes.Get(1),nodes.Get(2));

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = address.Assign (dev1);
  
  address.SetBase ("10.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces1 = address.Assign (dev2);

  Ipv4GlobalRoutingHelper:: PopulateRoutingTables();


  Ptr<Socket> srcSocket = Socket::CreateSocket (nodes.Get(0), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  srcSocket->Bind ();
  srcSocket->SetRecvCallback (MakeCallback (&srcSocketRecv));

  Ptr<Socket> dstSocket = Socket::CreateSocket (nodes.Get(2), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  uint16_t dstport = 12345;
  Ipv4Address dstaddr ("10.0.0.2");
  InetSocketAddress dst = InetSocketAddress (dstaddr, dstport);
  dstSocket->Bind (dst);
  dstSocket->SetRecvCallback (MakeCallback (&dstSocketRecv));

  char data[1000];
  strcpy(data,publicKey.c_str());
 
  Packet::EnablePrinting();


  // AnimationInterface anim ("Q1.xml");
  // anim.SetConstantPosition (nodes.Get(0), 1.0, 10.0);
  // anim.SetConstantPosition (nodes.Get(1), 8.0, 10.0);
  // anim.SetConstantPosition (nodes.Get(2), 15.0, 10.0);

  Simulator::Schedule (Seconds (1),&SendStuff, data, srcSocket, dstaddr, dstport);

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
