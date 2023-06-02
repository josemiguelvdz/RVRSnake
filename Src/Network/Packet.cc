#include "Packet.h"
#include <string.h>

Packet::Packet() : type(PACKETTYPE_NULL) {

}

Packet::Packet(PacketType type, PacketInfo packetInfo) : type(PACKETTYPE_NULL), info(packetInfo) {

}

Packet::~Packet() {

}

void Packet::to_bin() {
    _size = sizeof(uint8_t) + sizeof(PacketInfo);
    alloc_data(_size);

    memset(_data, 0, _size);

    char* index = _data;

    memcpy(index, &type, sizeof(uint8_t));
    index += sizeof(uint8_t);

    switch (type){
        case PACKETTYPE_CONNECTIONREQUEST:
            memcpy(index, info.connectionRequest.playerName, NAME_CHARACTER_LIMIT * sizeof(char));
            index += NAME_CHARACTER_LIMIT * sizeof(char);
            break;
        case PACKETTYPE_DISCONNECTIONREQUEST:
            memcpy(index, &info.disconnectionRequest.playerId, sizeof(uint8_t));
            index += sizeof(uint8_t);
        break;
        case PACKETTYPE_CONNECTIONACCEPT:
            memcpy(index, &info.accept.playerId, sizeof(uint8_t));
            index += sizeof(uint8_t);

            memcpy(index, &info.accept.color1, sizeof(uint8_t));
            index += sizeof(uint8_t);

            memcpy(index, &info.accept.color2, sizeof(uint8_t));
            index += sizeof(uint8_t);

            memcpy(index, &info.accept.color3, sizeof(uint8_t));
            index += sizeof(uint8_t);

            memcpy(index, &info.accept.color4, sizeof(uint8_t));
            index += sizeof(uint8_t);

            memcpy(index, info.accept.playerName1, NAME_CHARACTER_LIMIT * sizeof(char));
            index += NAME_CHARACTER_LIMIT * sizeof(char);

            memcpy(index, info.accept.playerName2, NAME_CHARACTER_LIMIT * sizeof(char));
            index += NAME_CHARACTER_LIMIT * sizeof(char);

            memcpy(index, info.accept.playerName3, NAME_CHARACTER_LIMIT * sizeof(char));
            index += NAME_CHARACTER_LIMIT * sizeof(char);

            memcpy(index, info.accept.playerName4, NAME_CHARACTER_LIMIT * sizeof(char));
            index += NAME_CHARACTER_LIMIT * sizeof(char);
            break;
        case PACKETTYPE_CREATEPLAYER:
        break;
        case PACKETTYPE_SYNCSNAKE:
        break;
        case PACKETTYPE_SYNCAPPLE:
        break;
        case PACKETTYPE_NULL:
        break;
    }
}

int Packet::from_bin(char * data) {
    char* index = data;

    memcpy(&type, index, sizeof(uint8_t));
    index += sizeof(uint8_t);

    switch (type){
    case PACKETTYPE_CONNECTIONREQUEST:
        memcpy(info.connectionRequest.playerName, index, NAME_CHARACTER_LIMIT * sizeof(char));
        index += NAME_CHARACTER_LIMIT * sizeof(char);
    break;
    case PACKETTYPE_CONNECTIONACCEPT:
        memcpy(&info.accept.playerId, index, sizeof(uint8_t));
        index += sizeof(uint8_t);

        memcpy(&info.accept.color1, index, sizeof(uint8_t));
        index += sizeof(uint8_t);

        memcpy(&info.accept.color2, index, sizeof(uint8_t));
        index += sizeof(uint8_t);

        memcpy(&info.accept.color3, index, sizeof(uint8_t));
        index += sizeof(uint8_t);

        memcpy(&info.accept.color4, index, sizeof(uint8_t));
        index += sizeof(uint8_t);

        memcpy(&info.accept.playerName1, index, sizeof(NAME_CHARACTER_LIMIT * sizeof(char)));
        index += NAME_CHARACTER_LIMIT * sizeof(char);

        memcpy(&info.accept.playerName2, index, sizeof(NAME_CHARACTER_LIMIT * sizeof(char)));
        index += NAME_CHARACTER_LIMIT * sizeof(char);

        memcpy(&info.accept.playerName3, index, sizeof(NAME_CHARACTER_LIMIT * sizeof(char)));
        index += NAME_CHARACTER_LIMIT * sizeof(char);

        memcpy(&info.accept.playerName4, index, sizeof(NAME_CHARACTER_LIMIT * sizeof(char)));
        index += NAME_CHARACTER_LIMIT * sizeof(char);
        break;
    case PACKETTYPE_CONNECTIONDENY:
    break;
    case PACKETTYPE_DISCONNECTIONREQUEST:
        memcpy(&info.disconnectionRequest.playerId, index, sizeof(uint8_t));
        index += sizeof(uint8_t);
    break;
    case PACKETTYPE_CREATEPLAYER:
    break;
    case PACKETTYPE_SYNCSNAKE:
    break;
    case PACKETTYPE_SYNCAPPLE:
    break;
    case PACKETTYPE_HOSTQUIT:
    break;
    case PACKETTYPE_NULL:
    break;
    }

    return index - data;
}