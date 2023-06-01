#pragma once

#include <cstdint>

#define NAME_CHARACTER_LIMIT 8

// Tipos de paquete
enum PacketType : uint8_t {
	PACKETTYPE_START,
	PACKETTYPE_ACCEPT,
	PACKETTYPE_DENY,
	PACKETTYPE_COLORCONTEXT,
	PACKETTYPE_COLORREQUEST,
	PACKETTYPE_COLORACCEPT,
	PACKETTYPE_COLORDENY,
	PACKETTYPE_NAME,
	PACKETTYPE_UPDATE,
	PACKETTYPE_SYNCSNAKE,
	PACKETTYPE_SYNCAPPLE,
	PACKETTYPE_ENDGAME,
	PACKETTYPE_QUIT,
    PACKETTYPE_NULL
};

// Paquete que manda el servidor cuando acepta a un jugador
struct PacketAccept {
	uint8_t playerId;
	char playerName[NAME_CHARACTER_LIMIT];
};

// Paquete para mandar nombres
struct PacketName {
	char playerName[NAME_CHARACTER_LIMIT];
};

// Paquete para comenzar juego
struct PacketStartGame {
	
};

// Paquete para sincronizar a los jugadores
struct PacketSyncSnake {
	uint8_t snakeId;

	uint8_t positionX;
	uint8_t positionY;

	uint8_t orientationX;
	uint8_t orientationY;
};

// Paquete para sincronizar las manzanas
struct PacketSyncApple {
	uint8_t positionX;
    uint8_t positionY;

	bool eaten;
};

union PacketInfo {
	PacketAccept accept;
	PacketName name;
	PacketStartGame startGame;
	PacketSyncSnake snake;
	PacketSyncApple apple;
};