#pragma once

#include "common.hpp"

namespace gameboy
{
	class bus;

	class cpu
	{
		friend class bus;

	public:
		cpu(void);
		~cpu(void);

	private:

		class registers
		{
			friend class cpu;

		public:

			registers(void)
				: F(0x00), A(0x00), C(0x00), B(0x00), E(0x00), D(0x00), L(0x00), H(0x00), SP(0x0000), PC(0x0000)
			{

			}
			~registers(void)
			{

			}
		private:

			union
			{
				struct
				{
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
					std::uint8_t F;
					std::uint8_t A;
					std::uint8_t C;
					std::uint8_t B;
					std::uint8_t E;
					std::uint8_t D;
					std::uint8_t L;
					std::uint8_t H;
#else
					std::uint8_t A;
					std::uint8_t F;
					std::uint8_t B;
					std::uint8_t C;
					std::uint8_t D;
					std::uint8_t E;
					std::uint8_t H;
					std::uint8_t L;
#endif
				};
				struct
				{
					std::uint16_t AF;
					std::uint16_t BC;
					std::uint16_t DE;
					std::uint16_t HL;
				};
			};

			std::uint16_t SP;
			std::uint16_t PC;


			void print(void) const;

		};

		enum struct REGISTER : std::uint8_t
		{
			A,
			B,
			C,
			D,
			E,
			F,
			H,
			L,
			AF,
			BC,
			DE,
			HL,
			PC,
			SP,
		};

		enum struct OPCODE : std::uint8_t
		{
			NOP = 0x00,
			LD__BC_U16 = 0x01,
			LD__$BC_A = 0x02,
			INC__BC = 0x03,
			INC__B = 0x04,
			DEC__B = 0x05,
			LD__B_U8 = 0x06,
			RLCA = 0x07,
			LD__$U16_SP = 0x08,
			ADD__HL_BC = 0x09,
			LD__A_$BC = 0x0A,
			DEC__BC = 0x0B,
			INC__C = 0x0C,
			DEC__C = 0x0D,
			LD__C_U8 = 0x0E,
			RRCA = 0x0F,
			STOP = 0x10,
			LD__DE_U16 = 0x11,
			LD__$DE_A = 0x12,
			INC__DE = 0x13,
			INC__D = 0x14,
			DEC__D = 0x15,
			LD__D_U8 = 0x16,
			RLA = 0x17,
			JR__S8 = 0x18,
			ADD__HL_DE = 0x19,
			LD__A_$DE = 0x1A,
			DEC__DE = 0x1B,
			INC__E = 0x1C,
			DEC__E = 0x1D,
			LD__E_U8 = 0x1E,
			RRA = 0x1F,
			JR__NZ_S8 = 0x20,
			LD__HL_U16 = 0x21,
			LDI__$HL_A = 0x22,
			INC__HL = 0x23,
			INC__H = 0x24,
			DEC__H = 0x25,
			LD__H_U8 = 0x26,
			DAA = 0x27,
			JR__Z_S8 = 0x28,
			ADD__HL_HL = 0x29,
			LDI__A_$HL = 0x2A,
			DEC__HL = 0x2B,
			INC__L = 0x2C,
			DEC__L = 0x2D,
			LD__L_U8 = 0x2E,
			CPL = 0x2F,
			JR__NC_S8 = 0x30,
			LD__SP_U16 = 0x31,
			LDD__$HL_A = 0x32,
			INC__SP = 0x33,
			INC__$HL = 0x34,
			DEC__$HL = 0x35,
			LD__$HL_U8 = 0x36,
			SCF = 0x37,
			JR__C_S8 = 0x38,
			ADD__HL_SP = 0x39,
			LDD__A_$HL = 0x3A,
			DEC__SP = 0x3B,
			INC__A = 0x3C,
			DEC__A = 0x3D,
			LD__A_U8 = 0x3E,
			CCF = 0x3F,
			LD__B_B = 0x40,
			LD__B_C = 0x41,
			LD__B_D = 0x42,
			LD__B_E = 0x43,
			LD__B_H = 0x44,
			LD__B_L = 0x45,
			LD__B_$HL = 0x46,
			LD__B_A = 0x47,
			LD__C_B = 0x48,
			LD__C_C = 0x49,
			LD__C_D = 0x4A,
			LD__C_E = 0x4B,
			LD__C_H = 0x4C,
			LD__C_L = 0x4D,
			LD__C_$HL = 0x4E,
			LD__C_A = 0x4F,
			LD__D_B = 0x50,
			LD__D_C = 0x51,
			LD__D_D = 0x52,
			LD__D_E = 0x53,
			LD__D_H = 0x54,
			LD__D_L = 0x55,
			LD__D_$HL = 0x56,
			LD__D_A = 0x57,
			LD__E_B = 0x58,
			LD__E_C = 0x59,
			LD__E_D = 0x5A,
			LD__E_E = 0x5B,
			LD__E_H = 0x5C,
			LD__E_L = 0x5D,
			LD__E_$HL = 0x5E,
			LD__E_A = 0x5F,
			LD__H_B = 0x60,
			LD__H_C = 0x61,
			LD__H_D = 0x62,
			LD__H_E = 0x63,
			LD__H_H = 0x64,
			LD__H_L = 0x65,
			LD__H_$HL = 0x66,
			LD__H_A = 0x67,
			LD__L_B = 0x68,
			LD__L_C = 0x69,
			LD__L_D = 0x6A,
			LD__L_E = 0x6B,
			LD__L_H = 0x6C,
			LD__L_L = 0x6D,
			LD__L_$HL = 0x6E,
			LD__L_A = 0x6F,
			LD__$HL_B = 0x70,
			LD__$HL_C = 0x71,
			LD__$HL_D = 0x72,
			LD__$HL_E = 0x73,
			LD__$HL_H = 0x74,
			LD__$HL_L = 0x75,
			HALT = 0x76,
			LD__$HL_A = 0x77,
			LD__A_B = 0x78,
			LD__A_C = 0x79,
			LD__A_D = 0x7A,
			LD__A_E = 0x7B,
			LD__A_H = 0x7C,
			LD__A_L = 0x7D,
			LD__A_$HL = 0x7E,
			LD__A_A = 0x7F,
			ADD__A_B = 0x80,
			ADD__A_C = 0x81,
			ADD__A_D = 0x82,
			ADD__A_E = 0x83,
			ADD__A_H = 0x84,
			ADD__A_L = 0x85,
			ADD__A_$HL = 0x86,
			ADD__A_A = 0x87,
			ADC__A_B = 0x88,
			ADC__A_C = 0x89,
			ADC__A_D = 0x8A,
			ADC__A_E = 0x8B,
			ADC__A_H = 0x8C,
			ADC__A_L = 0x8D,
			ADC__A_$HL = 0x8E,
			ADC__A_A = 0x8F,
			SUB__A_B = 0x90,
			SUB__A_C = 0x91,
			SUB__A_D = 0x92,
			SUB__A_E = 0x93,
			SUB__A_H = 0x94,
			SUB__A_L = 0x95,
			SUB__A_$HL = 0x96,
			SUB__A_A = 0x97,
			SBC__A_B = 0x98,
			SBC__A_C = 0x99,
			SBC__A_D = 0x9A,
			SBC__A_E = 0x9B,
			SBC__A_H = 0x9C,
			SBC__A_L = 0x9D,
			SBC__A_$HL = 0x9E,
			SBC__A_A = 0x9F,
			AND__A_B = 0xA0,
			AND__A_C = 0xA1,
			AND__A_D = 0xA2,
			AND__A_E = 0xA3,
			AND__A_H = 0xA4,
			AND__A_L = 0xA5,
			AND__A_$HL = 0xA6,
			AND__A_A = 0xA7,
			XOR__A_B = 0xA8,
			XOR__A_C = 0xA9,
			XOR__A_D = 0xAA,
			XOR__A_E = 0xAB,
			XOR__A_H = 0xAC,
			XOR__A_L = 0xAD,
			XOR__A_$HL = 0xAE,
			XOR__A_A = 0xAF,
			OR__A_B = 0xB0,
			OR__A_C = 0xB1,
			OR__A_D = 0xB2,
			OR__A_E = 0xB3,
			OR__A_H = 0xB4,
			OR__A_L = 0xB5,
			OR__A_$HL = 0xB6,
			OR__A_A = 0xB7,
			CP__A_B = 0xB8,
			CP__A_C = 0xB9,
			CP__A_D = 0xBA,
			CP__A_E = 0xBB,
			CP__A_H = 0xBC,
			CP__A_L = 0xBD,
			CP__A_$HL = 0xBE,
			CP__A_A = 0xBF,
			RET__NZ = 0xC0,
			POP__BC = 0xC1,
			JP__NZ_U16 = 0xC2,
			JP__U16 = 0xC3,
			CALL__NZ_U16 = 0xC4,
			PUSH__BC = 0xC5,
			ADD__A_U8 = 0xC6,
			RST__00H = 0xC7,
			RET__Z = 0xC8,
			RET = 0xC9,
			JP__Z_U16 = 0xCA,
			PREFIX__CB = 0xCB,
			CALL__Z_U16 = 0xCC,
			CALL__U16 = 0xCD,
			ADC__A_U8 = 0xCE,
			RST__08H = 0xCF,
			RET__NC = 0xD0,
			POP__DE = 0xD1,
			JP__NC_U16 = 0xD2,
			CALL__NC_U16 = 0xD4,
			PUSH__DE = 0xD5,
			SUB__A_U8 = 0xD6,
			RST__10H = 0xD7,
			RET__C = 0xD8,
			RETI = 0xD9,
			JP__C_U16 = 0xDA,
			CALL__C_U16 = 0xDC,
			SBC__A_U8 = 0xDE,
			RST__18H = 0xDF,
			LDH__$U8_A = 0xE0,
			POP__HL = 0xE1,
			LD__$C_A = 0xE2,
			PUSH__HL = 0xE5,
			AND__A_U8 = 0xE6,
			RST__20H = 0xE7,
			ADD__SP_S8 = 0xE8,
			JP__$HL = 0xE9,
			LD__$U16_A = 0xEA,
			XOR__A_U8 = 0xEE,
			RST__28H = 0xEF,
			LDH__A_$U8 = 0xF0,
			POP__AF = 0xF1,
			LD__A_$C = 0xF2,
			DI = 0xF3,
			PUSH__AF = 0xF5,
			OR__A_U8 = 0xF6,
			RST__30H = 0xF7,
			LDHL__SP_S8 = 0xF8,
			LD__SP_HL = 0xF9,
			LD__A_$U16 = 0xFA,
			EI = 0xFB,
			CP__A_U8 = 0xFE,
			RST__38H = 0xFF,
		};

		enum struct PREFIXED_OPCODE : std::uint8_t
		{
			RLC__B = 0x00,
			RLC__C = 0x01,
			RLC__D = 0x02,
			RLC__E = 0x03,
			RLC__H = 0x04,
			RLC__L = 0x05,
			RLC__$HL = 0x06,
			RLC__A = 0x07,
			RRC__B = 0x08,
			RRC__C = 0x09,
			RRC__D = 0x0A,
			RRC__E = 0x0B,
			RRC__H = 0x0C,
			RRC__L = 0x0D,
			RRC__$HL = 0x0E,
			RRC__A = 0x0F,
			RL__B = 0x10,
			RL__C = 0x11,
			RL__D = 0x12,
			RL__E = 0x13,
			RL__H = 0x14,
			RL__L = 0x15,
			RL__$HL = 0x16,
			RL__A = 0x17,
			RR__B = 0x18,
			RR__C = 0x19,
			RR__D = 0x1A,
			RR__E = 0x1B,
			RR__H = 0x1C,
			RR__L = 0x1D,
			RR__$HL = 0x1E,
			RR__A = 0x1F,
			SLA__B = 0x20,
			SLA__C = 0x21,
			SLA__D = 0x22,
			SLA__E = 0x23,
			SLA__H = 0x24,
			SLA__L = 0x25,
			SLA__$HL = 0x26,
			SLA__A = 0x27,
			SRA__B = 0x28,
			SRA__C = 0x29,
			SRA__D = 0x2A,
			SRA__E = 0x2B,
			SRA__H = 0x2C,
			SRA__L = 0x2D,
			SRA__$HL = 0x2E,
			SRA__A = 0x2F,
			SWAP__B = 0x30,
			SWAP__C = 0x31,
			SWAP__D = 0x32,
			SWAP__E = 0x33,
			SWAP__H = 0x34,
			SWAP__L = 0x35,
			SWAP__$HL = 0x36,
			SWAP__A = 0x37,
			SRL__B = 0x38,
			SRL__C = 0x39,
			SRL__D = 0x3A,
			SRL__E = 0x3B,
			SRL__H = 0x3C,
			SRL__L = 0x3D,
			SRL__$HL = 0x3E,
			SRL__A = 0x3F,
			BIT__0_B = 0x40,
			BIT__0_C = 0x41,
			BIT__0_D = 0x42,
			BIT__0_E = 0x43,
			BIT__0_H = 0x44,
			BIT__0_L = 0x45,
			BIT__0_$HL = 0x46,
			BIT__0_A = 0x47,
			BIT__1_B = 0x48,
			BIT__1_C = 0x49,
			BIT__1_D = 0x4A,
			BIT__1_E = 0x4B,
			BIT__1_H = 0x4C,
			BIT__1_L = 0x4D,
			BIT__1_$HL = 0x4E,
			BIT__1_A = 0x4F,
			BIT__2_B = 0x50,
			BIT__2_C = 0x51,
			BIT__2_D = 0x52,
			BIT__2_E = 0x53,
			BIT__2_H = 0x54,
			BIT__2_L = 0x55,
			BIT__2_$HL = 0x56,
			BIT__2_A = 0x57,
			BIT__3_B = 0x58,
			BIT__3_C = 0x59,
			BIT__3_D = 0x5A,
			BIT__3_E = 0x5B,
			BIT__3_H = 0x5C,
			BIT__3_L = 0x5D,
			BIT__3_$HL = 0x5E,
			BIT__3_A = 0x5F,
			BIT__4_B = 0x60,
			BIT__4_C = 0x61,
			BIT__4_D = 0x62,
			BIT__4_E = 0x63,
			BIT__4_H = 0x64,
			BIT__4_L = 0x65,
			BIT__4_$HL = 0x66,
			BIT__4_A = 0x67,
			BIT__5_B = 0x68,
			BIT__5_C = 0x69,
			BIT__5_D = 0x6A,
			BIT__5_E = 0x6B,
			BIT__5_H = 0x6C,
			BIT__5_L = 0x6D,
			BIT__5_$HL = 0x6E,
			BIT__5_A = 0x6F,
			BIT__6_B = 0x70,
			BIT__6_C = 0x71,
			BIT__6_D = 0x72,
			BIT__6_E = 0x73,
			BIT__6_H = 0x74,
			BIT__6_L = 0x75,
			BIT__6_$HL = 0x76,
			BIT__6_A = 0x77,
			BIT__7_B = 0x78,
			BIT__7_C = 0x79,
			BIT__7_D = 0x7A,
			BIT__7_E = 0x7B,
			BIT__7_H = 0x7C,
			BIT__7_L = 0x7D,
			BIT__7_$HL = 0x7E,
			BIT__7_A = 0x7F,
			RES__0_B = 0x80,
			RES__0_C = 0x81,
			RES__0_D = 0x82,
			RES__0_E = 0x83,
			RES__0_H = 0x84,
			RES__0_L = 0x85,
			RES__0_$HL = 0x86,
			RES__0_A = 0x87,
			RES__1_B = 0x88,
			RES__1_C = 0x89,
			RES__1_D = 0x8A,
			RES__1_E = 0x8B,
			RES__1_H = 0x8C,
			RES__1_L = 0x8D,
			RES__1_$HL = 0x8E,
			RES__1_A = 0x8F,
			RES__2_B = 0x90,
			RES__2_C = 0x91,
			RES__2_D = 0x92,
			RES__2_E = 0x93,
			RES__2_H = 0x94,
			RES__2_L = 0x95,
			RES__2_$HL = 0x96,
			RES__2_A = 0x97,
			RES__3_B = 0x98,
			RES__3_C = 0x99,
			RES__3_D = 0x9A,
			RES__3_E = 0x9B,
			RES__3_H = 0x9C,
			RES__3_L = 0x9D,
			RES__3_$HL = 0x9E,
			RES__3_A = 0x9F,
			RES__4_B = 0xA0,
			RES__4_C = 0xA1,
			RES__4_D = 0xA2,
			RES__4_E = 0xA3,
			RES__4_H = 0xA4,
			RES__4_L = 0xA5,
			RES__4_$HL = 0xA6,
			RES__4_A = 0xA7,
			RES__5_B = 0xA8,
			RES__5_C = 0xA9,
			RES__5_D = 0xAA,
			RES__5_E = 0xAB,
			RES__5_H = 0xAC,
			RES__5_L = 0xAD,
			RES__5_$HL = 0xAE,
			RES__5_A = 0xAF,
			RES__6_B = 0xB0,
			RES__6_C = 0xB1,
			RES__6_D = 0xB2,
			RES__6_E = 0xB3,
			RES__6_H = 0xB4,
			RES__6_L = 0xB5,
			RES__6_$HL = 0xB6,
			RES__6_A = 0xB7,
			RES__7_B = 0xB8,
			RES__7_C = 0xB9,
			RES__7_D = 0xBA,
			RES__7_E = 0xBB,
			RES__7_H = 0xBC,
			RES__7_L = 0xBD,
			RES__7_$HL = 0xBE,
			RES__7_A = 0xBF,
			SET__0_B = 0xC0,
			SET__0_C = 0xC1,
			SET__0_D = 0xC2,
			SET__0_E = 0xC3,
			SET__0_H = 0xC4,
			SET__0_L = 0xC5,
			SET__0_$HL = 0xC6,
			SET__0_A = 0xC7,
			SET__1_B = 0xC8,
			SET__1_C = 0xC9,
			SET__1_D = 0xCA,
			SET__1_E = 0xCB,
			SET__1_H = 0xCC,
			SET__1_L = 0xCD,
			SET__1_$HL = 0xCE,
			SET__1_A = 0xCF,
			SET__2_B = 0xD0,
			SET__2_C = 0xD1,
			SET__2_D = 0xD2,
			SET__2_E = 0xD3,
			SET__2_H = 0xD4,
			SET__2_L = 0xD5,
			SET__2_$HL = 0xD6,
			SET__2_A = 0xD7,
			SET__3_B = 0xD8,
			SET__3_C = 0xD9,
			SET__3_D = 0xDA,
			SET__3_E = 0xDB,
			SET__3_H = 0xDC,
			SET__3_L = 0xDD,
			SET__3_$HL = 0xDE,
			SET__3_A = 0xDF,
			SET__4_B = 0xE0,
			SET__4_C = 0xE1,
			SET__4_D = 0xE2,
			SET__4_E = 0xE3,
			SET__4_H = 0xE4,
			SET__4_L = 0xE5,
			SET__4_$HL = 0xE6,
			SET__4_A = 0xE7,
			SET__5_B = 0xE8,
			SET__5_C = 0xE9,
			SET__5_D = 0xEA,
			SET__5_E = 0xEB,
			SET__5_H = 0xEC,
			SET__5_L = 0xED,
			SET__5_$HL = 0xEE,
			SET__5_A = 0xEF,
			SET__6_B = 0xF0,
			SET__6_C = 0xF1,
			SET__6_D = 0xF2,
			SET__6_E = 0xF3,
			SET__6_H = 0xF4,
			SET__6_L = 0xF5,
			SET__6_$HL = 0xF6,
			SET__6_A = 0xF7,
			SET__7_B = 0xF8,
			SET__7_C = 0xF9,
			SET__7_D = 0xFA,
			SET__7_E = 0xFB,
			SET__7_H = 0xFC,
			SET__7_L = 0xFD,
			SET__7_$HL = 0xFE,
			SET__7_A = 0xFF,
		};

		enum struct TEMPLATED_OPCODE : std::uint8_t
		{
			EMPTY,
			ADC__A_$HL,
			ADC__A_R,
			ADC__A_U8,
			ADD__A_$HL,
			ADD__A_R,
			ADD__A_U8,
			ADD__HL_RR,
			ADD__SP_S8,
			AND__A_$HL,
			AND__A_R,
			AND__A_U8,
			BIT__n_$HL,
			BIT__n_R,
			CALL__CC_U16_b,
			CALL__CC_U16_nb,
			CALL__U16,
			CCF,
			CP__A_$HL,
			CP__A_R,
			CP__A_U8,
			CPL,
			DAA,
			DEC__$HL,
			DEC__R,
			DEC__RR,
			DI,
			EI,
			HALT,
			INC__$HL,
			INC__R,
			INC__RR,
			JP__$HL,
			JP__CC_U16_b,
			JP__CC_U16_nb,
			JP__U16,
			JR__CC_S8_b,
			JR__CC_S8_nb,
			JR__S8,
			LD__$R_R,
			LD__$RR_R,
			LD__$RR_U8,
			LD__$U16_R,
			LD__$U16_RR,
			LDHL__SP_S8,
			LD__R_$R,
			LD__R_$RR,
			LD__R_$U16,
			LD__R_R,
			LD__R_U8,
			LD__RR_RR,
			LD__RR_U16,
			LDD__$HL_R,
			LDD__R_$HL,
			LDH__$U8_R,
			LDH__R_$U8,
			LDI__$HL_R,
			LDI__R_$HL,
			NOP,
			OR__A_$HL,
			OR__A_R,
			OR__A_U8,
			POP__RR,
			PREFIX__CB,
			PUSH__RR,
			RES__n_$HL,
			RES__n_R,
			RET,
			RET__CC_b,
			RET__CC_nb,
			RETI,
			RL__$HL,
			RL__R,
			RLA,
			RLC__$HL,
			RLC__R,
			RLCA,
			RR__$HL,
			RR__R,
			RRA,
			RRC__$HL,
			RRC__R,
			RRCA,
			RST__nH,
			SBC__A_$HL,
			SBC__A_R,
			SBC__A_U8,
			SCF,
			SET__n_$HL,
			SET__n_R,
			SLA__$HL,
			SLA__R,
			SRA__$HL,
			SRA__R,
			SRL__$HL,
			SRL__R,
			STOP__0,
			SUB__A_$HL,
			SUB__A_R,
			SUB__A_U8,
			SWAP__$HL,
			SWAP__R,
			XOR__A_$HL,
			XOR__A_R,
			XOR__A_U8
		};

		static const std::map<OPCODE, std::string> OPCODE_MNEMONIC;
		static const std::map<PREFIXED_OPCODE, std::string> PREFIXED_OPCODE_MNEMONIC;

		static const std::map<TEMPLATED_OPCODE, std::uint8_t> TEMPLATED_OPCODE_CYCLES;
		//static const std::map<PREFIXED_OPCODE, std::uint8_t> PREFIXED_OPCODE_CYCLES;

		static void print_opcode(const OPCODE&, const std::uint16_t&);
		static void print_opcode(const PREFIXED_OPCODE&, const std::uint16_t&);

		void print_argument(const std::uint8_t&);
		void print_argument(const std::uint16_t&);
		void print_argument(const std::int8_t&);


		bus* _bus;
		registers _registers;
		bool _ime;

		bool _halted;

		std::uint8_t execute_instruction(const bool&);
		std::uint8_t handle_interrupts(void);

		enum struct FLAG : std::uint8_t
		{
			Z = 0x07,
			N = 0x06,
			H = 0x05,
			C = 0x04,
		};

		static bool get_bit(const std::uint8_t&, const std::uint8_t&);
		static void set_bit(const std::uint8_t&, std::uint8_t&);
		static void reset_bit(const std::uint8_t&, std::uint8_t&);

		void set_flag(const FLAG&);
		void reset_flag(const FLAG&);
		bool get_flag(const FLAG&);

		struct carries
		{
			bool H;
			bool C;
		};

		template<typename T, std::uint8_t n>
		bool carry(const std::function<T(T, T)>, const T&, const T&);

		carries addition_carries(const std::uint8_t&, const std::uint8_t&);
		carries addition_carries(const std::uint16_t&, const std::uint16_t&);
		//carries addition_carries(const std::uint16_t&, const std::uint8_t&);

		carries subtraction_carries(const std::uint8_t&, const std::uint8_t&);
		carries subtraction_carries(const std::uint16_t&, const std::uint16_t&);
		//carries subtraction_carries(const std::uint16_t&, const std::uint8_t&);


		std::variant<std::uint8_t*,std::uint16_t*> register_ptr(const REGISTER&);

		void _ADC__A_U8(const std::uint8_t&);
		const std::uint8_t& ADC__A_U8();
		const std::uint8_t& ADC__A_R(const REGISTER&);
		const std::uint8_t& ADC__A_$HL();

		void _ADD__A_U8(const std::uint8_t&);
		const std::uint8_t& ADD__A_U8();
		const std::uint8_t& ADD__A_R(const REGISTER&);
		const std::uint8_t& ADD__A_$HL();

		void _ADD__HL_U16(const std::uint16_t&);
		const std::uint8_t& ADD__HL_RR(const REGISTER&);

		void _ADD__SP_S8(const std::int8_t&);
		const std::uint8_t& ADD__SP_S8();

		void _SBC__A_U8(const std::uint8_t&);
		const std::uint8_t& SBC__A_U8();
		const std::uint8_t& SBC__A_R(const REGISTER&);
		const std::uint8_t& SBC__A_$HL();

		void _SUB__A_U8(const std::uint8_t&);
		const std::uint8_t& SUB__A_U8();
		const std::uint8_t& SUB__A_R(const REGISTER&);
		const std::uint8_t& SUB__A_$HL();

		void _AND__A_U8(const std::uint8_t&);
		const std::uint8_t& AND__A_U8();
		const std::uint8_t& AND__A_R(const REGISTER&);
		const std::uint8_t& AND__A_$HL();

		void _OR__A_U8(const std::uint8_t&);
		const std::uint8_t& OR__A_U8();
		const std::uint8_t& OR__A_R(const REGISTER&);
		const std::uint8_t& OR__A_$HL();

		void _XOR__A_U8(const std::uint8_t&);
		const std::uint8_t& XOR__A_U8();
		const std::uint8_t& XOR__A_R(const REGISTER&);
		const std::uint8_t& XOR__A_$HL();

		const std::uint8_t& PREFIX_CB();

		void _BIT__n_U8(const std::uint8_t&, const std::uint8_t&);
		const std::uint8_t& BIT__n_R(const std::uint8_t&, const REGISTER&);
		const std::uint8_t& BIT__n_$HL(const std::uint8_t&);
		void _RES__n_U8(const std::uint8_t&, std::uint8_t&);
		const std::uint8_t& RES__n_R(const std::uint8_t&, const REGISTER&);
		const std::uint8_t& RES__n_$HL(const std::uint8_t&);
		void _SET__n_U8(const std::uint8_t&, std::uint8_t&);
		const std::uint8_t& SET__n_R(const std::uint8_t&, const REGISTER&);
		const std::uint8_t& SET__n_$HL(const std::uint8_t&);

		void _CP__A_U8(const std::uint8_t&);
		const std::uint8_t& CP__A_U8();
		const std::uint8_t& CP__A_R(const REGISTER&);
		const std::uint8_t& CP__A_$HL(void);

		void _DEC__U16(std::uint16_t&);
		void _DEC__U8(std::uint8_t&);
		const std::uint8_t& DEC__RR(const REGISTER&);
		const std::uint8_t& DEC__R(const REGISTER&);
		const std::uint8_t& DEC__$HL();

		void _INC__U16(std::uint16_t&);
		void _INC__U8(std::uint8_t&);
		const std::uint8_t& INC__RR(const REGISTER&);
		const std::uint8_t& INC__R(const REGISTER&);
		const std::uint8_t& INC__$HL();

		const std::uint8_t& HALT();

		void _LD__U8_U8(std::uint8_t&, const std::uint8_t&);
		const std::uint8_t& LD__R_U8(const REGISTER&);
		const std::uint8_t& LD__R_R(const REGISTER&, const REGISTER&);
		const std::uint8_t& LD__R_$RR(const REGISTER&, const REGISTER&);
		const std::uint8_t& LD__$RR_R(const REGISTER&, const REGISTER&);
		const std::uint8_t& LD__$RR_U8(const REGISTER&); //<


		const std::uint8_t& LDD__$HL_R(const REGISTER&);
		const std::uint8_t& LDD__R_$HL(const REGISTER&);
		const std::uint8_t& LDI__$HL_R(const REGISTER&);
		const std::uint8_t& LDI__R_$HL(const REGISTER&);

		const std::uint8_t& LD__$R_R(const REGISTER&, const REGISTER&);
		const std::uint8_t& LD__R_$R(const REGISTER&, const REGISTER&);

		const std::uint8_t& LDH__$U8_R(const REGISTER&);
		const std::uint8_t& LDH__R_$U8(const REGISTER&);

		void _LD__U16_U16(std::uint16_t&, const std::uint16_t&);
		const std::uint8_t& LD__RR_U16(const REGISTER&);
		const std::uint8_t& LD__RR_RR(const REGISTER&, const REGISTER&);
		const std::uint8_t& LD__$U16_RR(const REGISTER&);
		const std::uint8_t& LD__$U16_R(const REGISTER&);
		const std::uint8_t& LD__R_$U16(const REGISTER&);

		void _LDHL__SP_S8(const std::int8_t&);
		const std::uint8_t& LDHL__SP_S8();

		const std::uint8_t& NOP();

		void _PUSH__U16(const std::uint16_t&);
		const std::uint8_t& PUSH__RR(const REGISTER&);

		void _POP__U16(std::uint16_t&);
		const std::uint8_t& POP__RR(const REGISTER&);
		
		const std::uint8_t& RST__nH(const std::uint8_t&);

		void _RL__U8(std::uint8_t&);
		const std::uint8_t& RL__R(const REGISTER&);
		const std::uint8_t& RL__$HL();

		void _RLC__U8(std::uint8_t&);
		const std::uint8_t& RLC__R(const REGISTER&);
		const std::uint8_t& RLC__$HL();

		void _RR__U8(std::uint8_t&);
		const std::uint8_t& RR__R(const REGISTER&);
		const std::uint8_t& RR__$HL();

		void _RRC__U8(std::uint8_t&);
		const std::uint8_t& RRC__R(const REGISTER&);
		const std::uint8_t& RRC__$HL();

		const std::uint8_t& RLA();
		const std::uint8_t& RLCA();
		const std::uint8_t& RRA();
		const std::uint8_t& RRCA();

		void _SLA__U8(std::uint8_t&);
		const std::uint8_t& SLA__R(const REGISTER&);
		const std::uint8_t& SLA__$HL();

		void _SRA__U8(std::uint8_t&);
		const std::uint8_t& SRA__R(const REGISTER&);
		const std::uint8_t& SRA__$HL();

		void _SRL__U8(std::uint8_t&);
		const std::uint8_t& SRL__R(const REGISTER&);
		const std::uint8_t& SRL__$HL();

		void _SWAP__U8(std::uint8_t&);
		const std::uint8_t& SWAP__R(const REGISTER&);
		const std::uint8_t& SWAP__$HL();

		enum struct FLAG_CONDITION : std::uint8_t
		{
			NZ,
			Z,
			NC,
			C,
		};

		bool test_flag_condition(const FLAG_CONDITION&);

		void _JP__U16(const std::uint16_t&);
		const std::uint8_t& JP__U16();
		const std::uint8_t& JP__CC_U16(const FLAG_CONDITION&);
		const std::uint8_t& JP__$HL();

		void _JR__S8(const std::int8_t&);
		const std::uint8_t& JR__S8();
		const std::uint8_t& JR__CC_S8(const FLAG_CONDITION&);

		void _CALL__U16(const std::uint16_t&);
		const std::uint8_t& CALL__U16();
		const std::uint8_t& CALL__CC_U16(const FLAG_CONDITION&);

		void _RET();
		const std::uint8_t& RET();
		const std::uint8_t& RET__CC(const FLAG_CONDITION&);

		const std::uint8_t& RETI();

		enum struct INTERRUPT : std::uint8_t
		{
			VBlank = 0x00,
			LCD_STAT = 0x01,
			Timer = 0x02,
			Serial = 0x03,
			Joypad = 0x04,
		};
		static const std::array<INTERRUPT,5> INTERRUPTS;

		static const std::map<INTERRUPT, std::uint8_t> INTERRUPT_VECTOR;

		bool interrupt_enabled(const INTERRUPT&);
		bool interrupt_requested(const INTERRUPT&);

		void IME(const bool&);
		const std::uint8_t& DI();
		const std::uint8_t& EI();

		const std::uint8_t& DAA();

		const std::uint8_t& CPL();
		const std::uint8_t& CCF();
		const std::uint8_t& SCF();

	public:

		void run(void);
		
		const std::uint16_t& PC(void);
		std::uint8_t next(void);

		void initialise(const std::uint8_t&, const std::uint8_t&, const std::uint8_t&, const std::uint8_t&, const std::uint8_t&, const std::uint8_t&, const std::uint8_t&, const std::uint8_t&, const std::uint16_t&, const std::uint16_t&);

		void dump(std::ofstream&);
		void load_dump(std::ifstream&);

		void hook(void);
	};

}
