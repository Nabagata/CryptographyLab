#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include <bits/stdc++.h>

using namespace ns3;
using namespace std;

#define ll long long int
#define pll pair<ll,ll>
#define MAXN 100
#define pb push_back

ll users,levels,M,n,phi_n,p,q,root=0;
ll sender,receiver;
pll key_of_level[10];
ll par[MAXN];
ll child[MAXN];

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


void mySendFunction()

void myRecvFunction(Ptr<Socket> socket)
{
	Address from;
	Ptr<Packet> packet = socket->RecvFrom (from);
	packet->RemoveAllPacketTags ();
	packet->RemoveAllByteTags ();
	unsigned char buffer[1000];
	packet->CopyData(buffer,packet->GetSize());
	InetSocketAddress address = InetSocketAddress::ConvertFrom (from);
	cout<<"Destination Received " << packet->GetSize () << " bytes from " << address.GetIpv4 () << endl;
	cout<<"Data recievied : "<<buffer<<endl;    

	char data[1000];
	strcpy(data,(char*)buffer);

	string s(data);
	stringstream ss;
	ss<<s;
	ll rid,sid,C,M;

	ss>>rid; ss>>sid; ss>>C;
	
	int mylevel = log2(rid);
	if(sid == par[rid])
	{
		M = ModularExponent(C,key_of_level[mylevel].second,n);



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
	}

	cout<<"Plain text send : "<<M<<endl;
}

int main(int argc, char *argv[])
{
	cout<<"Enter the number of users in the tree. Should be of the form 2^n-1..."<<endl;
	cin>>users;

	cout<<"Enter two primes p and q "<<endl;
	cin>>p>>q;
	n = p*q;
	phi_n = (p-1)*(q-1);

	levels = log2(users) + 1;
	for(int i=1;i<levels;i++) 
	{
		ll e,d;
		cout<<"Enter the public key shared in level "<<i<<" coprime to "<<phi_n<<endl;
		cin>>e;
		d = ModuloMultiplicativeInverse(e,phi_n);
		key_of_level[i] = make_pair(e,d);
	}

	int sid,rid;
	cout<<"Enter the sender and reciever id at same levels"<<endl;
	cin>>sid>>rid;

	if(log2(sid)!=log2(rid)) 
	{
		cout<<"Sender and reciever are from different levels. Exiting..."<<endl;
		return 0;
	}
	memset(par,0,sizeof par); 
	memset(child,0,sizeof child);
	root=1;

	ll current = sid;
	while(current!=root)
	{
		par[current] = current/2;
		current /= 2;
	}
	current = rid;
	while(current!=root)
	{
		child[current/2] = current;
		current /= 2;
	}
	sender = sid;
	receiver = rid;
	cout<<"Enter the integer message to be sent : "<<endl;
	cin>>M;





	NodeContainer nodes;
	nodes.Create (users);

	CsmaHelper csma;
	csma.SetChannelAttribute ("DataRate", StringValue ("100Mbps"));
  	csma.SetChannelAttribute ("Delay", TimeValue (NanoSeconds (6560)));

	NetDeviceContainer CsmaDevices;
	CsmaDevices = csma.Install (nodes);

	InternetStackHelper stack;
	stack.Install (nodes);

	Ipv4AddressHelper address;
	address.SetBase ("10.1.2.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces = address.Assign (CsmaDevices);

	Ipv4GlobalRoutingHelper:: PopulateRoutingTables();

	for(int i=0;i<users;i++)
	{
		uint16_t myport = 8000;
		Ptr<Socket> mySocket = Socket::CreateSocket (nodes.Get(i), TypeId::LookupByName ("ns3::UdpSocketFactory"));
		Ipv4Address myaddr ( interfaces.GetAddress(i) );
		
		InetSocketAddress my_ip_and_port = InetSocketAddress ( myaddr, myport+i );
		mySocket->Bind (my_ip_and_port);
		if(i!=0)
		{
			mySocket->SetRecvCallback (MakeCallback (&myRecvFunction));
		}
		else
		{
			mySocket->SetRecvCallback (MakeCallback (&rootRecvFunction));
		}
		
	}
	return 0;
}