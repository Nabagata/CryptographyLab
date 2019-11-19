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

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

#define ll long long int
#define pll pair<ll,ll>
#define MAXN 100
#define pb push_back

ll p,q,n,e,d,phi_n,M;
ll users;

vector< ll > public_keys[MAXN];
vector< pll > private_keys[MAXN];

ll N[MAXN];

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
	stringstream ss;
	ss<<s;
	ll rid,pid,C;

	ss>>rid; ss>>pid; ss>>C;
	
	ll M = ModularExponent(C,private_keys[rid][pid].first,N[rid]);

	cout<<"Plain text send : "<<M<<endl;

	return;
}

int main(int argc, char *argv[])
{
	cout<<"Enter the number of users : "; cin>>users;

	for(int i=0;i<users;i++)
	{
		cout<<"Enter p and q for user "<<i<<endl;
		cin>>p>>q;
		N[i] = p*q;
		phi_n = (p-1)*(q-1);
		cout<<"How many key pairs for user "<<i<<endl;
		int kp;
		cin>>kp;
		for(int j=0;j<kp;j++)
		{
			cout<<"Enter public key e( "<<j<<" ) for user "<<i<<" which is coprime to "<<phi_n<<endl;
			cin>>e;
			d = ModuloMultiplicativeInverse(e,phi_n);
			cout<<"Public Key = "<<e<<" private key = "<<d<<endl;
			public_keys[i].push_back(e);
			private_keys[i].push_back(make_pair(d,j));
		}
	}

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
	
	int sid,rid;
	ll pid;
	cout<<"Enter id of sender and reciever "<<endl; cin>>sid; cin>>rid;
	cout<<"Enter the message integer"<<endl;
	ll M;
	cin>>M;
	cout<<"Enter the public key id of user "<<rid<<"which is less than "<<public_keys[rid].size()<<endl;
	cin>>pid;

	//Encryption
	ll C = ModularExponent(M,public_keys[rid][pid],N[rid]);

	//Data formatting
	stringstream ss;
	string x,y,z;
	ss<<C; ss>>x;
	stringstream ss2;
	ss2<<pid; ss2>>y;
	stringstream ss3;
	ss3<<rid; ss3>>z;
	string msg="";

	msg+=z; msg+=" ";	msg+=y; msg+=" "; msg+=x;
	char data[1000];
	strcpy(data,msg.c_str());

	//Sending message
	Ptr<Socket> srcSocket = Socket::CreateSocket (nodes.Get(sid), TypeId::LookupByName ("ns3::UdpSocketFactory"));
	srcSocket->Bind ();
	srcSocket->SetRecvCallback (MakeCallback (&srcSocketRecv));

	Ptr<Socket> dstSocket = Socket::CreateSocket (nodes.Get(rid), TypeId::LookupByName ("ns3::UdpSocketFactory"));
	Ipv4Address dstaddr ( interfaces.GetAddress(rid) );
	uint16_t dstport = 8080;
	InetSocketAddress dst = InetSocketAddress (dstaddr, dstport);
	dstSocket->Bind (dst);
	dstSocket->SetRecvCallback (MakeCallback (&dstSocketRecv));


	cout<<"Sending message : "<<data<<endl;
	Simulator::Schedule (Seconds (1),&SendStuff, data, srcSocket, dstaddr, dstport);
	Simulator::Run ();
	Simulator::Destroy ();
	return 0;
}