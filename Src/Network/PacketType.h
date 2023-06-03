#pragma once

#include <cstdint>

#define NAME_CHARACTER_LIMIT 8

// Tipos de paquete
enum PacketType : uint8_t {
	PACKETTYPE_CONNECTIONREQUEST,
	PACKETTYPE_DISCONNECTIONREQUEST,
	PACKETTYPE_CONNECTIONACCEPT,
	PACKETTYPE_CONNECTIONDENY,
	PACKETTYPE_CREATEPLAYER,
	PACKETTYPE_START,
	PACKETTYPE_SYNCSNAKE,
	PACKETTYPE_SYNCAPPLE,
	PACKETTYPE_HOSTQUIT,
	PACKETTYPE_CHANGETOCOLORSELECTION,
    PACKETTYPE_NULL
};

// Paquete que se manda al host para establecer la conexion
struct PacketConnectionRequest {
	char playerName[NAME_CHARACTER_LIMIT];
};

// Paquete que manda el servidor cuando acepta a un jugador
struct PacketAccept {
	uint8_t playerId;
	uint8_t color1, color2, color3, color4;
	char playerName1[NAME_CHARACTER_LIMIT];
	char playerName2[NAME_CHARACTER_LIMIT];
	char playerName3[NAME_CHARACTER_LIMIT];
	char playerName4[NAME_CHARACTER_LIMIT];
};

struct PacketDisconnectionRequest {
	uint8_t playerId;
};

struct PacketCreatePlayer{
	uint8_t newPlayerId;
	char newPlayerName[NAME_CHARACTER_LIMIT];
};

// Paquete para sincronizar a los jugadores
struct PacketSyncSnake {
	uint8_t id;

	_Float32 positionX;
    _Float32 positionY;

	_Float32 orientationX;
	_Float32 orientationY;

	bool alive;
	bool ate;
	bool turnNextPartToCorner;
};

// Paquete para sincronizar las manzanas
struct PacketSyncApple {
	uint8_t snakeId;

	_Float32 positionX;
    _Float32 positionY;

	bool eaten;
};

struct PacketChangeToColorSelection {
	uint8_t color1, color2, color3, color4;
	char playerName1[NAME_CHARACTER_LIMIT];
	char playerName2[NAME_CHARACTER_LIMIT];
	char playerName3[NAME_CHARACTER_LIMIT];
	char playerName4[NAME_CHARACTER_LIMIT];
};

union PacketInfo {
	PacketConnectionRequest connectionRequest;
	PacketAccept accept;
	PacketDisconnectionRequest disconnectionRequest;
	PacketCreatePlayer createPlayer;
	PacketSyncSnake snake;
	PacketSyncApple apple;
	PacketChangeToColorSelection changeToColorSelection;
};