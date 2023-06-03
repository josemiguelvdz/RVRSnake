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
        memcpy(index, &info.createPlayer.newPlayerId, sizeof(uint8_t));
        index += sizeof(uint8_t);

        memcpy(index, &info.createPlayer.newPlayerName, NAME_CHARACTER_LIMIT * sizeof(char));
        index += NAME_CHARACTER_LIMIT * sizeof(char);
        break;
    case PACKETTYPE_SYNCSNAKE:
        memcpy(index, &info.snake.id, sizeof(uint8_t));
        index += sizeof(uint8_t);

        memcpy(index, &info.snake.orientationX, sizeof(_Float32));
        index += sizeof(_Float32);

        memcpy(index, &info.snake.orientationY, sizeof(_Float32));
        index += sizeof(_Float32);
        break;
    case PACKETTYPE_SYNCAPPLE:
        memcpy(index, &info.apple.positionX, sizeof(_Float32));
        index += sizeof(_Float32);

        memcpy(index, &info.apple.positionY, sizeof(_Float32));
        index += sizeof(_Float32);

        memcpy(index, &info.apple.eaten, sizeof(bool));
        index += sizeof(bool);

        memcpy(index, &info.apple.snakeId, sizeof(uint8_t));
        index += sizeof(uint8_t);
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
    case PACKETTYPE_DISCONNECTIONREQUEST:
        memcpy(&info.disconnectionRequest.playerId, index, sizeof(uint8_t));
        index += sizeof(uint8_t);
        break;
    case PACKETTYPE_CREATEPLAYER:
        memcpy(&info.createPlayer.newPlayerId, index, sizeof(uint8_t));
        index += sizeof(uint8_t);

        memcpy(&info.createPlayer.newPlayerName, index, sizeof(NAME_CHARACTER_LIMIT * sizeof(char)));
        index += NAME_CHARACTER_LIMIT * sizeof(char);
        break;
    case PACKETTYPE_SYNCSNAKE:
        memcpy(&info.snake.id, index, sizeof(uint8_t));
        index += sizeof(uint8_t);

        memcpy(&info.snake.orientationX, index, sizeof(_Float32));
        index += sizeof(_Float32);

        memcpy(&info.snake.orientationY, index, sizeof(_Float32));
        index += sizeof(_Float32);
        break;
    case PACKETTYPE_SYNCAPPLE:
        memcpy(&info.apple.positionX, index, sizeof(_Float32));
        index += sizeof(_Float32);

        memcpy(&info.apple.positionY, index, sizeof(_Float32));
        index += sizeof(_Float32);

        memcpy(&info.apple.eaten, index, sizeof(bool));
        index += sizeof(bool);

        memcpy(&info.apple.snakeId, index, sizeof(uint8_t));
        index += sizeof(uint8_t);
        break;
    }

    return index - data;
}