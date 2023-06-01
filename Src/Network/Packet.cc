#include "Packet.h"

Packet::Packet() : packetType(PACKETTYPE_NULL) {

}

Packet::Packet(PacketType type, PacketInfo packetInfo) : packetType(PACKETTYPE_NULL), packetInfo(packetInfo) {

}

Packet::~Packet() {

}

void Packet::to_bin() {

}

int Packet::from_bin(char * data) {

}