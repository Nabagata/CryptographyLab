#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include <bits/stdc++.h>

using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

#define ll long long int
#define MAXN 70000000
#define pb push_back

ll p,q,n,ea,eb,da,db,phi_n,M;

ll ModularExponent(ll a, ll x, ll n)
{
  if( x==0 ) return 1;
  ll ans = 1;
  ll prd = ModularExponent(a,x/2,n);
  ans = ( prd%n * prd%n )%n;
  if( x&1 ) ans = ( ans%n * a%n)%n;
  return ans;
}

ll gcdExtended(ll a, ll b, ll *x, ll *y) 
{ 
    if (a == 0) 
    { 
        *x = 0, *y = 1; 
        return b; 
    } 
  
    ll x1, y1; 
    ll gcd = gcdExtended(b%a, a, &x1, &y1);  
    *x = y1 - (b/a) * x1; 
    *y = x1; 
    return gcd; 
} 

ll ModuloMultiplicativeInverse(ll a, ll b)
{
  ll x,y;
  gcdExtended(a,b,&x,&y);
  if(x<0) x+=b;
  return x;
}

void SendStuff (char *data,Ptr<Socket> sock, Ipv4Address dstaddr, uint16_t port)
{
    Ptr<Packet> p = Create<Packet> ();
    uint8_t buffer[1000];
    bzero((char*)buffer,1000);
    uint32_t size;
    strcpy((char*)buffer,data);
    size = strlen((char*)buffer);
    Ptr<Packet> p1 = Create<Packet> (buffer,size);
    p->AddAtEnd(p1);
    cout<<"Sending message "<<data<<endl;
    sock->SendTo (p, 0, InetSocketAddress (dstaddr,port));
    return;
}

void srcSocketRecv (Ptr<Socket> socket)
{

}

void dstSocketRecv (Ptr<Socket> socket)
{
    Address from;
    Ptr<Packet> packet = socket->RecvFrom (from);
    //cout<<"Packet:"<<*packet<<" SIZE:"<<packet->GetSize()<<endl;
    packet->RemoveAllPacketTags ();
    packet->RemoveAllByteTags ();
    unsigned char buffer[1000];
    packet->CopyData(buffer,packet->GetSize());
    InetSocketAddress address = InetSocketAddress::ConvertFrom (from);
    cout<<"Destination Received " << packet->GetSize () << " bytes from " << address.GetIpv4 () << " Data:" <<buffer<<endl;
    cout<<"Data recievied : "<<buffer<<endl;    

    char data[1000];
    strcpy(data,(char*)buffer);

    string s(data);
    ll Cdash;
    stringstream ss;
    ss<<s;
    ss>>Cdash;
    ll C = ModularExponent(Cdash,db,n);
    cout<<"First decryption = "<<C<<endl;
    ll Mdash = ModularExponent(C,ea,n);

    cout<<"Integer message recieved = "<<Mdash<<endl;
    return;
}

int main(int argc, char *argv[])
{

  	NodeContainer nodes;
  	nodes.Create (2);

  	PointToPointHelper pointToPoint;
  	pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  	pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  	NetDeviceContainer p2pDevices;
  	p2pDevices = pointToPoint.Install (nodes.Get(0),nodes.Get(1));

  	InternetStackHelper stack;
  	stack.Install (nodes);

  	Ipv4AddressHelper address;
  	address.SetBase ("10.1.2.0", "255.255.255.0");
  	Ipv4InterfaceContainer interfaces = address.Assign (p2pDevices);

  	Ipv4GlobalRoutingHelper:: PopulateRoutingTables();

  	Ptr<Socket> srcSocket = Socket::CreateSocket (nodes.Get(0), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  	srcSocket->Bind ();
    srcSocket->SetRecvCallback (MakeCallback (&srcSocketRecv));

  	Ptr<Socket> dstSocket = Socket::CreateSocket (nodes.Get(1), TypeId::LookupByName ("ns3::UdpSocketFactory"));
  	uint16_t dstport = 8080;
  	Ipv4Address dstaddr ("10.1.2.2");
  	InetSocketAddress dst = InetSocketAddress (dstaddr, dstport);
  	dstSocket->Bind (dst);
  	dstSocket->SetRecvCallback (MakeCallback (&dstSocketRecv));

    
    //Encrypting
    cout<<"Enter the two primes p and q"<<endl;
    cin>>p>>q;

    n = p*q;
    phi_n = (p-1)*(q-1);

    cout<<"Enter public key of a coprime to "<<phi_n<<endl;
    cin>>ea;
    da = ModuloMultiplicativeInverse(ea,phi_n);

    cout<<"PUa = "<<ea<<" PKa = "<<da<<endl;


    cout<<"Enter public key of b coprime to "<<phi_n<<endl;
    cin>>eb;
    db = ModuloMultiplicativeInverse(eb,phi_n);

    cout<<"PUb = "<<eb<<" PKb = "<<db<<endl;

    cout<<"Enter the message integer "<<endl;
    cin>>M;

    //Encryption
    ll C = ModularExponent(M,da,n);
    cout<<"C = "<<C<<endl;

    ll Cdash = ModularExponent(C,eb,n);
    cout<<"Cdash = "<<Cdash<<endl;
    stringstream ss; 
    ss<<Cdash;
    char data[1000];
    ss>>data;
    cout<<"Sending message "<<data<<endl;
    Simulator::Schedule (Seconds (1),&SendStuff, data, srcSocket, dstaddr, dstport);

    Simulator::Run ();
    Simulator::Destroy ();

  	return 0;
}