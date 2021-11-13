
#include "ns3/core-module.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/net-device-container.h"
#include "ns3/csma-helper.h"
#include "ns3/bridge-helper.h"
#include "puente_helper.h"


NS_LOG_COMPONENT_DEFINE("PuenteHelper");


using namespace ns3;


Ptr<Node> PuenteHelper (NodeContainer nodosLan, NetDeviceContainer & d_nodosLan, PuenteConfig_t aditionalConfig){
	
	NetDeviceContainer d_puertosBridge;
	CsmaHelper         h_csma;
	BridgeHelper       h_bridge;
	Ptr<Node>          puente = CreateObject<Node>();
	
	// ADITIONAL CONFIG
	h_csma.SetChannelAttribute("DataRate", DataRateValue(aditionalConfig.regimenBinario));
	
	for (NodeContainer::Iterator indice = nodosLan.Begin (); indice != nodosLan.End (); indice++){
			
		NetDeviceContainer enlace = h_csma.Install(NodeContainer (*indice, puente));
		d_nodosLan.Add (enlace.Get (0));
		d_puertosBridge.Add (enlace.Get (1));
		
	}
	
	h_bridge.Install (puente, d_puertosBridge);
	
	Ptr<NetDevice> bridgePort = d_puertosBridge.Get(0);
	Ptr<CsmaChannel> channel = bridgePort->GetChannel()->GetObject<CsmaChannel>();
	DataRateValue dataRate;
	channel->GetAttribute("DataRate", dataRate);
	
	NS_LOG_INFO("Creado puente: (regimen_binario=" << dataRate.Get() << ")");
	
	return puente;
	
}
