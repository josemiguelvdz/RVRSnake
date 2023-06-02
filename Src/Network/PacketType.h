#pragma once

#include <cstdint>

#define NAME_CHARACTER_LIMIT 8

// Tipos de paquete
enum PacketType : uint8_t {
	PACKETTYPE_CONNECTIONREQUEST,
	PACKETTYPE_DISCONNECTIONREQUEST,
	PACKETTYPE_CONNECTIONACCEPT,
	PACKETTYPE_CONNECTIONDENY,
	PACKETTYPE_DISCONNECTIONACCEPT,
	PACKETTYPE_CREATEPLAYER,
	PACKETTYPE_COLORREQUEST,
	PACKETTYPE_COLORACCEPT,
	PACKETTYPE_COLORDENY,
	PACKETTYPE_COLORCHANGE,
	PACKETTYPE_SYNCSNAKE,
	PACKETTYPE_SYNCAPPLE,
	PACKETTYPE_QUIT,
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

struct PacketColorRequest {
	uint8_t playerId;
	uint8_t requestedColor;
};

struct PacketColorChange {
	uint8_t playerId;
	uint8_t newColor;
};

struct PacketColorAccept {
	uint8_t color1, color2, color3, color4;
};

struct PacketCreatePlayer{
	uint8_t newPlayerId;
	char newPlayerName[NAME_CHARACTER_LIMIT];
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
	PacketColorRequest colorRequest;
	PacketColorChange colorChange;
	PacketColorAccept colorAccept;
	PacketCreatePlayer createPlayer;
	PacketStartGame startGame;
	PacketSyncSnake snake;
	PacketSyncApple apple;
};