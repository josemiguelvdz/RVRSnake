#include "Packet.h"

Packet::Packet() : type(PACKETTYPE_NULL) {

}

Packet::Packet(PacketType type, PacketInfo packetInfo) : type(PACKETTYPE_NULL), info(packetInfo) {

}

Packet::~Packet() {

}

void Packet::to_bin() {

}

int Packet::from_bin(char * data) {

}