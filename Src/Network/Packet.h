#pragma once
#include "Serializable.h"
#include "PacketType.h"

class Packet : public Serializable {
public:
	Packet();
	Packet(PacketType type, PacketInfo packetInfo);
	~Packet();

    void to_bin() override;
    int from_bin(char * data) override;

	PacketType packetType;
	PacketInfo packetInfo;
};