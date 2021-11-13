#ifndef puente_helper_h
#define puente_helper_h

#include "ns3/core-module.h"
#include "ns3/node.h"


using namespace ns3;

#define DEFFAULT_CONFIG {DataRate("100Mb/s")}

typedef struct{
	DataRate regimenBinario;
} PuenteConfig_t;


Ptr<Node> PuenteHelper (NodeContainer nodosLan, NetDeviceContainer & d_nodosLan, PuenteConfig_t aditionalConfig = DEFFAULT_CONFIG);


#endif