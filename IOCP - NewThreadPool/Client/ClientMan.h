#pragma once
#include <winsock2.h>
#include <vector>
#include <string>

#include "..\TSingleton.h"

class Client;

using namespace std;

class ClientMan : public TSingleton<ClientMan>
{
private:
	static void CALLBACK WorkerRemoveClient(PTP_CALLBACK_INSTANCE /* Instance */, PVOID Context);

public:
	ClientMan(void);
	virtual ~ClientMan(void);

	void AddClients(int numClients);
	void ConnectClients(const char* ip, u_short port);
	void ShutdownClients();
	void RemoveClients();
	void PostRemoveClient(Client* client);
	void Send(const string& msg);

	bool IsAlive(const Client* client);
	size_t GetNumClients();

private:
	void RemoveClient(Client* client);


private:
	typedef vector<Client*> ClientList;
	ClientList m_listClient;

	CRITICAL_SECTION m_CSForClients;
};
