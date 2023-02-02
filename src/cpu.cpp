#include "cpu.hpp"
#include "bus.hpp"

using namespace gameboy;

const std::map<cpu::OPCODE, std::string> cpu::OPCODE_MNEMONIC = { 
	{cpu::OPCODE::NOP, "NOP"},
	{cpu::OPCODE::LD__BC_U16, "LD BC,u16"},
	{cpu::OPCODE::LD__$BC_A, "LD (BC),A"},
	{cpu::OPCODE::INC__BC, "INC BC"},
	{cpu::OPCODE::INC__B, "INC B"},
	{cpu::OPCODE::DEC__B, "DEC B"},
	{cpu::OPCODE::LD__B_U8, "LD B,u8"},
	{cpu::OPCODE::RLCA, "RLCA"},
	{cpu::OPCODE::LD__$U16_SP, "LD (u16),SP"},
	{cpu::OPCODE::ADD__HL_BC, "ADD HL,BC"},
	{cpu::OPCODE::LD__A_$BC, "LD A,(BC)"},
	{cpu::OPCODE::DEC__BC, "DEC BC"},
	{cpu::OPCODE::INC__C, "INC C"},
	{cpu::OPCODE::DEC__C, "DEC C"},
	{cpu::OPCODE::LD__C_U8, "LD C,u8"},
	{cpu::OPCODE::RRCA, "RRCA"},
	{cpu::OPCODE::STOP, "STOP"},
	{cpu::OPCODE::LD__DE_U16, "LD DE,u16"},
	{cpu::OPCODE::LD__$DE_A, "LD (DE),A"},
	{cpu::OPCODE::INC__DE, "INC DE"},
	{cpu::OPCODE::INC__D, "INC D"},
	{cpu::OPCODE::DEC__D, "DEC D"},
	{cpu::OPCODE::LD__D_U8, "LD D,u8"},
	{cpu::OPCODE::RLA, "RLA"},
	{cpu::OPCODE::JR__S8, "JR s8"},
	{cpu::OPCODE::ADD__HL_DE, "ADD HL,DE"},
	{cpu::OPCODE::LD__A_$DE, "LD A,(DE)"},
	{cpu::OPCODE::DEC__DE, "DEC DE"},
	{cpu::OPCODE::INC__E, "INC E"},
	{cpu::OPCODE::DEC__E, "DEC E"},
	{cpu::OPCODE::LD__E_U8, "LD E,u8"},
	{cpu::OPCODE::RRA, "RRA"},
	{cpu::OPCODE::JR__NZ_S8, "JR NZ,s8"},
	{cpu::OPCODE::LD__HL_U16, "LD HL,u16"},
	{cpu::OPCODE::LDI__$HL_A, "LD (HL+),A"},
	{cpu::OPCODE::INC__HL, "INC HL"},
	{cpu::OPCODE::INC__H, "INC H"},
	{cpu::OPCODE::DEC__H, "DEC H"},
	{cpu::OPCODE::LD__H_U8, "LD H,u8"},
	{cpu::OPCODE::DAA, "DAA"},
	{cpu::OPCODE::JR__Z_S8, "JR Z,s8"},
	{cpu::OPCODE::ADD__HL_HL, "ADD HL,HL"},
	{cpu::OPCODE::LDI__A_$HL, "LD A,(HL+)"},
	{cpu::OPCODE::DEC__HL, "DEC HL"},
	{cpu::OPCODE::INC__L, "INC L"},
	{cpu::OPCODE::DEC__L, "DEC L"},
	{cpu::OPCODE::LD__L_U8, "LD L,u8"},
	{cpu::OPCODE::CPL, "CPL"},
	{cpu::OPCODE::JR__NC_S8, "JR NC,s8"},
	{cpu::OPCODE::LD__SP_U16, "LD SP,u16"},
	{cpu::OPCODE::LDD__$HL_A, "LD (HL-),A"},
	{cpu::OPCODE::INC__SP, "INC SP"},
	{cpu::OPCODE::INC__$HL, "INC (HL)"},
	{cpu::OPCODE::DEC__$HL, "DEC (HL)"},
	{cpu::OPCODE::LD__$HL_U8, "LD (HL),u8"},
	{cpu::OPCODE::SCF, "SCF"},
	{cpu::OPCODE::JR__C_S8, "JR C,s8"},
	{cpu::OPCODE::ADD__HL_SP, "ADD HL,SP"},
	{cpu::OPCODE::LDD__A_$HL, "LD A,(HL-)"},
	{cpu::OPCODE::DEC__SP, "DEC SP"},
	{cpu::OPCODE::INC__A, "INC A"},
	{cpu::OPCODE::DEC__A, "DEC A"},
	{cpu::OPCODE::LD__A_U8, "LD A,u8"},
	{cpu::OPCODE::CCF, "CCF"},
	{cpu::OPCODE::LD__B_B, "LD B,B"},
	{cpu::OPCODE::LD__B_C, "LD B,C"},
	{cpu::OPCODE::LD__B_D, "LD B,D"},
	{cpu::OPCODE::LD__B_E, "LD B,E"},
	{cpu::OPCODE::LD__B_H, "LD B,H"},
	{cpu::OPCODE::LD__B_L, "LD B,L"},
	{cpu::OPCODE::LD__B_$HL, "LD B,(HL)"},
	{cpu::OPCODE::LD__B_A, "LD B,A"},
	{cpu::OPCODE::LD__C_B, "LD C,B"},
	{cpu::OPCODE::LD__C_C, "LD C,C"},
	{cpu::OPCODE::LD__C_D, "LD C,D"},
	{cpu::OPCODE::LD__C_E, "LD C,E"},
	{cpu::OPCODE::LD__C_H, "LD C,H"},
	{cpu::OPCODE::LD__C_L, "LD C,L"},
	{cpu::OPCODE::LD__C_$HL, "LD C,(HL)"},
	{cpu::OPCODE::LD__C_A, "LD C,A"},
	{cpu::OPCODE::LD__D_B, "LD D,B"},
	{cpu::OPCODE::LD__D_C, "LD D,C"},
	{cpu::OPCODE::LD__D_D, "LD D,D"},
	{cpu::OPCODE::LD__D_E, "LD D,E"},
	{cpu::OPCODE::LD__D_H, "LD D,H"},
	{cpu::OPCODE::LD__D_L, "LD D,L"},
	{cpu::OPCODE::LD__D_$HL, "LD D,(HL)"},
	{cpu::OPCODE::LD__D_A, "LD D,A"},
	{cpu::OPCODE::LD__E_B, "LD E,B"},
	{cpu::OPCODE::LD__E_C, "LD E,C"},
	{cpu::OPCODE::LD__E_D, "LD E,D"},
	{cpu::OPCODE::LD__E_E, "LD E,E"},
	{cpu::OPCODE::LD__E_H, "LD E,H"},
	{cpu::OPCODE::LD__E_L, "LD E,L"},
	{cpu::OPCODE::LD__E_$HL, "LD E,(HL)"},
	{cpu::OPCODE::LD__E_A, "LD E,A"},
	{cpu::OPCODE::LD__H_B, "LD H,B"},
	{cpu::OPCODE::LD__H_C, "LD H,C"},
	{cpu::OPCODE::LD__H_D, "LD H,D"},
	{cpu::OPCODE::LD__H_E, "LD H,E"},
	{cpu::OPCODE::LD__H_H, "LD H,H"},
	{cpu::OPCODE::LD__H_L, "LD H,L"},
	{cpu::OPCODE::LD__H_$HL, "LD H,(HL)"},
	{cpu::OPCODE::LD__H_A, "LD H,A"},
	{cpu::OPCODE::LD__L_B, "LD L,B"},
	{cpu::OPCODE::LD__L_C, "LD L,C"},
	{cpu::OPCODE::LD__L_D, "LD L,D"},
	{cpu::OPCODE::LD__L_E, "LD L,E"},
	{cpu::OPCODE::LD__L_H, "LD L,H"},
	{cpu::OPCODE::LD__L_L, "LD L,L"},
	{cpu::OPCODE::LD__L_$HL, "LD L,(HL)"},
	{cpu::OPCODE::LD__L_A, "LD L,A"},
	{cpu::OPCODE::LD__$HL_B, "LD (HL),B"},
	{cpu::OPCODE::LD__$HL_C, "LD (HL),C"},
	{cpu::OPCODE::LD__$HL_D, "LD (HL),D"},
	{cpu::OPCODE::LD__$HL_E, "LD (HL),E"},
	{cpu::OPCODE::LD__$HL_H, "LD (HL),H"},
	{cpu::OPCODE::LD__$HL_L, "LD (HL),L"},
	{cpu::OPCODE::HALT, "HALT"},
	{cpu::OPCODE::LD__$HL_A, "LD (HL),A"},
	{cpu::OPCODE::LD__A_B, "LD A,B"},
	{cpu::OPCODE::LD__A_C, "LD A,C"},
	{cpu::OPCODE::LD__A_D, "LD A,D"},
	{cpu::OPCODE::LD__A_E, "LD A,E"},
	{cpu::OPCODE::LD__A_H, "LD A,H"},
	{cpu::OPCODE::LD__A_L, "LD A,L"},
	{cpu::OPCODE::LD__A_$HL, "LD A,(HL)"},
	{cpu::OPCODE::LD__A_A, "LD A,A"},
	{cpu::OPCODE::ADD__A_B, "ADD A,B"},
	{cpu::OPCODE::ADD__A_C, "ADD A,C"},
	{cpu::OPCODE::ADD__A_D, "ADD A,D"},
	{cpu::OPCODE::ADD__A_E, "ADD A,E"},
	{cpu::OPCODE::ADD__A_H, "ADD A,H"},
	{cpu::OPCODE::ADD__A_L, "ADD A,L"},
	{cpu::OPCODE::ADD__A_$HL, "ADD A,(HL)"},
	{cpu::OPCODE::ADD__A_A, "ADD A,A"},
	{cpu::OPCODE::ADC__A_B, "ADC A,B"},
	{cpu::OPCODE::ADC__A_C, "ADC A,C"},
	{cpu::OPCODE::ADC__A_D, "ADC A,D"},
	{cpu::OPCODE::ADC__A_E, "ADC A,E"},
	{cpu::OPCODE::ADC__A_H, "ADC A,H"},
	{cpu::OPCODE::ADC__A_L, "ADC A,L"},
	{cpu::OPCODE::ADC__A_$HL, "ADC A,(HL)"},
	{cpu::OPCODE::ADC__A_A, "ADC A,A"},
	{cpu::OPCODE::SUB__A_B, "SUB A,B"},
	{cpu::OPCODE::SUB__A_C, "SUB A,C"},
	{cpu::OPCODE::SUB__A_D, "SUB A,D"},
	{cpu::OPCODE::SUB__A_E, "SUB A,E"},
	{cpu::OPCODE::SUB__A_H, "SUB A,H"},
	{cpu::OPCODE::SUB__A_L, "SUB A,L"},
	{cpu::OPCODE::SUB__A_$HL, "SUB A,(HL)"},
	{cpu::OPCODE::SUB__A_A, "SUB A,A"},
	{cpu::OPCODE::SBC__A_B, "SBC A,B"},
	{cpu::OPCODE::SBC__A_C, "SBC A,C"},
	{cpu::OPCODE::SBC__A_D, "SBC A,D"},
	{cpu::OPCODE::SBC__A_E, "SBC A,E"},
	{cpu::OPCODE::SBC__A_H, "SBC A,H"},
	{cpu::OPCODE::SBC__A_L, "SBC A,L"},
	{cpu::OPCODE::SBC__A_$HL, "SBC A,(HL)"},
	{cpu::OPCODE::SBC__A_A, "SBC A,A"},
	{cpu::OPCODE::AND__A_B, "AND A,B"},
	{cpu::OPCODE::AND__A_C, "AND A,C"},
	{cpu::OPCODE::AND__A_D, "AND A,D"},
	{cpu::OPCODE::AND__A_E, "AND A,E"},
	{cpu::OPCODE::AND__A_H, "AND A,H"},
	{cpu::OPCODE::AND__A_L, "AND A,L"},
	{cpu::OPCODE::AND__A_$HL, "AND A,(HL)"},
	{cpu::OPCODE::AND__A_A, "AND A,A"},
	{cpu::OPCODE::XOR__A_B, "XOR A,B"},
	{cpu::OPCODE::XOR__A_C, "XOR A,C"},
	{cpu::OPCODE::XOR__A_D, "XOR A,D"},
	{cpu::OPCODE::XOR__A_E, "XOR A,E"},
	{cpu::OPCODE::XOR__A_H, "XOR A,H"},
	{cpu::OPCODE::XOR__A_L, "XOR A,L"},
	{cpu::OPCODE::XOR__A_$HL, "XOR A,(HL)"},
	{cpu::OPCODE::XOR__A_A, "XOR A,A"},
	{cpu::OPCODE::OR__A_B, "OR A,B"},
	{cpu::OPCODE::OR__A_C, "OR A,C"},
	{cpu::OPCODE::OR__A_D, "OR A,D"},
	{cpu::OPCODE::OR__A_E, "OR A,E"},
	{cpu::OPCODE::OR__A_H, "OR A,H"},
	{cpu::OPCODE::OR__A_L, "OR A,L"},
	{cpu::OPCODE::OR__A_$HL, "OR A,(HL)"},
	{cpu::OPCODE::OR__A_A, "OR A,A"},
	{cpu::OPCODE::CP__A_B, "CP A,B"},
	{cpu::OPCODE::CP__A_C, "CP A,C"},
	{cpu::OPCODE::CP__A_D, "CP A,D"},
	{cpu::OPCODE::CP__A_E, "CP A,E"},
	{cpu::OPCODE::CP__A_H, "CP A,H"},
	{cpu::OPCODE::CP__A_L, "CP A,L"},
	{cpu::OPCODE::CP__A_$HL, "CP A,(HL)"},
	{cpu::OPCODE::CP__A_A, "CP A,A"},
	{cpu::OPCODE::RET__NZ, "RET NZ"},
	{cpu::OPCODE::POP__BC, "POP BC"},
	{cpu::OPCODE::JP__NZ_U16, "JP NZ,u16"},
	{cpu::OPCODE::JP__U16, "JP u16"},
	{cpu::OPCODE::CALL__NZ_U16, "CALL NZ,u16"},
	{cpu::OPCODE::PUSH__BC, "PUSH BC"},
	{cpu::OPCODE::ADD__A_U8, "ADD A,u8"},
	{cpu::OPCODE::RST__00H, "RST 00H"},
	{cpu::OPCODE::RET__Z, "RET Z"},
	{cpu::OPCODE::RET, "RET"},
	{cpu::OPCODE::JP__Z_U16, "JP Z,u16"},
	{cpu::OPCODE::PREFIX__CB, "PREFIX CB"},
	{cpu::OPCODE::CALL__Z_U16, "CALL Z,u16"},
	{cpu::OPCODE::CALL__U16, "CALL u16"},
	{cpu::OPCODE::ADC__A_U8, "ADC A,u8"},
	{cpu::OPCODE::RST__08H, "RST 08H"},
	{cpu::OPCODE::RET__NC, "RET NC"},
	{cpu::OPCODE::POP__DE, "POP DE"},
	{cpu::OPCODE::JP__NC_U16, "JP NC,u16"},
	{cpu::OPCODE::CALL__NC_U16, "CALL NC,u16"},
	{cpu::OPCODE::PUSH__DE, "PUSH DE"},
	{cpu::OPCODE::SUB__A_U8, "SUB A,u8"},
	{cpu::OPCODE::RST__10H, "RST 10H"},
	{cpu::OPCODE::RET__C, "RET C"},
	{cpu::OPCODE::RETI, "RETI"},
	{cpu::OPCODE::JP__C_U16, "JP C,u16"},
	{cpu::OPCODE::CALL__C_U16, "CALL C,u16"},
	{cpu::OPCODE::SBC__A_U8, "SBC A,u8"},
	{cpu::OPCODE::RST__18H, "RST 18H"},
	{cpu::OPCODE::LDH__$U8_A, "LDH (u8),A"},
	{cpu::OPCODE::POP__HL, "POP HL"},
	{cpu::OPCODE::LD__$C_A, "LD (C),A"},
	{cpu::OPCODE::PUSH__HL, "PUSH HL"},
	{cpu::OPCODE::AND__A_U8, "AND A,u8"},
	{cpu::OPCODE::RST__20H, "RST 20H"},
	{cpu::OPCODE::ADD__SP_S8, "ADD SP,s8"},
	{cpu::OPCODE::JP__$HL, "JP (HL)"},
	{cpu::OPCODE::LD__$U16_A, "LD (u16),A"},
	{cpu::OPCODE::XOR__A_U8, "XOR A,u8"},
	{cpu::OPCODE::RST__28H, "RST 28H"},
	{cpu::OPCODE::LDH__A_$U8, "LDH A,(u8)"},
	{cpu::OPCODE::POP__AF, "POP AF"},
	{cpu::OPCODE::LD__A_$C, "LD A,(C)"},
	{cpu::OPCODE::DI, "DI"},
	{cpu::OPCODE::PUSH__AF, "PUSH AF"},
	{cpu::OPCODE::OR__A_U8, "OR A,u8"},
	{cpu::OPCODE::RST__30H, "RST 30H"},
	{cpu::OPCODE::LDHL__SP_S8, "LD HL,SP+s8"},
	{cpu::OPCODE::LD__SP_HL, "LD SP,HL"},
	{cpu::OPCODE::LD__A_$U16, "LD A,(u16)"},
	{cpu::OPCODE::EI, "EI"},
	{cpu::OPCODE::CP__A_U8, "CP A,u8"},
	{cpu::OPCODE::RST__38H, "RST 38H"},
};

const std::map<cpu::PREFIXED_OPCODE, std::string> cpu::PREFIXED_OPCODE_MNEMONIC = {
	{cpu::PREFIXED_OPCODE::RLC__B, "RLC B"},
	{cpu::PREFIXED_OPCODE::RLC__C, "RLC C"},
	{cpu::PREFIXED_OPCODE::RLC__D, "RLC D"},
	{cpu::PREFIXED_OPCODE::RLC__E, "RLC E"},
	{cpu::PREFIXED_OPCODE::RLC__H, "RLC H"},
	{cpu::PREFIXED_OPCODE::RLC__L, "RLC L"},
	{cpu::PREFIXED_OPCODE::RLC__$HL, "RLC (HL)"},
	{cpu::PREFIXED_OPCODE::RLC__A, "RLC A"},
	{cpu::PREFIXED_OPCODE::RRC__B, "RRC B"},
	{cpu::PREFIXED_OPCODE::RRC__C, "RRC C"},
	{cpu::PREFIXED_OPCODE::RRC__D, "RRC D"},
	{cpu::PREFIXED_OPCODE::RRC__E, "RRC E"},
	{cpu::PREFIXED_OPCODE::RRC__H, "RRC H"},
	{cpu::PREFIXED_OPCODE::RRC__L, "RRC L"},
	{cpu::PREFIXED_OPCODE::RRC__$HL, "RRC (HL)"},
	{cpu::PREFIXED_OPCODE::RRC__A, "RRC A"},
	{cpu::PREFIXED_OPCODE::RL__B, "RL B"},
	{cpu::PREFIXED_OPCODE::RL__C, "RL C"},
	{cpu::PREFIXED_OPCODE::RL__D, "RL D"},
	{cpu::PREFIXED_OPCODE::RL__E, "RL E"},
	{cpu::PREFIXED_OPCODE::RL__H, "RL H"},
	{cpu::PREFIXED_OPCODE::RL__L, "RL L"},
	{cpu::PREFIXED_OPCODE::RL__$HL, "RL (HL)"},
	{cpu::PREFIXED_OPCODE::RL__A, "RL A"},
	{cpu::PREFIXED_OPCODE::RR__B, "RR B"},
	{cpu::PREFIXED_OPCODE::RR__C, "RR C"},
	{cpu::PREFIXED_OPCODE::RR__D, "RR D"},
	{cpu::PREFIXED_OPCODE::RR__E, "RR E"},
	{cpu::PREFIXED_OPCODE::RR__H, "RR H"},
	{cpu::PREFIXED_OPCODE::RR__L, "RR L"},
	{cpu::PREFIXED_OPCODE::RR__$HL, "RR (HL)"},
	{cpu::PREFIXED_OPCODE::RR__A, "RR A"},
	{cpu::PREFIXED_OPCODE::SLA__B, "SLA B"},
	{cpu::PREFIXED_OPCODE::SLA__C, "SLA C"},
	{cpu::PREFIXED_OPCODE::SLA__D, "SLA D"},
	{cpu::PREFIXED_OPCODE::SLA__E, "SLA E"},
	{cpu::PREFIXED_OPCODE::SLA__H, "SLA H"},
	{cpu::PREFIXED_OPCODE::SLA__L, "SLA L"},
	{cpu::PREFIXED_OPCODE::SLA__$HL, "SLA (HL)"},
	{cpu::PREFIXED_OPCODE::SLA__A, "SLA A"},
	{cpu::PREFIXED_OPCODE::SRA__B, "SRA B"},
	{cpu::PREFIXED_OPCODE::SRA__C, "SRA C"},
	{cpu::PREFIXED_OPCODE::SRA__D, "SRA D"},
	{cpu::PREFIXED_OPCODE::SRA__E, "SRA E"},
	{cpu::PREFIXED_OPCODE::SRA__H, "SRA H"},
	{cpu::PREFIXED_OPCODE::SRA__L, "SRA L"},
	{cpu::PREFIXED_OPCODE::SRA__$HL, "SRA (HL)"},
	{cpu::PREFIXED_OPCODE::SRA__A, "SRA A"},
	{cpu::PREFIXED_OPCODE::SWAP__B, "SWAP B"},
	{cpu::PREFIXED_OPCODE::SWAP__C, "SWAP C"},
	{cpu::PREFIXED_OPCODE::SWAP__D, "SWAP D"},
	{cpu::PREFIXED_OPCODE::SWAP__E, "SWAP E"},
	{cpu::PREFIXED_OPCODE::SWAP__H, "SWAP H"},
	{cpu::PREFIXED_OPCODE::SWAP__L, "SWAP L"},
	{cpu::PREFIXED_OPCODE::SWAP__$HL, "SWAP (HL)"},
	{cpu::PREFIXED_OPCODE::SWAP__A, "SWAP A"},
	{cpu::PREFIXED_OPCODE::SRL__B, "SRL B"},
	{cpu::PREFIXED_OPCODE::SRL__C, "SRL C"},
	{cpu::PREFIXED_OPCODE::SRL__D, "SRL D"},
	{cpu::PREFIXED_OPCODE::SRL__E, "SRL E"},
	{cpu::PREFIXED_OPCODE::SRL__H, "SRL H"},
	{cpu::PREFIXED_OPCODE::SRL__L, "SRL L"},
	{cpu::PREFIXED_OPCODE::SRL__$HL, "SRL (HL)"},
	{cpu::PREFIXED_OPCODE::SRL__A, "SRL A"},
	{cpu::PREFIXED_OPCODE::BIT__0_B, "BIT 0,B"},
	{cpu::PREFIXED_OPCODE::BIT__0_C, "BIT 0,C"},
	{cpu::PREFIXED_OPCODE::BIT__0_D, "BIT 0,D"},
	{cpu::PREFIXED_OPCODE::BIT__0_E, "BIT 0,E"},
	{cpu::PREFIXED_OPCODE::BIT__0_H, "BIT 0,H"},
	{cpu::PREFIXED_OPCODE::BIT__0_L, "BIT 0,L"},
	{cpu::PREFIXED_OPCODE::BIT__0_$HL, "BIT 0,(HL)"},
	{cpu::PREFIXED_OPCODE::BIT__0_A, "BIT 0,A"},
	{cpu::PREFIXED_OPCODE::BIT__1_B, "BIT 1,B"},
	{cpu::PREFIXED_OPCODE::BIT__1_C, "BIT 1,C"},
	{cpu::PREFIXED_OPCODE::BIT__1_D, "BIT 1,D"},
	{cpu::PREFIXED_OPCODE::BIT__1_E, "BIT 1,E"},
	{cpu::PREFIXED_OPCODE::BIT__1_H, "BIT 1,H"},
	{cpu::PREFIXED_OPCODE::BIT__1_L, "BIT 1,L"},
	{cpu::PREFIXED_OPCODE::BIT__1_$HL, "BIT 1,(HL)"},
	{cpu::PREFIXED_OPCODE::BIT__1_A, "BIT 1,A"},
	{cpu::PREFIXED_OPCODE::BIT__2_B, "BIT 2,B"},
	{cpu::PREFIXED_OPCODE::BIT__2_C, "BIT 2,C"},
	{cpu::PREFIXED_OPCODE::BIT__2_D, "BIT 2,D"},
	{cpu::PREFIXED_OPCODE::BIT__2_E, "BIT 2,E"},
	{cpu::PREFIXED_OPCODE::BIT__2_H, "BIT 2,H"},
	{cpu::PREFIXED_OPCODE::BIT__2_L, "BIT 2,L"},
	{cpu::PREFIXED_OPCODE::BIT__2_$HL, "BIT 2,(HL)"},
	{cpu::PREFIXED_OPCODE::BIT__2_A, "BIT 2,A"},
	{cpu::PREFIXED_OPCODE::BIT__3_B, "BIT 3,B"},
	{cpu::PREFIXED_OPCODE::BIT__3_C, "BIT 3,C"},
	{cpu::PREFIXED_OPCODE::BIT__3_D, "BIT 3,D"},
	{cpu::PREFIXED_OPCODE::BIT__3_E, "BIT 3,E"},
	{cpu::PREFIXED_OPCODE::BIT__3_H, "BIT 3,H"},
	{cpu::PREFIXED_OPCODE::BIT__3_L, "BIT 3,L"},
	{cpu::PREFIXED_OPCODE::BIT__3_$HL, "BIT 3,(HL)"},
	{cpu::PREFIXED_OPCODE::BIT__3_A, "BIT 3,A"},
	{cpu::PREFIXED_OPCODE::BIT__4_B, "BIT 4,B"},
	{cpu::PREFIXED_OPCODE::BIT__4_C, "BIT 4,C"},
	{cpu::PREFIXED_OPCODE::BIT__4_D, "BIT 4,D"},
	{cpu::PREFIXED_OPCODE::BIT__4_E, "BIT 4,E"},
	{cpu::PREFIXED_OPCODE::BIT__4_H, "BIT 4,H"},
	{cpu::PREFIXED_OPCODE::BIT__4_L, "BIT 4,L"},
	{cpu::PREFIXED_OPCODE::BIT__4_$HL, "BIT 4,(HL)"},
	{cpu::PREFIXED_OPCODE::BIT__4_A, "BIT 4,A"},
	{cpu::PREFIXED_OPCODE::BIT__5_B, "BIT 5,B"},
	{cpu::PREFIXED_OPCODE::BIT__5_C, "BIT 5,C"},
	{cpu::PREFIXED_OPCODE::BIT__5_D, "BIT 5,D"},
	{cpu::PREFIXED_OPCODE::BIT__5_E, "BIT 5,E"},
	{cpu::PREFIXED_OPCODE::BIT__5_H, "BIT 5,H"},
	{cpu::PREFIXED_OPCODE::BIT__5_L, "BIT 5,L"},
	{cpu::PREFIXED_OPCODE::BIT__5_$HL, "BIT 5,(HL)"},
	{cpu::PREFIXED_OPCODE::BIT__5_A, "BIT 5,A"},
	{cpu::PREFIXED_OPCODE::BIT__6_B, "BIT 6,B"},
	{cpu::PREFIXED_OPCODE::BIT__6_C, "BIT 6,C"},
	{cpu::PREFIXED_OPCODE::BIT__6_D, "BIT 6,D"},
	{cpu::PREFIXED_OPCODE::BIT__6_E, "BIT 6,E"},
	{cpu::PREFIXED_OPCODE::BIT__6_H, "BIT 6,H"},
	{cpu::PREFIXED_OPCODE::BIT__6_L, "BIT 6,L"},
	{cpu::PREFIXED_OPCODE::BIT__6_$HL, "BIT 6,(HL)"},
	{cpu::PREFIXED_OPCODE::BIT__6_A, "BIT 6,A"},
	{cpu::PREFIXED_OPCODE::BIT__7_B, "BIT 7,B"},
	{cpu::PREFIXED_OPCODE::BIT__7_C, "BIT 7,C"},
	{cpu::PREFIXED_OPCODE::BIT__7_D, "BIT 7,D"},
	{cpu::PREFIXED_OPCODE::BIT__7_E, "BIT 7,E"},
	{cpu::PREFIXED_OPCODE::BIT__7_H, "BIT 7,H"},
	{cpu::PREFIXED_OPCODE::BIT__7_L, "BIT 7,L"},
	{cpu::PREFIXED_OPCODE::BIT__7_$HL, "BIT 7,(HL)"},
	{cpu::PREFIXED_OPCODE::BIT__7_A, "BIT 7,A"},
	{cpu::PREFIXED_OPCODE::RES__0_B, "RES 0,B"},
	{cpu::PREFIXED_OPCODE::RES__0_C, "RES 0,C"},
	{cpu::PREFIXED_OPCODE::RES__0_D, "RES 0,D"},
	{cpu::PREFIXED_OPCODE::RES__0_E, "RES 0,E"},
	{cpu::PREFIXED_OPCODE::RES__0_H, "RES 0,H"},
	{cpu::PREFIXED_OPCODE::RES__0_L, "RES 0,L"},
	{cpu::PREFIXED_OPCODE::RES__0_$HL, "RES 0,(HL)"},
	{cpu::PREFIXED_OPCODE::RES__0_A, "RES 0,A"},
	{cpu::PREFIXED_OPCODE::RES__1_B, "RES 1,B"},
	{cpu::PREFIXED_OPCODE::RES__1_C, "RES 1,C"},
	{cpu::PREFIXED_OPCODE::RES__1_D, "RES 1,D"},
	{cpu::PREFIXED_OPCODE::RES__1_E, "RES 1,E"},
	{cpu::PREFIXED_OPCODE::RES__1_H, "RES 1,H"},
	{cpu::PREFIXED_OPCODE::RES__1_L, "RES 1,L"},
	{cpu::PREFIXED_OPCODE::RES__1_$HL, "RES 1,(HL)"},
	{cpu::PREFIXED_OPCODE::RES__1_A, "RES 1,A"},
	{cpu::PREFIXED_OPCODE::RES__2_B, "RES 2,B"},
	{cpu::PREFIXED_OPCODE::RES__2_C, "RES 2,C"},
	{cpu::PREFIXED_OPCODE::RES__2_D, "RES 2,D"},
	{cpu::PREFIXED_OPCODE::RES__2_E, "RES 2,E"},
	{cpu::PREFIXED_OPCODE::RES__2_H, "RES 2,H"},
	{cpu::PREFIXED_OPCODE::RES__2_L, "RES 2,L"},
	{cpu::PREFIXED_OPCODE::RES__2_$HL, "RES 2,(HL)"},
	{cpu::PREFIXED_OPCODE::RES__2_A, "RES 2,A"},
	{cpu::PREFIXED_OPCODE::RES__3_B, "RES 3,B"},
	{cpu::PREFIXED_OPCODE::RES__3_C, "RES 3,C"},
	{cpu::PREFIXED_OPCODE::RES__3_D, "RES 3,D"},
	{cpu::PREFIXED_OPCODE::RES__3_E, "RES 3,E"},
	{cpu::PREFIXED_OPCODE::RES__3_H, "RES 3,H"},
	{cpu::PREFIXED_OPCODE::RES__3_L, "RES 3,L"},
	{cpu::PREFIXED_OPCODE::RES__3_$HL, "RES 3,(HL)"},
	{cpu::PREFIXED_OPCODE::RES__3_A, "RES 3,A"},
	{cpu::PREFIXED_OPCODE::RES__4_B, "RES 4,B"},
	{cpu::PREFIXED_OPCODE::RES__4_C, "RES 4,C"},
	{cpu::PREFIXED_OPCODE::RES__4_D, "RES 4,D"},
	{cpu::PREFIXED_OPCODE::RES__4_E, "RES 4,E"},
	{cpu::PREFIXED_OPCODE::RES__4_H, "RES 4,H"},
	{cpu::PREFIXED_OPCODE::RES__4_L, "RES 4,L"},
	{cpu::PREFIXED_OPCODE::RES__4_$HL, "RES 4,(HL)"},
	{cpu::PREFIXED_OPCODE::RES__4_A, "RES 4,A"},
	{cpu::PREFIXED_OPCODE::RES__5_B, "RES 5,B"},
	{cpu::PREFIXED_OPCODE::RES__5_C, "RES 5,C"},
	{cpu::PREFIXED_OPCODE::RES__5_D, "RES 5,D"},
	{cpu::PREFIXED_OPCODE::RES__5_E, "RES 5,E"},
	{cpu::PREFIXED_OPCODE::RES__5_H, "RES 5,H"},
	{cpu::PREFIXED_OPCODE::RES__5_L, "RES 5,L"},
	{cpu::PREFIXED_OPCODE::RES__5_$HL, "RES 5,(HL)"},
	{cpu::PREFIXED_OPCODE::RES__5_A, "RES 5,A"},
	{cpu::PREFIXED_OPCODE::RES__6_B, "RES 6,B"},
	{cpu::PREFIXED_OPCODE::RES__6_C, "RES 6,C"},
	{cpu::PREFIXED_OPCODE::RES__6_D, "RES 6,D"},
	{cpu::PREFIXED_OPCODE::RES__6_E, "RES 6,E"},
	{cpu::PREFIXED_OPCODE::RES__6_H, "RES 6,H"},
	{cpu::PREFIXED_OPCODE::RES__6_L, "RES 6,L"},
	{cpu::PREFIXED_OPCODE::RES__6_$HL, "RES 6,(HL)"},
	{cpu::PREFIXED_OPCODE::RES__6_A, "RES 6,A"},
	{cpu::PREFIXED_OPCODE::RES__7_B, "RES 7,B"},
	{cpu::PREFIXED_OPCODE::RES__7_C, "RES 7,C"},
	{cpu::PREFIXED_OPCODE::RES__7_D, "RES 7,D"},
	{cpu::PREFIXED_OPCODE::RES__7_E, "RES 7,E"},
	{cpu::PREFIXED_OPCODE::RES__7_H, "RES 7,H"},
	{cpu::PREFIXED_OPCODE::RES__7_L, "RES 7,L"},
	{cpu::PREFIXED_OPCODE::RES__7_$HL, "RES 7,(HL)"},
	{cpu::PREFIXED_OPCODE::RES__7_A, "RES 7,A"},
	{cpu::PREFIXED_OPCODE::SET__0_B, "SET 0,B"},
	{cpu::PREFIXED_OPCODE::SET__0_C, "SET 0,C"},
	{cpu::PREFIXED_OPCODE::SET__0_D, "SET 0,D"},
	{cpu::PREFIXED_OPCODE::SET__0_E, "SET 0,E"},
	{cpu::PREFIXED_OPCODE::SET__0_H, "SET 0,H"},
	{cpu::PREFIXED_OPCODE::SET__0_L, "SET 0,L"},
	{cpu::PREFIXED_OPCODE::SET__0_$HL, "SET 0,(HL)"},
	{cpu::PREFIXED_OPCODE::SET__0_A, "SET 0,A"},
	{cpu::PREFIXED_OPCODE::SET__1_B, "SET 1,B"},
	{cpu::PREFIXED_OPCODE::SET__1_C, "SET 1,C"},
	{cpu::PREFIXED_OPCODE::SET__1_D, "SET 1,D"},
	{cpu::PREFIXED_OPCODE::SET__1_E, "SET 1,E"},
	{cpu::PREFIXED_OPCODE::SET__1_H, "SET 1,H"},
	{cpu::PREFIXED_OPCODE::SET__1_L, "SET 1,L"},
	{cpu::PREFIXED_OPCODE::SET__1_$HL, "SET 1,(HL)"},
	{cpu::PREFIXED_OPCODE::SET__1_A, "SET 1,A"},
	{cpu::PREFIXED_OPCODE::SET__2_B, "SET 2,B"},
	{cpu::PREFIXED_OPCODE::SET__2_C, "SET 2,C"},
	{cpu::PREFIXED_OPCODE::SET__2_D, "SET 2,D"},
	{cpu::PREFIXED_OPCODE::SET__2_E, "SET 2,E"},
	{cpu::PREFIXED_OPCODE::SET__2_H, "SET 2,H"},
	{cpu::PREFIXED_OPCODE::SET__2_L, "SET 2,L"},
	{cpu::PREFIXED_OPCODE::SET__2_$HL, "SET 2,(HL)"},
	{cpu::PREFIXED_OPCODE::SET__2_A, "SET 2,A"},
	{cpu::PREFIXED_OPCODE::SET__3_B, "SET 3,B"},
	{cpu::PREFIXED_OPCODE::SET__3_C, "SET 3,C"},
	{cpu::PREFIXED_OPCODE::SET__3_D, "SET 3,D"},
	{cpu::PREFIXED_OPCODE::SET__3_E, "SET 3,E"},
	{cpu::PREFIXED_OPCODE::SET__3_H, "SET 3,H"},
	{cpu::PREFIXED_OPCODE::SET__3_L, "SET 3,L"},
	{cpu::PREFIXED_OPCODE::SET__3_$HL, "SET 3,(HL)"},
	{cpu::PREFIXED_OPCODE::SET__3_A, "SET 3,A"},
	{cpu::PREFIXED_OPCODE::SET__4_B, "SET 4,B"},
	{cpu::PREFIXED_OPCODE::SET__4_C, "SET 4,C"},
	{cpu::PREFIXED_OPCODE::SET__4_D, "SET 4,D"},
	{cpu::PREFIXED_OPCODE::SET__4_E, "SET 4,E"},
	{cpu::PREFIXED_OPCODE::SET__4_H, "SET 4,H"},
	{cpu::PREFIXED_OPCODE::SET__4_L, "SET 4,L"},
	{cpu::PREFIXED_OPCODE::SET__4_$HL, "SET 4,(HL)"},
	{cpu::PREFIXED_OPCODE::SET__4_A, "SET 4,A"},
	{cpu::PREFIXED_OPCODE::SET__5_B, "SET 5,B"},
	{cpu::PREFIXED_OPCODE::SET__5_C, "SET 5,C"},
	{cpu::PREFIXED_OPCODE::SET__5_D, "SET 5,D"},
	{cpu::PREFIXED_OPCODE::SET__5_E, "SET 5,E"},
	{cpu::PREFIXED_OPCODE::SET__5_H, "SET 5,H"},
	{cpu::PREFIXED_OPCODE::SET__5_L, "SET 5,L"},
	{cpu::PREFIXED_OPCODE::SET__5_$HL, "SET 5,(HL)"},
	{cpu::PREFIXED_OPCODE::SET__5_A, "SET 5,A"},
	{cpu::PREFIXED_OPCODE::SET__6_B, "SET 6,B"},
	{cpu::PREFIXED_OPCODE::SET__6_C, "SET 6,C"},
	{cpu::PREFIXED_OPCODE::SET__6_D, "SET 6,D"},
	{cpu::PREFIXED_OPCODE::SET__6_E, "SET 6,E"},
	{cpu::PREFIXED_OPCODE::SET__6_H, "SET 6,H"},
	{cpu::PREFIXED_OPCODE::SET__6_L, "SET 6,L"},
	{cpu::PREFIXED_OPCODE::SET__6_$HL, "SET 6,(HL)"},
	{cpu::PREFIXED_OPCODE::SET__6_A, "SET 6,A"},
	{cpu::PREFIXED_OPCODE::SET__7_B, "SET 7,B"},
	{cpu::PREFIXED_OPCODE::SET__7_C, "SET 7,C"},
	{cpu::PREFIXED_OPCODE::SET__7_D, "SET 7,D"},
	{cpu::PREFIXED_OPCODE::SET__7_E, "SET 7,E"},
	{cpu::PREFIXED_OPCODE::SET__7_H, "SET 7,H"},
	{cpu::PREFIXED_OPCODE::SET__7_L, "SET 7,L"},
	{cpu::PREFIXED_OPCODE::SET__7_$HL, "SET 7,(HL)"},
	{cpu::PREFIXED_OPCODE::SET__7_A, "SET 7,A"}, 
};

const std::map<cpu::TEMPLATED_OPCODE, std::uint8_t> cpu::TEMPLATED_OPCODE_CYCLES = {
	{cpu::TEMPLATED_OPCODE::EMPTY, 0},
	{cpu::TEMPLATED_OPCODE::ADC__A_$HL, 8},
	{cpu::TEMPLATED_OPCODE::ADC__A_R, 4},
	{cpu::TEMPLATED_OPCODE::ADC__A_U8, 8},
	{cpu::TEMPLATED_OPCODE::ADD__A_$HL, 8},
	{cpu::TEMPLATED_OPCODE::ADD__A_R, 4},
	{cpu::TEMPLATED_OPCODE::ADD__A_U8, 8},
	{cpu::TEMPLATED_OPCODE::ADD__HL_RR, 8},
	{cpu::TEMPLATED_OPCODE::ADD__SP_S8, 16},
	{cpu::TEMPLATED_OPCODE::AND__A_$HL, 8},
	{cpu::TEMPLATED_OPCODE::AND__A_R, 4},
	{cpu::TEMPLATED_OPCODE::AND__A_U8, 8},
	{cpu::TEMPLATED_OPCODE::BIT__n_$HL, 16},
	{cpu::TEMPLATED_OPCODE::BIT__n_R, 8},
	{cpu::TEMPLATED_OPCODE::CALL__CC_U16_b, 12},
	{cpu::TEMPLATED_OPCODE::CALL__CC_U16_nb, 12},
	{cpu::TEMPLATED_OPCODE::CALL__U16, 24},
	{cpu::TEMPLATED_OPCODE::CCF, 4},
	{cpu::TEMPLATED_OPCODE::CP__A_$HL, 8},
	{cpu::TEMPLATED_OPCODE::CP__A_R, 4},
	{cpu::TEMPLATED_OPCODE::CP__A_U8, 8},
	{cpu::TEMPLATED_OPCODE::CPL, 4},
	{cpu::TEMPLATED_OPCODE::DAA, 4},
	{cpu::TEMPLATED_OPCODE::DEC__$HL, 12},
	{cpu::TEMPLATED_OPCODE::DEC__R, 4},
	{cpu::TEMPLATED_OPCODE::DEC__RR, 8},
	{cpu::TEMPLATED_OPCODE::DI, 4},
	{cpu::TEMPLATED_OPCODE::EI, 4},
	{cpu::TEMPLATED_OPCODE::HALT, 4},
	{cpu::TEMPLATED_OPCODE::INC__$HL, 12},
	{cpu::TEMPLATED_OPCODE::INC__R, 4},
	{cpu::TEMPLATED_OPCODE::INC__RR, 8},
	{cpu::TEMPLATED_OPCODE::JP__$HL, 4},
	{cpu::TEMPLATED_OPCODE::JP__CC_U16_b, 16},
	{cpu::TEMPLATED_OPCODE::JP__CC_U16_nb, 12},
	{cpu::TEMPLATED_OPCODE::JP__U16, 16},
	{cpu::TEMPLATED_OPCODE::JR__CC_S8_b, 12},
	{cpu::TEMPLATED_OPCODE::JR__CC_S8_nb, 8},
	{cpu::TEMPLATED_OPCODE::JR__S8, 12},
	{cpu::TEMPLATED_OPCODE::LD__$R_R, 8},
	{cpu::TEMPLATED_OPCODE::LD__$RR_R, 8},
	{cpu::TEMPLATED_OPCODE::LD__$RR_U8, 12},
	{cpu::TEMPLATED_OPCODE::LD__$U16_R, 16},
	{cpu::TEMPLATED_OPCODE::LD__$U16_RR, 20},
	{cpu::TEMPLATED_OPCODE::LDHL__SP_S8, 12},
	{cpu::TEMPLATED_OPCODE::LD__R_$R, 8},
	{cpu::TEMPLATED_OPCODE::LD__R_$RR, 8},
	{cpu::TEMPLATED_OPCODE::LD__R_$U16, 16},
	{cpu::TEMPLATED_OPCODE::LD__R_R, 4},
	{cpu::TEMPLATED_OPCODE::LD__R_U8, 8},
	{cpu::TEMPLATED_OPCODE::LD__RR_RR, 8},
	{cpu::TEMPLATED_OPCODE::LD__RR_U16, 12},
	{cpu::TEMPLATED_OPCODE::LDD__$HL_R, 8},
	{cpu::TEMPLATED_OPCODE::LDD__R_$HL, 8},
	{cpu::TEMPLATED_OPCODE::LDH__$U8_R, 12},
	{cpu::TEMPLATED_OPCODE::LDH__R_$U8, 12},
	{cpu::TEMPLATED_OPCODE::LDI__$HL_R, 8},
	{cpu::TEMPLATED_OPCODE::LDI__R_$HL, 8},
	{cpu::TEMPLATED_OPCODE::NOP, 4},
	{cpu::TEMPLATED_OPCODE::OR__A_$HL, 8},
	{cpu::TEMPLATED_OPCODE::OR__A_R, 4},
	{cpu::TEMPLATED_OPCODE::OR__A_U8, 8},
	{cpu::TEMPLATED_OPCODE::POP__RR, 12},
	{cpu::TEMPLATED_OPCODE::PREFIX__CB, 4},
	{cpu::TEMPLATED_OPCODE::PUSH__RR, 16},
	{cpu::TEMPLATED_OPCODE::RES__n_$HL, 16},
	{cpu::TEMPLATED_OPCODE::RES__n_R, 8},
	{cpu::TEMPLATED_OPCODE::RET, 16},
	{cpu::TEMPLATED_OPCODE::RET__CC_b, 20},
	{cpu::TEMPLATED_OPCODE::RET__CC_nb, 8},
	{cpu::TEMPLATED_OPCODE::RETI, 16},
	{cpu::TEMPLATED_OPCODE::RL__$HL, 16},
	{cpu::TEMPLATED_OPCODE::RL__R, 8},
	{cpu::TEMPLATED_OPCODE::RLA, 4},
	{cpu::TEMPLATED_OPCODE::RLC__$HL, 16},
	{cpu::TEMPLATED_OPCODE::RLC__R, 8},
	{cpu::TEMPLATED_OPCODE::RLCA, 4},
	{cpu::TEMPLATED_OPCODE::RR__$HL, 16},
	{cpu::TEMPLATED_OPCODE::RR__R, 8},
	{cpu::TEMPLATED_OPCODE::RRA, 4},
	{cpu::TEMPLATED_OPCODE::RRC__$HL, 16},
	{cpu::TEMPLATED_OPCODE::RRC__R, 8},
	{cpu::TEMPLATED_OPCODE::RRCA, 4},
	{cpu::TEMPLATED_OPCODE::RST__nH, 16},
	{cpu::TEMPLATED_OPCODE::SBC__A_$HL, 8},
	{cpu::TEMPLATED_OPCODE::SBC__A_R, 4},
	{cpu::TEMPLATED_OPCODE::SBC__A_U8, 8},
	{cpu::TEMPLATED_OPCODE::SCF, 4},
	{cpu::TEMPLATED_OPCODE::SET__n_$HL, 16},
	{cpu::TEMPLATED_OPCODE::SET__n_R, 8},
	{cpu::TEMPLATED_OPCODE::SLA__$HL, 16},
	{cpu::TEMPLATED_OPCODE::SLA__R, 8},
	{cpu::TEMPLATED_OPCODE::SRA__$HL, 16},
	{cpu::TEMPLATED_OPCODE::SRA__R, 8},
	{cpu::TEMPLATED_OPCODE::SRL__$HL, 16},
	{cpu::TEMPLATED_OPCODE::SRL__R, 8},
	{cpu::TEMPLATED_OPCODE::STOP__0, 4},
	{cpu::TEMPLATED_OPCODE::SUB__A_$HL, 8},
	{cpu::TEMPLATED_OPCODE::SUB__A_R, 4},
	{cpu::TEMPLATED_OPCODE::SUB__A_U8, 8},
	{cpu::TEMPLATED_OPCODE::SWAP__$HL, 16},
	{cpu::TEMPLATED_OPCODE::SWAP__R, 8},
	{cpu::TEMPLATED_OPCODE::XOR__A_$HL, 8},
	{cpu::TEMPLATED_OPCODE::XOR__A_R, 4},
	{cpu::TEMPLATED_OPCODE::XOR__A_U8, 8}
};

const std::map<cpu::INTERRUPT, std::uint8_t> cpu::INTERRUPT_VECTOR = {
	{cpu::INTERRUPT::VBlank, 0x40},
	{cpu::INTERRUPT::LCD_STAT, 0x48},
	{cpu::INTERRUPT::Timer, 0x50},
	{cpu::INTERRUPT::Serial, 0x58},
	{cpu::INTERRUPT::Joypad, 0x60}
};

const std::array<cpu::INTERRUPT,5> cpu::INTERRUPTS = {INTERRUPT::VBlank, INTERRUPT::LCD_STAT, INTERRUPT::Timer, INTERRUPT::Serial, INTERRUPT::Joypad};

cpu::cpu()
	: _registers(), _ime(false)
{
	
}

cpu::~cpu(void)
{

}

std::uint8_t cpu::execute_instruction(const bool& print_opcodes)
{
	cpu::OPCODE opcode;
	cpu::PREFIXED_OPCODE prefixed_opcode;

	std::uint8_t cycles = 0;
	

	opcode = (cpu::OPCODE)this->_bus->get_u8_memory_value(this->_registers.PC);
	if (print_opcodes)
	{
		cpu::print_opcode(opcode, this->_registers.PC);
	}

	switch (opcode)
	{
		case cpu::OPCODE::NOP:

			cycles += this->NOP();
			break;
		case cpu::OPCODE::LD__BC_U16:

			cycles += this->LD__RR_U16(REGISTER::BC);
			break;
		case cpu::OPCODE::LD__$BC_A:

			cycles += this->LD__$RR_R(REGISTER::BC, REGISTER::A);
			break;
		case cpu::OPCODE::INC__BC:

			cycles += this->INC__RR(REGISTER::BC);
			break;
		case cpu::OPCODE::INC__B:

			cycles += this->INC__R(REGISTER::B);
			break;
		case cpu::OPCODE::DEC__B:

			cycles += this->DEC__R(REGISTER::B);
			break;
		case cpu::OPCODE::LD__B_U8:

			cycles += this->LD__R_U8(REGISTER::B);
			break;
		case cpu::OPCODE::RLCA:

			cycles += this->RLCA();
			break;
		case cpu::OPCODE::LD__$U16_SP:

			cycles += this->LD__$U16_RR(REGISTER::SP);
			break;
		case cpu::OPCODE::ADD__HL_BC:

			cycles += this->ADD__HL_RR(REGISTER::BC);
			break;
		case cpu::OPCODE::LD__A_$BC:

			cycles += this->LD__R_$RR(REGISTER::A, REGISTER::BC);
			break;
		case cpu::OPCODE::DEC__BC:

			cycles += this->DEC__RR(REGISTER::BC);
			break;
		case cpu::OPCODE::INC__C:

			cycles += this->INC__R(REGISTER::C);
			break;
		case cpu::OPCODE::DEC__C:

			cycles += this->DEC__R(REGISTER::C);
			break;
		case cpu::OPCODE::LD__C_U8:

			cycles += this->LD__R_U8(REGISTER::C);
			break;
		case cpu::OPCODE::RRCA:

			cycles += this->RRCA();
			break;
		case cpu::OPCODE::STOP:

			throw std::logic_error("<" + cpu::OPCODE_MNEMONIC.at(opcode) + ">");
			break;
		case cpu::OPCODE::LD__DE_U16:

			cycles += this->LD__RR_U16(REGISTER::DE);
			break;
		case cpu::OPCODE::LD__$DE_A:

			cycles += this->LD__$RR_R(REGISTER::DE, REGISTER::A);
			break;
		case cpu::OPCODE::INC__DE:

			cycles += this->INC__RR(REGISTER::DE);
			break;
		case cpu::OPCODE::INC__D:

			cycles += this->INC__R(REGISTER::D);
			break;
		case cpu::OPCODE::DEC__D:

			cycles += this->DEC__R(REGISTER::D);
			break;
		case cpu::OPCODE::LD__D_U8:

			cycles += this->LD__R_U8(REGISTER::D);
			break;
		case cpu::OPCODE::RLA:

			cycles += this->RLA();
			break;
		case cpu::OPCODE::JR__S8:

			cycles += this->JR__S8();
			break;
		case cpu::OPCODE::ADD__HL_DE:

			cycles += this->ADD__HL_RR(REGISTER::DE);
			break;
		case cpu::OPCODE::LD__A_$DE:

			cycles += this->LD__R_$RR(REGISTER::A, REGISTER::DE);
			break;
		case cpu::OPCODE::DEC__DE:

			cycles += this->DEC__RR(REGISTER::DE);
			break;
		case cpu::OPCODE::INC__E:

			cycles += this->INC__R(REGISTER::E);
			break;
		case cpu::OPCODE::DEC__E:

			cycles += this->DEC__R(REGISTER::E);
			break;
		case cpu::OPCODE::LD__E_U8:

			cycles += this->LD__R_U8(REGISTER::E);
			break;
		case cpu::OPCODE::RRA:

			cycles += this->RRA();
			break;
		case cpu::OPCODE::JR__NZ_S8:

			cycles += this->JR__CC_S8(FLAG_CONDITION::NZ);
			break;
		case cpu::OPCODE::LD__HL_U16:

			cycles += this->LD__RR_U16(REGISTER::HL);
			break;
		case cpu::OPCODE::LDI__$HL_A:

			cycles += this->LDI__$HL_R(REGISTER::A);
			break;
		case cpu::OPCODE::INC__HL:

			cycles += this->INC__RR(REGISTER::HL);
			break;
		case cpu::OPCODE::INC__H:

			cycles += this->INC__R(REGISTER::H);
			break;
		case cpu::OPCODE::DEC__H:

			cycles += this->DEC__R(REGISTER::H);
			break;
		case cpu::OPCODE::LD__H_U8:

			cycles += this->LD__R_U8(REGISTER::H);
			break;
		case cpu::OPCODE::DAA:

			cycles += this->DAA();
			break;
		case cpu::OPCODE::JR__Z_S8:

			cycles += this->JR__CC_S8(FLAG_CONDITION::Z);
			break;
		case cpu::OPCODE::ADD__HL_HL:

			cycles += this->ADD__HL_RR(REGISTER::HL);
			break;
		case cpu::OPCODE::LDI__A_$HL:

			cycles += this->LDI__R_$HL(REGISTER::A);
			break;
		case cpu::OPCODE::DEC__HL:

			cycles += this->DEC__RR(REGISTER::HL);
			break;
		case cpu::OPCODE::INC__L:

			cycles += this->INC__R(REGISTER::L);
			break;
		case cpu::OPCODE::DEC__L:

			cycles += this->DEC__R(REGISTER::L);
			break;
		case cpu::OPCODE::LD__L_U8:

			cycles += this->LD__R_U8(REGISTER::L);
			break;
		case cpu::OPCODE::CPL:

			cycles += this->CPL();
			break;
		case cpu::OPCODE::JR__NC_S8:

			cycles += this->JR__CC_S8(FLAG_CONDITION::NC);
			break;
		case cpu::OPCODE::LD__SP_U16:

			cycles += this->LD__RR_U16(REGISTER::SP);
			break;
		case cpu::OPCODE::LDD__$HL_A:

			cycles += this->LDD__$HL_R(REGISTER::A);
			break;
		case cpu::OPCODE::INC__SP:

			cycles += this->INC__RR(REGISTER::SP);
			break;
		case cpu::OPCODE::INC__$HL:

			cycles += this->INC__$HL();
			break;
		case cpu::OPCODE::DEC__$HL:

			cycles += this->DEC__$HL();
			break;
		case cpu::OPCODE::LD__$HL_U8:

			cycles += this->LD__$RR_U8(REGISTER::HL);
			break;
		case cpu::OPCODE::SCF:

			cycles += this->SCF();
			break;
		case cpu::OPCODE::JR__C_S8:

			cycles += this->JR__CC_S8(FLAG_CONDITION::C);
			break;
		case cpu::OPCODE::ADD__HL_SP:

			cycles += this->ADD__HL_RR(REGISTER::SP);
			break;
		case cpu::OPCODE::LDD__A_$HL:

			cycles += this->LDD__R_$HL(REGISTER::A);
			break;
		case cpu::OPCODE::DEC__SP:

			cycles += this->DEC__RR(REGISTER::SP);
			break;
		case cpu::OPCODE::INC__A:

			cycles += this->INC__R(REGISTER::A);
			break;
		case cpu::OPCODE::DEC__A:

			cycles += this->DEC__R(REGISTER::A);
			break;
		case cpu::OPCODE::LD__A_U8:

			cycles += this->LD__R_U8(REGISTER::A);
			break;
		case cpu::OPCODE::CCF:

			cycles += this->CCF();
			break;
		case cpu::OPCODE::LD__B_B:

			cycles += this->LD__R_R(REGISTER::B, REGISTER::B);
			break;
		case cpu::OPCODE::LD__B_C:

			cycles += this->LD__R_R(REGISTER::B, REGISTER::C);
			break;
		case cpu::OPCODE::LD__B_D:

			cycles += this->LD__R_R(REGISTER::B, REGISTER::D);
			break;
		case cpu::OPCODE::LD__B_E:

			cycles += this->LD__R_R(REGISTER::B, REGISTER::E);
			break;
		case cpu::OPCODE::LD__B_H:

			cycles += this->LD__R_R(REGISTER::B, REGISTER::H);
			break;
		case cpu::OPCODE::LD__B_L:

			cycles += this->LD__R_R(REGISTER::B, REGISTER::L);
			break;
		case cpu::OPCODE::LD__B_$HL:

			cycles += this->LD__R_$RR(REGISTER::B, REGISTER::HL);
			break;
		case cpu::OPCODE::LD__B_A:

			cycles += this->LD__R_R(REGISTER::B, REGISTER::A);
			break;
		case cpu::OPCODE::LD__C_B:

			cycles += this->LD__R_R(REGISTER::C, REGISTER::B);
			break;
		case cpu::OPCODE::LD__C_C:

			cycles += this->LD__R_R(REGISTER::C, REGISTER::C);
			break;
		case cpu::OPCODE::LD__C_D:

			cycles += this->LD__R_R(REGISTER::C, REGISTER::D);
			break;
		case cpu::OPCODE::LD__C_E:

			cycles += this->LD__R_R(REGISTER::C, REGISTER::E);
			break;
		case cpu::OPCODE::LD__C_H:

			cycles += this->LD__R_R(REGISTER::C, REGISTER::H);
			break;
		case cpu::OPCODE::LD__C_L:

			cycles += this->LD__R_R(REGISTER::C, REGISTER::L);
			break;
		case cpu::OPCODE::LD__C_$HL:

			cycles += this->LD__R_$RR(REGISTER::C, REGISTER::HL);
			break;
		case cpu::OPCODE::LD__C_A:

			cycles += this->LD__R_R(REGISTER::C, REGISTER::A);
			break;
		case cpu::OPCODE::LD__D_B:

			cycles += this->LD__R_R(REGISTER::D, REGISTER::B);
			break;
		case cpu::OPCODE::LD__D_C:

			cycles += this->LD__R_R(REGISTER::D, REGISTER::C);
			break;
		case cpu::OPCODE::LD__D_D:

			cycles += this->LD__R_R(REGISTER::D, REGISTER::D);
			break;
		case cpu::OPCODE::LD__D_E:

			cycles += this->LD__R_R(REGISTER::D, REGISTER::E);
			break;
		case cpu::OPCODE::LD__D_H:

			cycles += this->LD__R_R(REGISTER::D, REGISTER::H);
			break;
		case cpu::OPCODE::LD__D_L:

			cycles += this->LD__R_R(REGISTER::D, REGISTER::L);
			break;
		case cpu::OPCODE::LD__D_$HL:

			cycles += this->LD__R_$RR(REGISTER::D, REGISTER::HL);
			break;
		case cpu::OPCODE::LD__D_A:

			cycles += this->LD__R_R(REGISTER::D, REGISTER::A);
			break;
		case cpu::OPCODE::LD__E_B:

			cycles += this->LD__R_R(REGISTER::E, REGISTER::B);
			break;
		case cpu::OPCODE::LD__E_C:

			cycles += this->LD__R_R(REGISTER::E, REGISTER::C);
			break;
		case cpu::OPCODE::LD__E_D:

			cycles += this->LD__R_R(REGISTER::E, REGISTER::D);
			break;
		case cpu::OPCODE::LD__E_E:

			cycles += this->LD__R_R(REGISTER::E, REGISTER::E);
			break;
		case cpu::OPCODE::LD__E_H:

			cycles += this->LD__R_R(REGISTER::E, REGISTER::H);
			break;
		case cpu::OPCODE::LD__E_L:

			cycles += this->LD__R_R(REGISTER::E, REGISTER::L);
			break;
		case cpu::OPCODE::LD__E_$HL:

			cycles += this->LD__R_$RR(REGISTER::E, REGISTER::HL);
			break;
		case cpu::OPCODE::LD__E_A:

			cycles += this->LD__R_R(REGISTER::E, REGISTER::A);
			break;
		case cpu::OPCODE::LD__H_B:

			cycles += this->LD__R_R(REGISTER::H, REGISTER::B);
			break;
		case cpu::OPCODE::LD__H_C:

			cycles += this->LD__R_R(REGISTER::H, REGISTER::C);
			break;
		case cpu::OPCODE::LD__H_D:

			cycles += this->LD__R_R(REGISTER::H, REGISTER::D);
			break;
		case cpu::OPCODE::LD__H_E:

			cycles += this->LD__R_R(REGISTER::H, REGISTER::E);
			break;
		case cpu::OPCODE::LD__H_H:

			cycles += this->LD__R_R(REGISTER::H, REGISTER::H);
			break;
		case cpu::OPCODE::LD__H_L:

			cycles += this->LD__R_R(REGISTER::H, REGISTER::L);
			break;
		case cpu::OPCODE::LD__H_$HL:

			cycles += this->LD__R_$RR(REGISTER::H, REGISTER::HL);
			break;
		case cpu::OPCODE::LD__H_A:

			cycles += this->LD__R_R(REGISTER::H, REGISTER::A);
			break;
		case cpu::OPCODE::LD__L_B:

			cycles += this->LD__R_R(REGISTER::L, REGISTER::B);
			break;
		case cpu::OPCODE::LD__L_C:

			cycles += this->LD__R_R(REGISTER::L, REGISTER::C);
			break;
		case cpu::OPCODE::LD__L_D:

			cycles += this->LD__R_R(REGISTER::L, REGISTER::D);
			break;
		case cpu::OPCODE::LD__L_E:

			cycles += this->LD__R_R(REGISTER::L, REGISTER::E);
			break;
		case cpu::OPCODE::LD__L_H:

			cycles += this->LD__R_R(REGISTER::L, REGISTER::H);
			break;
		case cpu::OPCODE::LD__L_L:

			cycles += this->LD__R_R(REGISTER::L, REGISTER::L);
			break;
		case cpu::OPCODE::LD__L_$HL:

			cycles += this->LD__R_$RR(REGISTER::L, REGISTER::HL);
			break;
		case cpu::OPCODE::LD__L_A:

			cycles += this->LD__R_R(REGISTER::L, REGISTER::A);
			break;
		case cpu::OPCODE::LD__$HL_B:

			cycles += this->LD__$RR_R(REGISTER::HL, REGISTER::B);
			break;
		case cpu::OPCODE::LD__$HL_C:

			cycles += this->LD__$RR_R(REGISTER::HL, REGISTER::C);
			break;
		case cpu::OPCODE::LD__$HL_D:

			cycles += this->LD__$RR_R(REGISTER::HL, REGISTER::D);
			break;
		case cpu::OPCODE::LD__$HL_E:

			cycles += this->LD__$RR_R(REGISTER::HL, REGISTER::E);
			break;
		case cpu::OPCODE::LD__$HL_H:

			cycles += this->LD__$RR_R(REGISTER::HL, REGISTER::H);
			break;
		case cpu::OPCODE::LD__$HL_L:

			cycles += this->LD__$RR_R(REGISTER::HL, REGISTER::L);
			break;
		case cpu::OPCODE::HALT:

			cycles += this->HALT();
			break;
		case cpu::OPCODE::LD__$HL_A:

			cycles += this->LD__$RR_R(REGISTER::HL, REGISTER::A);
			break;
		case cpu::OPCODE::LD__A_B:

			cycles += this->LD__R_R(REGISTER::A, REGISTER::B);
			break;
		case cpu::OPCODE::LD__A_C:

			cycles += this->LD__R_R(REGISTER::A, REGISTER::C);
			break;
		case cpu::OPCODE::LD__A_D:

			cycles += this->LD__R_R(REGISTER::A, REGISTER::D);
			break;
		case cpu::OPCODE::LD__A_E:

			cycles += this->LD__R_R(REGISTER::A, REGISTER::E);
			break;
		case cpu::OPCODE::LD__A_H:

			cycles += this->LD__R_R(REGISTER::A, REGISTER::H);
			break;
		case cpu::OPCODE::LD__A_L:

			cycles += this->LD__R_R(REGISTER::A, REGISTER::L);
			break;
		case cpu::OPCODE::LD__A_$HL:

			cycles += this->LD__R_$RR(REGISTER::A, REGISTER::HL);
			break;
		case cpu::OPCODE::LD__A_A:

			cycles += this->LD__R_R(REGISTER::A, REGISTER::A);
			break;
		case cpu::OPCODE::ADD__A_B:

			cycles += this->ADD__A_R(REGISTER::B);
			break;
		case cpu::OPCODE::ADD__A_C:

			cycles += this->ADD__A_R(REGISTER::C);
			break;
		case cpu::OPCODE::ADD__A_D:

			cycles += this->ADD__A_R(REGISTER::D);
			break;
		case cpu::OPCODE::ADD__A_E:

			cycles += this->ADD__A_R(REGISTER::E);
			break;
		case cpu::OPCODE::ADD__A_H:

			cycles += this->ADD__A_R(REGISTER::H);
			break;
		case cpu::OPCODE::ADD__A_L:

			cycles += this->ADD__A_R(REGISTER::L);
			break;
		case cpu::OPCODE::ADD__A_$HL:

			cycles += this->ADD__A_$HL();
			break;
		case cpu::OPCODE::ADD__A_A:

			cycles += this->ADD__A_R(REGISTER::A);
			break;
		case cpu::OPCODE::ADC__A_B:

			cycles += this->ADC__A_R(REGISTER::B);
			break;
		case cpu::OPCODE::ADC__A_C:

			cycles += this->ADC__A_R(REGISTER::C);
			break;
		case cpu::OPCODE::ADC__A_D:

			cycles += this->ADC__A_R(REGISTER::D);
			break;
		case cpu::OPCODE::ADC__A_E:

			cycles += this->ADC__A_R(REGISTER::E);
			break;
		case cpu::OPCODE::ADC__A_H:

			cycles += this->ADC__A_R(REGISTER::H);
			break;
		case cpu::OPCODE::ADC__A_L:

			cycles += this->ADC__A_R(REGISTER::L);
			break;
		case cpu::OPCODE::ADC__A_$HL:

			cycles += this->ADC__A_$HL();
			break;
		case cpu::OPCODE::ADC__A_A:

			cycles += this->ADC__A_R(REGISTER::A);
			break;
		case cpu::OPCODE::SUB__A_B:

			cycles += this->SUB__A_R(REGISTER::B);
			break;
		case cpu::OPCODE::SUB__A_C:

			cycles += this->SUB__A_R(REGISTER::C);
			break;
		case cpu::OPCODE::SUB__A_D:

			cycles += this->SUB__A_R(REGISTER::D);
			break;
		case cpu::OPCODE::SUB__A_E:

			cycles += this->SUB__A_R(REGISTER::E);
			break;
		case cpu::OPCODE::SUB__A_H:

			cycles += this->SUB__A_R(REGISTER::H);
			break;
		case cpu::OPCODE::SUB__A_L:

			cycles += this->SUB__A_R(REGISTER::L);
			break;
		case cpu::OPCODE::SUB__A_$HL:

			cycles += this->SUB__A_$HL();
			break;
		case cpu::OPCODE::SUB__A_A:

			cycles += this->SUB__A_R(REGISTER::A);
			break;
		case cpu::OPCODE::SBC__A_B:

			cycles += this->SBC__A_R(REGISTER::B);
			break;
		case cpu::OPCODE::SBC__A_C:

			cycles += this->SBC__A_R(REGISTER::C);
			break;
		case cpu::OPCODE::SBC__A_D:

			cycles += this->SBC__A_R(REGISTER::D);
			break;
		case cpu::OPCODE::SBC__A_E:

			cycles += this->SBC__A_R(REGISTER::E);
			break;
		case cpu::OPCODE::SBC__A_H:

			cycles += this->SBC__A_R(REGISTER::H);
			break;
		case cpu::OPCODE::SBC__A_L:

			cycles += this->SBC__A_R(REGISTER::L);
			break;
		case cpu::OPCODE::SBC__A_$HL:

			cycles += this->SBC__A_$HL();
			break;
		case cpu::OPCODE::SBC__A_A:

			cycles += this->SBC__A_R(REGISTER::A);
			break;
		case cpu::OPCODE::AND__A_B:

			cycles += this->AND__A_R(REGISTER::B);
			break;
		case cpu::OPCODE::AND__A_C:

			cycles += this->AND__A_R(REGISTER::C);
			break;
		case cpu::OPCODE::AND__A_D:

			cycles += this->AND__A_R(REGISTER::D);
			break;
		case cpu::OPCODE::AND__A_E:

			cycles += this->AND__A_R(REGISTER::E);
			break;
		case cpu::OPCODE::AND__A_H:

			cycles += this->AND__A_R(REGISTER::H);
			break;
		case cpu::OPCODE::AND__A_L:

			cycles += this->AND__A_R(REGISTER::L);
			break;
		case cpu::OPCODE::AND__A_$HL:

			cycles += this->AND__A_$HL();
			break;
		case cpu::OPCODE::AND__A_A:

			cycles += this->AND__A_R(REGISTER::A);
			break;
		case cpu::OPCODE::XOR__A_B:

			cycles += this->XOR__A_R(REGISTER::B);
			break;
		case cpu::OPCODE::XOR__A_C:

			cycles += this->XOR__A_R(REGISTER::C);
			break;
		case cpu::OPCODE::XOR__A_D:

			cycles += this->XOR__A_R(REGISTER::D);
			break;
		case cpu::OPCODE::XOR__A_E:

			cycles += this->XOR__A_R(REGISTER::E);
			break;
		case cpu::OPCODE::XOR__A_H:

			cycles += this->XOR__A_R(REGISTER::H);
			break;
		case cpu::OPCODE::XOR__A_L:

			cycles += this->XOR__A_R(REGISTER::L);
			break;
		case cpu::OPCODE::XOR__A_$HL:

			cycles += this->XOR__A_$HL();
			break;
		case cpu::OPCODE::XOR__A_A:

			cycles += this->XOR__A_R(REGISTER::A);
			break;
		case cpu::OPCODE::OR__A_B:

			cycles += this->OR__A_R(REGISTER::B);
			break;
		case cpu::OPCODE::OR__A_C:

			cycles += this->OR__A_R(REGISTER::C);
			break;
		case cpu::OPCODE::OR__A_D:

			cycles += this->OR__A_R(REGISTER::D);
			break;
		case cpu::OPCODE::OR__A_E:

			cycles += this->OR__A_R(REGISTER::E);
			break;
		case cpu::OPCODE::OR__A_H:

			cycles += this->OR__A_R(REGISTER::H);
			break;
		case cpu::OPCODE::OR__A_L:

			cycles += this->OR__A_R(REGISTER::L);
			break;
		case cpu::OPCODE::OR__A_$HL:

			cycles += this->OR__A_$HL();
			break;
		case cpu::OPCODE::OR__A_A:

			cycles += this->OR__A_R(REGISTER::A);
			break;
		case cpu::OPCODE::CP__A_B:

			cycles += this->CP__A_R(REGISTER::B);
			break;
		case cpu::OPCODE::CP__A_C:

			cycles += this->CP__A_R(REGISTER::C);
			break;
		case cpu::OPCODE::CP__A_D:

			cycles += this->CP__A_R(REGISTER::D);
			break;
		case cpu::OPCODE::CP__A_E:

			cycles += this->CP__A_R(REGISTER::E);
			break;
		case cpu::OPCODE::CP__A_H:

			cycles += this->CP__A_R(REGISTER::H);
			break;
		case cpu::OPCODE::CP__A_L:

			cycles += this->CP__A_R(REGISTER::L);
			break;
		case cpu::OPCODE::CP__A_$HL:

			cycles += this->CP__A_$HL();
			break;
		case cpu::OPCODE::CP__A_A:

			cycles += this->CP__A_R(REGISTER::A);
			break;
		case cpu::OPCODE::RET__NZ:

			cycles += this->RET__CC(FLAG_CONDITION::NZ);
			break;
		case cpu::OPCODE::POP__BC:

			cycles += this->POP__RR(REGISTER::BC);
			break;
		case cpu::OPCODE::JP__NZ_U16:

			cycles += this->JP__CC_U16(FLAG_CONDITION::NZ);
			break;
		case cpu::OPCODE::JP__U16:

			cycles += this->JP__U16();
			break;
		case cpu::OPCODE::CALL__NZ_U16:

			cycles += this->CALL__CC_U16(FLAG_CONDITION::NZ);
			break;
		case cpu::OPCODE::PUSH__BC:

			cycles += this->PUSH__RR(REGISTER::BC);
			break;
		case cpu::OPCODE::ADD__A_U8:

			cycles += this->ADD__A_U8();
			break;
		case cpu::OPCODE::RST__00H:

			cycles += this->RST__nH(0x00);
			break;
		case cpu::OPCODE::RET__Z:

			cycles += this->RET__CC(FLAG_CONDITION::Z);
			break;
		case cpu::OPCODE::RET:

			cycles += this->RET();
			break;
		case cpu::OPCODE::JP__Z_U16:

			cycles += this->JP__CC_U16(FLAG_CONDITION::Z);
			break;
		case cpu::OPCODE::PREFIX__CB:

			cycles += this->PREFIX_CB();

			prefixed_opcode = (cpu::PREFIXED_OPCODE)this->_bus->get_u8_memory_value(this->_registers.PC);
			if (print_opcodes)
			{
				cpu::print_opcode(prefixed_opcode, this->_registers.PC);
			}

			switch (prefixed_opcode)
			{
				case cpu::PREFIXED_OPCODE::RLC__B:

					cycles += this->RLC__R(REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RLC__C:

					cycles += this->RLC__R(REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RLC__D:

					cycles += this->RLC__R(REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RLC__E:

					cycles += this->RLC__R(REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RLC__H:

					cycles += this->RLC__R(REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RLC__L:

					cycles += this->RLC__R(REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RLC__$HL:

					cycles += this->RLC__$HL();
					break;
				case cpu::PREFIXED_OPCODE::RLC__A:

					cycles += this->RLC__R(REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RRC__B:

					cycles += this->RRC__R(REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RRC__C:

					cycles += this->RRC__R(REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RRC__D:

					cycles += this->RRC__R(REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RRC__E:

					cycles += this->RRC__R(REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RRC__H:

					cycles += this->RRC__R(REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RRC__L:

					cycles += this->RRC__R(REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RRC__$HL:

					cycles += this->RRC__$HL();
					break;
				case cpu::PREFIXED_OPCODE::RRC__A:

					cycles += this->RRC__R(REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RL__B:

					cycles += this->RL__R(REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RL__C:

					cycles += this->RL__R(REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RL__D:

					cycles += this->RL__R(REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RL__E:

					cycles += this->RL__R(REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RL__H:

					cycles += this->RL__R(REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RL__L:

					cycles += this->RL__R(REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RL__$HL:

					cycles += this->RL__$HL();
					break;
				case cpu::PREFIXED_OPCODE::RL__A:

					cycles += this->RL__R(REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RR__B:

					cycles += this->RR__R(REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RR__C:

					cycles += this->RR__R(REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RR__D:

					cycles += this->RR__R(REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RR__E:

					cycles += this->RR__R(REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RR__H:

					cycles += this->RR__R(REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RR__L:

					cycles += this->RR__R(REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RR__$HL:

					cycles += this->RR__$HL();
					break;
				case cpu::PREFIXED_OPCODE::RR__A:

					cycles += this->RR__R(REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SLA__B:

					cycles += this->SLA__R(REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SLA__C:

					cycles += this->SLA__R(REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SLA__D:

					cycles += this->SLA__R(REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SLA__E:

					cycles += this->SLA__R(REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SLA__H:

					cycles += this->SLA__R(REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SLA__L:

					cycles += this->SLA__R(REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SLA__$HL:

					cycles += this->SLA__$HL();
					break;
				case cpu::PREFIXED_OPCODE::SLA__A:

					cycles += this->SLA__R(REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SRA__B:

					cycles += this->SRA__R(REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SRA__C:

					cycles += this->SRA__R(REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SRA__D:

					cycles += this->SRA__R(REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SRA__E:

					cycles += this->SRA__R(REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SRA__H:

					cycles += this->SRA__R(REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SRA__L:

					cycles += this->SRA__R(REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SRA__$HL:

					cycles += this->SRA__$HL();
					break;
				case cpu::PREFIXED_OPCODE::SRA__A:

					cycles += this->SRA__R(REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SWAP__B:

					cycles += this->SWAP__R(REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SWAP__C:

					cycles += this->SWAP__R(REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SWAP__D:

					cycles += this->SWAP__R(REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SWAP__E:

					cycles += this->SWAP__R(REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SWAP__H:

					cycles += this->SWAP__R(REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SWAP__L:

					cycles += this->SWAP__R(REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SWAP__$HL:

					cycles += this->SWAP__$HL();
					break;
				case cpu::PREFIXED_OPCODE::SWAP__A:

					cycles += this->SWAP__R(REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SRL__B:

					cycles += this->SRL__R(REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SRL__C:

					cycles += this->SRL__R(REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SRL__D:

					cycles += this->SRL__R(REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SRL__E:

					cycles += this->SRL__R(REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SRL__H:

					cycles += this->SRL__R(REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SRL__L:

					cycles += this->SRL__R(REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SRL__$HL:

					cycles += this->SRL__$HL();
					break;
				case cpu::PREFIXED_OPCODE::SRL__A:

					cycles += this->SRL__R(REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::BIT__0_B:

					cycles += this->BIT__n_R(0, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::BIT__0_C:

					cycles += this->BIT__n_R(0, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::BIT__0_D:

					cycles += this->BIT__n_R(0, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::BIT__0_E:

					cycles += this->BIT__n_R(0, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::BIT__0_H:

					cycles += this->BIT__n_R(0, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::BIT__0_L:

					cycles += this->BIT__n_R(0, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::BIT__0_$HL:

					cycles += this->BIT__n_$HL(0);
					break;
				case cpu::PREFIXED_OPCODE::BIT__0_A:

					cycles += this->BIT__n_R(0, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::BIT__1_B:

					cycles += this->BIT__n_R(1, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::BIT__1_C:

					cycles += this->BIT__n_R(1, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::BIT__1_D:

					cycles += this->BIT__n_R(1, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::BIT__1_E:

					cycles += this->BIT__n_R(1, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::BIT__1_H:

					cycles += this->BIT__n_R(1, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::BIT__1_L:

					cycles += this->BIT__n_R(1, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::BIT__1_$HL:

					cycles += this->BIT__n_$HL(1);
					break;
				case cpu::PREFIXED_OPCODE::BIT__1_A:

					cycles += this->BIT__n_R(1, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::BIT__2_B:
					
					cycles += this->BIT__n_R(2, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::BIT__2_C:

					cycles += this->BIT__n_R(2, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::BIT__2_D:

					cycles += this->BIT__n_R(2, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::BIT__2_E:

					cycles += this->BIT__n_R(2, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::BIT__2_H:

					cycles += this->BIT__n_R(2, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::BIT__2_L:

					cycles += this->BIT__n_R(2, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::BIT__2_$HL:

					cycles += this->BIT__n_$HL(2);
					break;
				case cpu::PREFIXED_OPCODE::BIT__2_A:

					cycles += this->BIT__n_R(2, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::BIT__3_B:

					cycles += this->BIT__n_R(3, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::BIT__3_C:

					cycles += this->BIT__n_R(3, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::BIT__3_D:

					cycles += this->BIT__n_R(3, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::BIT__3_E:

					cycles += this->BIT__n_R(3, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::BIT__3_H:

					cycles += this->BIT__n_R(3, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::BIT__3_L:

					cycles += this->BIT__n_R(3, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::BIT__3_$HL:

					cycles += this->BIT__n_$HL(3);
					break;
				case cpu::PREFIXED_OPCODE::BIT__3_A:

					cycles += this->BIT__n_R(3, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::BIT__4_B:

					cycles += this->BIT__n_R(4, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::BIT__4_C:

					cycles += this->BIT__n_R(4, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::BIT__4_D:

					cycles += this->BIT__n_R(4, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::BIT__4_E:

					cycles += this->BIT__n_R(4, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::BIT__4_H:

					cycles += this->BIT__n_R(4, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::BIT__4_L:

					cycles += this->BIT__n_R(4, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::BIT__4_$HL:

					cycles += this->BIT__n_$HL(4);
					break;
				case cpu::PREFIXED_OPCODE::BIT__4_A:

					cycles += this->BIT__n_R(4, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::BIT__5_B:

					cycles += this->BIT__n_R(5, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::BIT__5_C:

					cycles += this->BIT__n_R(5, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::BIT__5_D:

					cycles += this->BIT__n_R(5, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::BIT__5_E:

					cycles += this->BIT__n_R(5, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::BIT__5_H:

					cycles += this->BIT__n_R(5, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::BIT__5_L:

					cycles += this->BIT__n_R(5, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::BIT__5_$HL:

					cycles += this->BIT__n_$HL(5);
					break;
				case cpu::PREFIXED_OPCODE::BIT__5_A:

					cycles += this->BIT__n_R(5, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::BIT__6_B:

					cycles += this->BIT__n_R(6, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::BIT__6_C:

					cycles += this->BIT__n_R(6, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::BIT__6_D:

					cycles += this->BIT__n_R(6, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::BIT__6_E:

					cycles += this->BIT__n_R(6, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::BIT__6_H:

					cycles += this->BIT__n_R(6, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::BIT__6_L:

					cycles += this->BIT__n_R(6, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::BIT__6_$HL:

					cycles += this->BIT__n_$HL(6);
					break;
				case cpu::PREFIXED_OPCODE::BIT__6_A:

					cycles += this->BIT__n_R(6, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::BIT__7_B:

					cycles += this->BIT__n_R(7, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::BIT__7_C:

					cycles += this->BIT__n_R(7, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::BIT__7_D:

					cycles += this->BIT__n_R(7, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::BIT__7_E:

					cycles += this->BIT__n_R(7, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::BIT__7_H:

					cycles += this->BIT__n_R(7, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::BIT__7_L:

					cycles += this->BIT__n_R(7, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::BIT__7_$HL:

					cycles += this->BIT__n_$HL(7);
					break;
				case cpu::PREFIXED_OPCODE::BIT__7_A:

					cycles += this->BIT__n_R(7, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RES__0_B:

					cycles += this->RES__n_R(0, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RES__0_C:

					cycles += this->RES__n_R(0, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RES__0_D:

					cycles += this->RES__n_R(0, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RES__0_E:

					cycles += this->RES__n_R(0, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RES__0_H:

					cycles += this->RES__n_R(0, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RES__0_L:

					cycles += this->RES__n_R(0, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RES__0_$HL:

					cycles += this->RES__n_$HL(0);
					break;
				case cpu::PREFIXED_OPCODE::RES__0_A:

					cycles += this->RES__n_R(0, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RES__1_B:

					cycles += this->RES__n_R(1, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RES__1_C:

					cycles += this->RES__n_R(1, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RES__1_D:

					cycles += this->RES__n_R(1, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RES__1_E:

					cycles += this->RES__n_R(1, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RES__1_H:

					cycles += this->RES__n_R(1, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RES__1_L:

					cycles += this->RES__n_R(1, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RES__1_$HL:

					cycles += this->RES__n_$HL(1);
					break;
				case cpu::PREFIXED_OPCODE::RES__1_A:

					cycles += this->RES__n_R(1, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RES__2_B:

					cycles += this->RES__n_R(2, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RES__2_C:

					cycles += this->RES__n_R(2, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RES__2_D:

					cycles += this->RES__n_R(2, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RES__2_E:

					cycles += this->RES__n_R(2, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RES__2_H:

					cycles += this->RES__n_R(2, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RES__2_L:

					cycles += this->RES__n_R(2, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RES__2_$HL:

					cycles += this->RES__n_$HL(2);
					break;
				case cpu::PREFIXED_OPCODE::RES__2_A:

					cycles += this->RES__n_R(2, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RES__3_B:

					cycles += this->RES__n_R(3, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RES__3_C:

					cycles += this->RES__n_R(3, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RES__3_D:

					cycles += this->RES__n_R(3, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RES__3_E:

					cycles += this->RES__n_R(3, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RES__3_H:

					cycles += this->RES__n_R(3, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RES__3_L:

					cycles += this->RES__n_R(3, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RES__3_$HL:

					cycles += this->RES__n_$HL(3);
					break;
				case cpu::PREFIXED_OPCODE::RES__3_A:

					cycles += this->RES__n_R(3, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RES__4_B:

					cycles += this->RES__n_R(4, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RES__4_C:

					cycles += this->RES__n_R(4, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RES__4_D:

					cycles += this->RES__n_R(4, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RES__4_E:

					cycles += this->RES__n_R(4, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RES__4_H:

					cycles += this->RES__n_R(4, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RES__4_L:

					cycles += this->RES__n_R(4, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RES__4_$HL:

					cycles += this->RES__n_$HL(4);
					break;
				case cpu::PREFIXED_OPCODE::RES__4_A:

					cycles += this->RES__n_R(4, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RES__5_B:

					cycles += this->RES__n_R(5, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RES__5_C:

					cycles += this->RES__n_R(5, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RES__5_D:

					cycles += this->RES__n_R(5, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RES__5_E:

					cycles += this->RES__n_R(5, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RES__5_H:

					cycles += this->RES__n_R(5, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RES__5_L:

					cycles += this->RES__n_R(5, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RES__5_$HL:

					cycles += this->RES__n_$HL(5);
					break;
				case cpu::PREFIXED_OPCODE::RES__5_A:

					cycles += this->RES__n_R(5, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RES__6_B:

					cycles += this->RES__n_R(6, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RES__6_C:

					cycles += this->RES__n_R(6, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RES__6_D:

					cycles += this->RES__n_R(6, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RES__6_E:

					cycles += this->RES__n_R(6, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RES__6_H:

					cycles += this->RES__n_R(6, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RES__6_L:

					cycles += this->RES__n_R(6, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RES__6_$HL:

					cycles += this->RES__n_$HL(6);
					break;
				case cpu::PREFIXED_OPCODE::RES__6_A:

					cycles += this->RES__n_R(6, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::RES__7_B:

					cycles += this->RES__n_R(7, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::RES__7_C:

					cycles += this->RES__n_R(7, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::RES__7_D:

					cycles += this->RES__n_R(7, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::RES__7_E:

					cycles += this->RES__n_R(7, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::RES__7_H:

					cycles += this->RES__n_R(7, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::RES__7_L:

					cycles += this->RES__n_R(7, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::RES__7_$HL:

					cycles += this->RES__n_$HL(7);
					break;
				case cpu::PREFIXED_OPCODE::RES__7_A:

					cycles += this->RES__n_R(7, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SET__0_B:

					cycles += this->SET__n_R(0, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SET__0_C:

					cycles += this->SET__n_R(0, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SET__0_D:

					cycles += this->SET__n_R(0, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SET__0_E:

					cycles += this->SET__n_R(0, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SET__0_H:

					cycles += this->SET__n_R(0, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SET__0_L:

					cycles += this->SET__n_R(0, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SET__0_$HL:

					cycles += this->SET__n_$HL(0);
					break;
				case cpu::PREFIXED_OPCODE::SET__0_A:

					cycles += this->SET__n_R(0, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SET__1_B:

					cycles += this->SET__n_R(1, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SET__1_C:

					cycles += this->SET__n_R(1, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SET__1_D:

					cycles += this->SET__n_R(1, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SET__1_E:

					cycles += this->SET__n_R(1, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SET__1_H:

					cycles += this->SET__n_R(1, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SET__1_L:

					cycles += this->SET__n_R(1, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SET__1_$HL:

					cycles += this->SET__n_$HL(1);
					break;
				case cpu::PREFIXED_OPCODE::SET__1_A:

					cycles += this->SET__n_R(1, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SET__2_B:

					cycles += this->SET__n_R(2, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SET__2_C:

					cycles += this->SET__n_R(2, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SET__2_D:

					cycles += this->SET__n_R(2, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SET__2_E:

					cycles += this->SET__n_R(2, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SET__2_H:

					cycles += this->SET__n_R(2, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SET__2_L:

					cycles += this->SET__n_R(2, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SET__2_$HL:

					cycles += this->SET__n_$HL(2);
					break;
				case cpu::PREFIXED_OPCODE::SET__2_A:

					cycles += this->SET__n_R(2, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SET__3_B:

					cycles += this->SET__n_R(3, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SET__3_C:

					cycles += this->SET__n_R(3, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SET__3_D:

					cycles += this->SET__n_R(3, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SET__3_E:

					cycles += this->SET__n_R(3, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SET__3_H:

					cycles += this->SET__n_R(3, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SET__3_L:

					cycles += this->SET__n_R(3, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SET__3_$HL:

					cycles += this->SET__n_$HL(3);
					break;
				case cpu::PREFIXED_OPCODE::SET__3_A:

					cycles += this->SET__n_R(3, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SET__4_B:

					cycles += this->SET__n_R(4, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SET__4_C:

					cycles += this->SET__n_R(4, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SET__4_D:

					cycles += this->SET__n_R(4, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SET__4_E:

					cycles += this->SET__n_R(4, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SET__4_H:

					cycles += this->SET__n_R(4, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SET__4_L:

					cycles += this->SET__n_R(4, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SET__4_$HL:

					cycles += this->SET__n_$HL(4);
					break;
				case cpu::PREFIXED_OPCODE::SET__4_A:

					cycles += this->SET__n_R(4, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SET__5_B:

					cycles += this->SET__n_R(5, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SET__5_C:

					cycles += this->SET__n_R(5, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SET__5_D:

					cycles += this->SET__n_R(5, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SET__5_E:

					cycles += this->SET__n_R(5, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SET__5_H:

					cycles += this->SET__n_R(5, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SET__5_L:

					cycles += this->SET__n_R(5, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SET__5_$HL:

					cycles += this->SET__n_$HL(5);
					break;
				case cpu::PREFIXED_OPCODE::SET__5_A:

					cycles += this->SET__n_R(5, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SET__6_B:

					cycles += this->SET__n_R(6, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SET__6_C:

					cycles += this->SET__n_R(6, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SET__6_D:

					cycles += this->SET__n_R(6, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SET__6_E:

					cycles += this->SET__n_R(6, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SET__6_H:

					cycles += this->SET__n_R(6, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SET__6_L:

					cycles += this->SET__n_R(6, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SET__6_$HL:

					cycles += this->SET__n_$HL(6);
					break;
				case cpu::PREFIXED_OPCODE::SET__6_A:

					cycles += this->SET__n_R(6, REGISTER::A);
					break;
				case cpu::PREFIXED_OPCODE::SET__7_B:

					cycles += this->SET__n_R(7, REGISTER::B);
					break;
				case cpu::PREFIXED_OPCODE::SET__7_C:

					cycles += this->SET__n_R(7, REGISTER::C);
					break;
				case cpu::PREFIXED_OPCODE::SET__7_D:

					cycles += this->SET__n_R(7, REGISTER::D);
					break;
				case cpu::PREFIXED_OPCODE::SET__7_E:

					cycles += this->SET__n_R(7, REGISTER::E);
					break;
				case cpu::PREFIXED_OPCODE::SET__7_H:

					cycles += this->SET__n_R(7, REGISTER::H);
					break;
				case cpu::PREFIXED_OPCODE::SET__7_L:

					cycles += this->SET__n_R(7, REGISTER::L);
					break;
				case cpu::PREFIXED_OPCODE::SET__7_$HL:

					cycles += this->SET__n_$HL(7);
					break;
				case cpu::PREFIXED_OPCODE::SET__7_A:

					cycles += this->SET__n_R(7, REGISTER::A);
					break;
				default:
					std::cerr << hex(4) << static_cast<int>(this->_registers.PC) << "\t" << "Unknown prefixed opcode: " << hex(2) << static_cast<int>(prefixed_opcode) << std::endl;
					break;
			}

			break;
		case cpu::OPCODE::CALL__Z_U16:

			cycles += this->CALL__CC_U16(FLAG_CONDITION::Z);
			break;
		case cpu::OPCODE::CALL__U16:

			cycles += this->CALL__U16();
			break;
		case cpu::OPCODE::ADC__A_U8:

			cycles += this->ADC__A_U8();
			break;
		case cpu::OPCODE::RST__08H:

			cycles += this->RST__nH(0x08);
			break;
		case cpu::OPCODE::RET__NC:

			cycles += this->RET__CC(FLAG_CONDITION::NC);
			break;
		case cpu::OPCODE::POP__DE:

			cycles += this->POP__RR(REGISTER::DE);
			break;
		case cpu::OPCODE::JP__NC_U16:

			cycles += this->JP__CC_U16(FLAG_CONDITION::NC);
			break;
		case cpu::OPCODE::CALL__NC_U16:

			cycles += this->CALL__CC_U16(FLAG_CONDITION::NC);
			break;
		case cpu::OPCODE::PUSH__DE:

			cycles += this->PUSH__RR(REGISTER::DE);
			break;
		case cpu::OPCODE::SUB__A_U8:

			cycles += this->SUB__A_U8();
			break;
		case cpu::OPCODE::RST__10H:

			cycles += this->RST__nH(0x10);
			break;
		case cpu::OPCODE::RET__C:

			cycles += this->RET__CC(FLAG_CONDITION::C);
			break;
		case cpu::OPCODE::RETI:

			cycles += this->RETI();
			break;
		case cpu::OPCODE::JP__C_U16:

			cycles += this->JP__CC_U16(FLAG_CONDITION::C);
			break;
		case cpu::OPCODE::CALL__C_U16:

			cycles += this->CALL__CC_U16(FLAG_CONDITION::C);
			break;
		case cpu::OPCODE::SBC__A_U8:

			cycles += this->SBC__A_U8();
			break;
		case cpu::OPCODE::RST__18H:

			cycles += this->RST__nH(0x18);
			break;
		case cpu::OPCODE::LDH__$U8_A:

			cycles += this->LDH__$U8_R(REGISTER::A);
			break;
		case cpu::OPCODE::POP__HL:

			cycles += this->POP__RR(REGISTER::HL);
			break;
		case cpu::OPCODE::LD__$C_A:

			cycles += this->LD__$R_R(REGISTER::C, REGISTER::A);
			break;
		case cpu::OPCODE::PUSH__HL:

			cycles += this->PUSH__RR(REGISTER::HL);
			break;
		case cpu::OPCODE::AND__A_U8:

			cycles += this->AND__A_U8();
			break;
		case cpu::OPCODE::RST__20H:

			cycles += this->RST__nH(0x20);
			break;
		case cpu::OPCODE::ADD__SP_S8:

			cycles += this->ADD__SP_S8();
			break;
		case cpu::OPCODE::JP__$HL:

			cycles += this->JP__$HL();
			break;
		case cpu::OPCODE::LD__$U16_A:

			cycles += this->LD__$U16_R(REGISTER::A);
			break;
		case cpu::OPCODE::XOR__A_U8:

			cycles += this->XOR__A_U8();
			break;
		case cpu::OPCODE::RST__28H:

			cycles += this->RST__nH(0x28);
			break;
		case cpu::OPCODE::LDH__A_$U8:

			cycles += this->LDH__R_$U8(REGISTER::A);
			break;
		case cpu::OPCODE::POP__AF:

			cycles += this->POP__RR(REGISTER::AF);
			break;
		case cpu::OPCODE::LD__A_$C:
			
			cycles += this->LD__R_$R(REGISTER::A, REGISTER::C);
			break;
		case cpu::OPCODE::DI:

			cycles += this->DI();
			break;
		case cpu::OPCODE::PUSH__AF:

			cycles += this->PUSH__RR(REGISTER::AF);
			break;
		case cpu::OPCODE::OR__A_U8:

			cycles += this->OR__A_U8();
			break;
		case cpu::OPCODE::RST__30H:

			cycles += this->RST__nH(0x30);
			break;
		case cpu::OPCODE::LDHL__SP_S8:

			cycles += this->LDHL__SP_S8();
			break;
		case cpu::OPCODE::LD__SP_HL:

			cycles += this->LD__RR_RR(REGISTER::SP, REGISTER::HL);
			break;
		case cpu::OPCODE::LD__A_$U16:

			cycles += this->LD__R_$U16(REGISTER::A);
			break;
		case cpu::OPCODE::EI:

			cycles += this->EI();
			break;
		case cpu::OPCODE::CP__A_U8:

			cycles += this->CP__A_U8();
			break;
		case cpu::OPCODE::RST__38H:

			cycles += this->RST__nH(0x38);
			break;
		default:
			std::cerr << hex(4) << static_cast<int>(this->_registers.PC) << "\t" << "Unknown opcode: " << hex(2) << static_cast<int>(opcode) << std::endl;
			throw std::invalid_argument("Unknown opcode.");
			break;
	}

	return cycles;
}

std::uint8_t cpu::handle_interrupts()
{
	std::uint8_t& IE = this->_bus->get_u8_memory_value(memory::$::IE);
	std::uint8_t& IF = this->_bus->get_u8_memory_value(memory::$::IF);

	std::uint8_t IE_IF = IE & IF;

	if (this->_ime && IE_IF > 0)
	{ 
		for (auto& i : cpu::INTERRUPTS)
		{
			if (this->get_bit(static_cast<std::uint8_t>(i), IE_IF))
			{
				//std::cout << ">> Handle interrupt " << hex(2) << (int)static_cast<std::uint8_t>(i) << std::endl;

				this->_PUSH__U16(this->_registers.PC);
				this->_registers.PC = cpu::INTERRUPT_VECTOR.at(i);

				this->reset_bit(static_cast<std::uint8_t>(i), IF);
			}
		}
	}

	//return 5*4;
	return 0;
}


template<typename T, std::uint8_t n>
bool cpu::carry(const std::function<T(T, T)> op, const T& arg1, const T& arg2)
{
	return (op(static_cast<T>(arg1) & ((1 << n) - 1), static_cast<T>(arg2) & ((1 << n) - 1)) & (1 << n)) == (1 << n);
}

cpu::carries cpu::addition_carries(const std::uint8_t& u8_1, const std::uint8_t& u8_2)
{
	bool H = carry<std::uint16_t, 4>(std::plus<>(), u8_1, u8_2);
	bool C = carry<std::uint16_t, 8>(std::plus<>(), u8_1, u8_2);

	return {H, C};
}

cpu::carries cpu::addition_carries(const std::uint16_t& u16_1, const std::uint16_t& u16_2)
{
	bool H = carry<std::uint32_t, 12>(std::plus<>(), u16_1, u16_2);
	bool C = carry<std::uint32_t, 16>(std::plus<>(), u16_1, u16_2);

	return {H, C};
}

cpu::carries cpu::subtraction_carries(const std::uint8_t& u8_1, const std::uint8_t& u8_2)
{
	bool H = carry<std::uint16_t, 4>(std::minus<>(), u8_1, u8_2);
	bool C = carry<std::uint16_t, 8>(std::minus<>(), u8_1, u8_2);

	return {H, C};
}

cpu::carries cpu::subtraction_carries(const std::uint16_t& u16_1, const std::uint16_t& u16_2)
{
	bool H = carry<std::uint32_t, 12>(std::minus<>(), u16_1, u16_2);
	bool C = carry<std::uint32_t, 16>(std::minus<>(), u16_1, u16_2);

	return {H, C};
}


bool cpu::get_bit(const std::uint8_t& n, const std::uint8_t& u8)
{
	return (u8 & (0b1 << n)) > 0;
}

void cpu::set_bit(const std::uint8_t& n, std::uint8_t& u8)
{
	u8 |= (0b1 << n);
}

void cpu::reset_bit(const std::uint8_t& n, std::uint8_t& u8)
{
	u8 &= ~(0b1 << n);
}

void cpu::set_flag(const cpu::FLAG& f)
{
	cpu::set_bit(static_cast<std::uint8_t>(f), this->_registers.F);
}

void cpu::reset_flag(const cpu::FLAG& f)
{
	cpu::reset_bit(static_cast<std::uint8_t>(f), this->_registers.F);
}

bool cpu::get_flag(const cpu::FLAG& f)
{
	//return static_cast<std::uint8_t>((this->_registers.F & (0b1 << static_cast<std::uint8_t>(f))) > 0);
	return cpu::get_bit(static_cast<std::uint8_t>(f), this->_registers.F);
}

std::variant<std::uint8_t*,std::uint16_t*> cpu::register_ptr(const cpu::REGISTER& R)
{
	std::variant<std::uint8_t*,std::uint16_t*> u_ptr;

	switch (R)
	{
		case cpu::REGISTER::A:
			u_ptr = &this->_registers.A;
			break;
		case cpu::REGISTER::B:
			u_ptr = &this->_registers.B;
			break;
		case cpu::REGISTER::C:
			u_ptr = &this->_registers.C;
			break;
		case cpu::REGISTER::D:
			u_ptr = &this->_registers.D;
			break;
		case cpu::REGISTER::E:
			u_ptr = &this->_registers.E;
			break;
		case cpu::REGISTER::F:
			u_ptr = &this->_registers.F;
			break;
		case cpu::REGISTER::H:
			u_ptr = &this->_registers.H;
			break;
		case cpu::REGISTER::L:
			u_ptr = &this->_registers.L;
			break;
		case cpu::REGISTER::AF:
			u_ptr = &this->_registers.AF;
			break;
		case cpu::REGISTER::BC:
			u_ptr = &this->_registers.BC;
			break;
		case cpu::REGISTER::DE:
			u_ptr = &this->_registers.DE;
			break;
		case cpu::REGISTER::HL:
			u_ptr = &this->_registers.HL;
			break;
		case cpu::REGISTER::PC:
			u_ptr = &this->_registers.PC;
			break;
		case cpu::REGISTER::SP:
			u_ptr = &this->_registers.SP;
			break;
	}

	return u_ptr;
}

void cpu::_ADD__A_U8(const std::uint8_t& u8)
{
	std::uint8_t A = this->_registers.A;

	cpu::carries _carries = this->addition_carries(A, u8);
	this->_registers.A += u8;

	this->_registers.A == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	_carries.H ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	_carries.C ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::ADD__A_U8()
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;

	this->_ADD__A_U8(U8);

	this->print_argument(U8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::ADD__A_U8);
}

const std::uint8_t& cpu::ADD__A_R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_ADD__A_U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::ADD__A_R);
}

const std::uint8_t& cpu::ADD__A_$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_ADD__A_U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::ADD__A_$HL);
}

void cpu::_ADD__HL_U16(const std::uint16_t& u16)
{
	std::uint16_t HL = this->_registers.HL;

	cpu::carries _carries = this->addition_carries(HL, u16);
	this->_registers.HL += u16;

	this->reset_flag(cpu::FLAG::N);
	_carries.H ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	_carries.C ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::ADD__HL_RR(const REGISTER& rr)
{
	this->_registers.PC += 1;
	std::uint16_t& RR = *std::get<std::uint16_t*>(this->register_ptr(rr));
	
	this->_ADD__HL_U16(RR);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::ADD__HL_RR);
}

void cpu::_ADD__SP_S8(const std::int8_t& s8)
{
	std::uint16_t SP = this->_registers.SP;

	cpu::carries _carries = this->addition_carries(static_cast<std::uint8_t>(this->_registers.SP), static_cast<std::uint8_t>(s8));
	this->_registers.SP += s8;

	this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	_carries.H ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	_carries.C ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::ADD__SP_S8()
{
	std::int8_t& S8 = *reinterpret_cast<std::int8_t*>(&this->_bus->get_u8_memory_value(this->_registers.PC + 1));
	this->_registers.PC += 2;

	this->_ADD__SP_S8(S8);

	this->print_argument(S8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::ADD__SP_S8);
}

void cpu::_ADC__A_U8(const std::uint8_t& u8)
{
	std::uint8_t A = this->_registers.A;

	cpu::carries _carries_1 = this->addition_carries(A, u8);
	cpu::carries _carries_2 = this->addition_carries(A + u8, static_cast<std::uint8_t>(this->get_flag(cpu::FLAG::C)));
	this->_registers.A += u8 + this->get_flag(cpu::FLAG::C);

	this->_registers.A == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	(_carries_1.H | _carries_2.H) ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	(_carries_1.C | _carries_2.C) ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::ADC__A_U8()
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;

	this->_ADC__A_U8(U8);

	this->print_argument(U8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::ADC__A_U8);
}

const std::uint8_t& cpu::ADC__A_R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_ADC__A_U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::ADC__A_R);
}

const std::uint8_t& cpu::ADC__A_$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_ADC__A_U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::ADC__A_$HL);
}

void cpu::_SUB__A_U8(const std::uint8_t& u8)
{
	std::uint8_t A = this->_registers.A;

	cpu::carries _carries = this->subtraction_carries(A, u8);
	this->_registers.A -= u8;

	this->_registers.A == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->set_flag(cpu::FLAG::N);
	_carries.H ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	_carries.C ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::SUB__A_U8()
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;

	this->_SUB__A_U8(U8);

	this->print_argument(U8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SUB__A_U8);
}

const std::uint8_t& cpu::SUB__A_R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_SUB__A_U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SUB__A_R);
}

const std::uint8_t& cpu::SUB__A_$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_SUB__A_U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SUB__A_$HL);
}

void cpu::_SBC__A_U8(const std::uint8_t& u8)
{
	std::uint8_t A = this->_registers.A;

	cpu::carries _carries_1 = this->subtraction_carries(A, u8);
	cpu::carries _carries_2 = this->subtraction_carries(A - u8, static_cast<std::uint8_t>(this->get_flag(cpu::FLAG::C)));
	this->_registers.A -= u8 + this->get_flag(cpu::FLAG::C);

	this->_registers.A == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->set_flag(cpu::FLAG::N);
	(_carries_1.H | _carries_2.H) ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	(_carries_1.C | _carries_2.C) ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::SBC__A_U8()
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;

	this->_SBC__A_U8(U8);

	this->print_argument(U8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SBC__A_U8);
}

const std::uint8_t& cpu::SBC__A_R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_SBC__A_U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SBC__A_R);
}

const std::uint8_t& cpu::SBC__A_$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_SBC__A_U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SBC__A_$HL);
}

void cpu::_AND__A_U8(const std::uint8_t& u8)
{
	this->_registers.A &= u8;

	this->_registers.A == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->set_flag(cpu::FLAG::H);
	this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::AND__A_U8()
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;

	this->_AND__A_U8(U8);

	this->print_argument(U8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::AND__A_U8);
}

const std::uint8_t& cpu::AND__A_R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_AND__A_U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::AND__A_R);
}

const std::uint8_t& cpu::AND__A_$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_AND__A_U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::AND__A_$HL);
}

void cpu::_OR__A_U8(const std::uint8_t& u8)
{
	this->_registers.A |= u8;

	this->_registers.A == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::OR__A_U8()
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;

	this->_OR__A_U8(U8);

	this->print_argument(U8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::OR__A_U8);
}

const std::uint8_t& cpu::OR__A_R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_OR__A_U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::OR__A_R);
}

const std::uint8_t& cpu::OR__A_$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_OR__A_U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::OR__A_$HL);
}

void cpu::_XOR__A_U8(const std::uint8_t& u8)
{
	this->_registers.A ^= u8;

	this->_registers.A == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::XOR__A_U8()
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;

	this->_XOR__A_U8(U8);

	this->print_argument(U8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::XOR__A_U8);
}

const std::uint8_t& cpu::XOR__A_R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_XOR__A_U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::XOR__A_R);
}

const std::uint8_t& cpu::XOR__A_$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_XOR__A_U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::XOR__A_$HL);
}

const std::uint8_t& cpu::PREFIX_CB()
{
	this->_registers.PC += 1;

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::PREFIX__CB);
}

void cpu::_BIT__n_U8(const std::uint8_t& n, const std::uint8_t& u8)
{
	(u8 & (0b1 << n)) == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->set_flag(cpu::FLAG::H);
}

const std::uint8_t& cpu::BIT__n_R(const std::uint8_t& n, const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_BIT__n_U8(n, R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::BIT__n_R);
}

const std::uint8_t& cpu::BIT__n_$HL(const std::uint8_t& n)
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_BIT__n_U8(n, $HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::BIT__n_$HL);
}

void cpu::_RES__n_U8(const std::uint8_t& n, std::uint8_t& u8)
{
	cpu::reset_bit(n, u8);
}

const std::uint8_t& cpu::RES__n_R(const std::uint8_t& n, const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_RES__n_U8(n, R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RES__n_R);
}

const std::uint8_t& cpu::RES__n_$HL(const std::uint8_t& n)
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_RES__n_U8(n, $HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RES__n_$HL);
}

void cpu::_SET__n_U8(const std::uint8_t& n, std::uint8_t& u8)
{
	cpu::set_bit(n, u8);
}

const std::uint8_t& cpu::SET__n_R(const std::uint8_t& n, const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_SET__n_U8(n, R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SET__n_R);
}

const std::uint8_t& cpu::SET__n_$HL(const std::uint8_t& n)
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);
	
	this->_SET__n_U8(n, $HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SET__n_$HL);
}

void cpu::_CP__A_U8(const std::uint8_t& u8)
{
	std::uint8_t A = this->_registers.A;

	cpu::carries _carries = this->subtraction_carries(A, u8);

	A - u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->set_flag(cpu::FLAG::N);
	_carries.H ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	_carries.C ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::CP__A_U8()
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;

	this->_CP__A_U8(U8);

	this->print_argument(U8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::CP__A_U8);
}

const std::uint8_t& cpu::CP__A_R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_CP__A_U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::CP__A_R);
}

const std::uint8_t& cpu::CP__A_$HL(void)
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_CP__A_U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::CP__A_$HL);
}

void cpu::_DEC__U16(std::uint16_t& u16)
{
	std::uint16_t _u16 = u16;
	u16 -= 1;
}

void cpu::_DEC__U8(std::uint8_t& u8)
{
	std::uint8_t _u8 = u8;
	u8 -= 1;

	cpu::carries _carries = this->subtraction_carries(_u8, 1);

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->set_flag(cpu::FLAG::N);
	_carries.H ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	//_carries.C ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::DEC__RR(const REGISTER& rr)
{
	this->_registers.PC += 1;
	std::uint16_t& RR = *std::get<std::uint16_t*>(this->register_ptr(rr));

	this->_DEC__U16(RR);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::DEC__RR);
}

const std::uint8_t& cpu::DEC__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));

	this->_DEC__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::DEC__R);
}

const std::uint8_t& cpu::DEC__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_DEC__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::DEC__$HL);
}

void cpu::_INC__U16(std::uint16_t& u16)
{
	std::uint16_t _u16 = u16;
	u16 += 1;
}

void cpu::_INC__U8(std::uint8_t& u8)
{
	std::uint8_t _u8 = u8;
	u8 += 1;

	cpu::carries _carries = this->addition_carries(_u8, 1);

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	_carries.H ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	//_carries.C ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::INC__RR(const REGISTER& rr)
{
	this->_registers.PC += 1;
	std::uint16_t& RR = *std::get<std::uint16_t*>(this->register_ptr(rr));

	this->_INC__U16(RR);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::INC__RR);
}

const std::uint8_t& cpu::INC__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));

	this->_INC__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::INC__R);
}

const std::uint8_t& cpu::INC__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_INC__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::INC__$HL);
}

const std::uint8_t& cpu::HALT()
{
	std::uint8_t& IE = this->_bus->get_u8_memory_value(memory::$::IE);
	std::uint8_t& IF = this->_bus->get_u8_memory_value(memory::$::IF);

	std::uint8_t IE_IF = IE & IF;

	if (this->_halted && IE_IF > 0)
	{
		this->_registers.PC += 1;

		this->_halted = false;
	}
	else
	{
		this->_halted = true;
	}

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::HALT);
}

void cpu::_LD__U8_U8(std::uint8_t& u8_1, const std::uint8_t& u8_2)
{
	u8_1 = u8_2;
}

const std::uint8_t& cpu::LD__R_U8(const REGISTER& r)
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_LD__U8_U8(R, U8);

	this->print_argument(U8);
	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__R_U8);
}

const std::uint8_t& cpu::LD__R_R(const REGISTER& r_1, const REGISTER& r_2)
{
	this->_registers.PC += 1;
	std::uint8_t& R_1 = *std::get<std::uint8_t*>(this->register_ptr(r_1));
	std::uint8_t& R_2 = *std::get<std::uint8_t*>(this->register_ptr(r_2));
	
	this->_LD__U8_U8(R_1, R_2);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__R_R);
}

const std::uint8_t& cpu::LD__R_$RR(const REGISTER& r, const REGISTER& rr)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	std::uint8_t& $RR = this->_bus->get_u8_memory_value(*std::get<std::uint16_t*>(this->register_ptr(rr)));

	this->_LD__U8_U8(R, $RR);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__R_$RR);
}

const std::uint8_t& cpu::LD__$RR_U8(const REGISTER& rr)
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;
	std::uint8_t& $RR = this->_bus->get_u8_memory_value(*std::get<std::uint16_t*>(this->register_ptr(rr)));

	this->_LD__U8_U8($RR, U8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__$RR_U8);
}

const std::uint8_t& cpu::LD__$RR_R(const REGISTER& rr, const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& $RR = this->_bus->get_u8_memory_value(*std::get<std::uint16_t*>(this->register_ptr(rr)));
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_LD__U8_U8($RR, R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__$RR_R);
}

const std::uint8_t& cpu::LDD__$HL_R(const REGISTER& r)
{
	this->LD__$RR_R(REGISTER::HL, r);
	this->_registers.HL--;

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LDD__$HL_R);
}

const std::uint8_t& cpu::LDD__R_$HL(const REGISTER& r)
{
	this->LD__R_$RR(r, REGISTER::HL);
	this->_registers.HL--;

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LDD__R_$HL);
}

const std::uint8_t& cpu::LDI__$HL_R(const REGISTER& r)
{
	this->LD__$RR_R(REGISTER::HL, r);
	this->_registers.HL++;

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LDI__$HL_R);
}

const std::uint8_t& cpu::LDI__R_$HL(const REGISTER& r)
{
	this->LD__R_$RR(r, REGISTER::HL);
	this->_registers.HL++;

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LDI__R_$HL);
}

void cpu::_LD__U16_U16(std::uint16_t& u16_1, const std::uint16_t& u16_2)
{
	u16_1 = u16_2;
}
 
const std::uint8_t& cpu::LD__RR_U16(const REGISTER& rr)
{
	std::uint16_t& U16 = this->_bus->get_u16_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 3;
	std::uint16_t& RR = *std::get<std::uint16_t*>(this->register_ptr(rr));
	
	this->_LD__U16_U16(RR, U16);

	this->print_argument(U16);
	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__RR_U16);
}

const std::uint8_t& cpu::LD__RR_RR(const REGISTER& rr_1, const REGISTER& rr_2)
{
	this->_registers.PC += 1;
	std::uint16_t& RR_1 = *std::get<std::uint16_t*>(this->register_ptr(rr_1));
	std::uint16_t& RR_2 = *std::get<std::uint16_t*>(this->register_ptr(rr_2));
	
	this->_LD__U16_U16(RR_1, RR_2);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__RR_RR);
}

const std::uint8_t& cpu::LD__$U16_RR(const REGISTER& rr)
{
	std::uint16_t& U16 = this->_bus->get_u16_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 3;
	std::uint16_t& $U16 = this->_bus->get_u16_memory_value(U16);
	std::uint16_t& RR = *std::get<std::uint16_t*>(this->register_ptr(rr));
	
	this->_LD__U16_U16($U16, RR);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__$U16_RR);
}

const std::uint8_t& cpu::LD__$U16_R(const REGISTER& r)
{
	std::uint16_t& U16 = this->_bus->get_u16_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 3;
	std::uint8_t& $U16 = this->_bus->get_u8_memory_value(U16);
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_LD__U8_U8($U16, R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__$U16_R);
}

const std::uint8_t& cpu::LD__R_$U16(const REGISTER& r)
{
	std::uint16_t& U16 = this->_bus->get_u16_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 3;
	std::uint8_t& $U16 = this->_bus->get_u8_memory_value(U16);
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_LD__U8_U8(R, $U16);

	this->print_argument(U16);
	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__R_$U16);
}

const std::uint8_t& cpu::LD__$R_R(const REGISTER& r_1, const REGISTER& r_2)
{
	this->_registers.PC += 1;
	std::uint8_t& $R = this->_bus->get_u8_memory_value(0xFF00 + *std::get<std::uint8_t*>(this->register_ptr(r_1)));
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r_2));

	this->_LD__U8_U8($R, R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__$R_R);
}

const std::uint8_t& cpu::LD__R_$R(const REGISTER& r_1, const REGISTER& r_2)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r_1));
	std::uint8_t& $R = this->_bus->get_u8_memory_value(0xFF00 + *std::get<std::uint8_t*>(this->register_ptr(r_2)));

	this->_LD__U8_U8(R, $R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LD__R_$R);
}

const std::uint8_t& cpu::LDH__$U8_R(const REGISTER& r)
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;
	std::uint8_t& $U8 = this->_bus->get_u8_memory_value(0xFF00 + U8);
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_LD__U8_U8($U8, R);

	this->print_argument(U8);
	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LDH__$U8_R);
}

const std::uint8_t& cpu::LDH__R_$U8(const REGISTER& r)
{
	std::uint8_t& U8 = this->_bus->get_u8_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 2;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	std::uint8_t& $U8 = this->_bus->get_u8_memory_value(0xFF00 + U8);
	
	this->_LD__U8_U8(R, $U8);

	this->print_argument(U8);
	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LDH__R_$U8);
}

void cpu::_LDHL__SP_S8(const std::int8_t& s8)
{
	cpu::carries _carries = this->addition_carries(static_cast<std::uint8_t>(this->_registers.SP), static_cast<std::uint8_t>(s8));
	this->_registers.HL = this->_registers.SP + s8;

	this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	_carries.H ? this->set_flag(cpu::FLAG::H) : this->reset_flag(cpu::FLAG::H);
	_carries.C ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::LDHL__SP_S8()
{
	std::int8_t& S8 = *reinterpret_cast<std::int8_t*>(&this->_bus->get_u8_memory_value(this->_registers.PC + 1));
	this->_registers.PC += 2;

	this->_LDHL__SP_S8(S8);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::LDHL__SP_S8);
}


const std::uint8_t& cpu::NOP()
{
	this->_registers.PC += 1;

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::NOP);
}

void cpu::_PUSH__U16(const std::uint16_t& u16)
{
	this->_registers.SP -= 2;
	this->_bus->get_u16_memory_value(this->_registers.SP) = u16;
}

const std::uint8_t& cpu::PUSH__RR(const REGISTER& rr)
{
	this->_registers.PC += 1;
	std::uint16_t& RR = *std::get<std::uint16_t*>(this->register_ptr(rr));

	this->_PUSH__U16(RR);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::PUSH__RR);
}

void cpu::_POP__U16(std::uint16_t& u16)
{
	u16 = this->_bus->get_u16_memory_value(this->_registers.SP);
	this->_registers.SP += 2;
}

const std::uint8_t& cpu::POP__RR(const REGISTER& rr)
{
	this->_registers.PC += 1;
	std::uint16_t& RR = *std::get<std::uint16_t*>(this->register_ptr(rr));

	this->_POP__U16(RR);

	if(rr == REGISTER::AF)
	{
		this->_registers.F &= 0xF0;
	}

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::POP__RR);
}

const std::uint8_t& cpu::RST__nH(const std::uint8_t& n)
{
	this->_registers.PC += 1;

	this->_CALL__U16(0x0000 + n);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RST__nH);
}

void cpu::_RL__U8(std::uint8_t& u8)
{
	bool cy = this->get_bit(7, u8);
	u8 = u8 << 1 | this->get_flag(cpu::FLAG::C);

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	cy ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::RL__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_RL__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RL__R);
}

const std::uint8_t& cpu::RL__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_RL__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RL__$HL);
}

void cpu::_RLC__U8(std::uint8_t& u8)
{
	bool cy = this->get_bit(7, u8);
	u8 = std::rotl(u8, 1);

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	cy ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::RLC__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_RLC__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RLC__R);
}

const std::uint8_t& cpu::RLC__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_RLC__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RLC__$HL);
}

void cpu::_RR__U8(std::uint8_t& u8)
{
	bool cy = this->get_bit(0, u8);
	u8 = u8 >> 1 | (this->get_flag(cpu::FLAG::C) << 7);

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	cy ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::RR__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_RR__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RR__R);
}

const std::uint8_t& cpu::RR__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_RR__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RR__$HL);
}

void cpu::_RRC__U8(std::uint8_t& u8)
{
	bool cy = this->get_bit(0, u8);
	u8 = std::rotr(u8, 1);

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	cy ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::RRC__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_RRC__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RRC__R);
}

const std::uint8_t& cpu::RRC__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_RRC__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RRC__$HL);
}

const std::uint8_t& cpu::RLA()
{
	this->RL__R(REGISTER::A);
	this->reset_flag(FLAG::Z);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RLA);
}

const std::uint8_t& cpu::RLCA()
{
	this->RLC__R(REGISTER::A);
	this->reset_flag(FLAG::Z);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RLCA);
}

const std::uint8_t& cpu::RRA()
{
	this->RR__R(REGISTER::A);
	this->reset_flag(FLAG::Z);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RRA);
}

const std::uint8_t& cpu::RRCA()
{
	this->RRC__R(REGISTER::A);
	this->reset_flag(FLAG::Z);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RRCA);
}

void cpu::_SLA__U8(std::uint8_t& u8)
{
	bool cy = this->get_bit(7, u8);
	u8 = u8 << 1;

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	cy ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::SLA__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_SLA__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SLA__R);
}

const std::uint8_t& cpu::SLA__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_SLA__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SLA__$HL);
}

void cpu::_SRA__U8(std::uint8_t& u8)
{
	bool cy = this->get_bit(0, u8);
	u8 = (u8 >> 1) | (u8 & (0b1 << 7));

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	cy ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::SRA__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_SRA__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SRA__R);
}

const std::uint8_t& cpu::SRA__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_SRA__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SRA__$HL);
}

void cpu::_SRL__U8(std::uint8_t& u8)
{
	bool cy = this->get_bit(0, u8);
	u8 = u8 >> 1;

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	cy ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::SRL__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_SRL__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SRL__R);
}

const std::uint8_t& cpu::SRL__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_SRL__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SRL__$HL);
}

void cpu::_SWAP__U8(std::uint8_t& u8)
{
	u8 = std::rotl(u8, 4);

	u8 == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::N);
	this->reset_flag(cpu::FLAG::H);
	this->reset_flag(cpu::FLAG::C);
}

const std::uint8_t& cpu::SWAP__R(const REGISTER& r)
{
	this->_registers.PC += 1;
	std::uint8_t& R = *std::get<std::uint8_t*>(this->register_ptr(r));
	
	this->_SWAP__U8(R);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SWAP__R);
}

const std::uint8_t& cpu::SWAP__$HL()
{
	this->_registers.PC += 1;
	std::uint8_t& $HL = this->_bus->get_u8_memory_value(this->_registers.HL);

	this->_SWAP__U8($HL);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SWAP__$HL);
}

bool cpu::test_flag_condition(const FLAG_CONDITION& cc)
{
	switch (cc)
	{
		case FLAG_CONDITION::NZ:
			return !this->get_flag(FLAG::Z);
			break;
		case FLAG_CONDITION::Z:
			return this->get_flag(FLAG::Z);
			break;
		case FLAG_CONDITION::NC:
			return !this->get_flag(FLAG::C);
			break;
		case FLAG_CONDITION::C:
			return this->get_flag(FLAG::C);
			break;
	}
}

void cpu::_JP__U16(const std::uint16_t& u16)
{
	this->_registers.PC = u16;
}

const std::uint8_t& cpu::JP__U16()
{
	std::uint16_t& U16 = this->_bus->get_u16_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 3;

	this->_JP__U16(U16);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::JP__U16);
}

const std::uint8_t& cpu::JP__CC_U16(const FLAG_CONDITION& cc)
{
	std::uint16_t& U16 = this->_bus->get_u16_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 3;

	if (this->test_flag_condition(cc))
	{
		this->_JP__U16(U16);

		return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::JP__CC_U16_b);
	}

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::JP__CC_U16_nb);
}

const std::uint8_t& cpu::JP__$HL()
{
	this->_registers.PC += 1;

	this->_JP__U16(this->_registers.HL);
	// Note: In contrast to what the notation suggests, this is really just a jump to HL and not to the memory at HL.

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::JP__$HL);
}

void cpu::_JR__S8(const std::int8_t& s8)
{
	this->_registers.PC += s8;
}

const std::uint8_t& cpu::JR__S8()
{
	std::int8_t& S8 = *reinterpret_cast<std::int8_t*>(&this->_bus->get_u8_memory_value(this->_registers.PC + 1));
	this->_registers.PC += 2;

	this->_JR__S8(S8);

	this->print_argument(S8);
	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::JR__S8);
}

const std::uint8_t& cpu::JR__CC_S8(const FLAG_CONDITION& cc)
{
	std::int8_t& S8 = *reinterpret_cast<std::int8_t*>(&this->_bus->get_u8_memory_value(this->_registers.PC + 1));
	this->_registers.PC += 2;

	if (this->test_flag_condition(cc))
	{
		this->_JR__S8(S8);

		return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::JR__CC_S8_b);
	}

	this->print_argument(S8);
	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::JR__CC_S8_nb);
}

void cpu::_CALL__U16(const std::uint16_t& u16)
{
	this->_registers.SP -= 2;
	this->_bus->get_u16_memory_value(this->_registers.SP) = this->_registers.PC;
	this->_registers.PC = u16;
}

const std::uint8_t& cpu::CALL__U16()
{
	std::uint16_t& U16 = this->_bus->get_u16_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 3;

	this->_CALL__U16(U16);

	this->print_argument(U16);
	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::CALL__U16);
}

const std::uint8_t& cpu::CALL__CC_U16(const FLAG_CONDITION& cc)
{
	std::uint16_t& U16 = this->_bus->get_u16_memory_value(this->_registers.PC + 1);
	this->_registers.PC += 3;

	if (this->test_flag_condition(cc))
	{
		this->_CALL__U16(U16);

		return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::CALL__CC_U16_b);
	}

	this->print_argument(U16);
	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::CALL__CC_U16_nb);
}

void cpu::_RET()
{
	std::uint16_t& u16 = this->_bus->get_u16_memory_value(this->_registers.SP);
	this->_registers.SP += 2;
	this->_registers.PC = u16;
}

const std::uint8_t& cpu::RET()
{
	this->_registers.PC += 1;

	this->_RET();

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RET);
}

const std::uint8_t& cpu::RET__CC(const FLAG_CONDITION& cc)
{
	this->_registers.PC += 1;

	if (this->test_flag_condition(cc))
	{
		this->_RET();

		return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RET__CC_b);
	}

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RET__CC_nb);
}

const std::uint8_t& cpu::RETI()
{
	this->_registers.PC += 1;

	this->EI();
	this->_RET();

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::RETI);
}

bool cpu::interrupt_enabled(const INTERRUPT& i)
{
	return static_cast<std::uint8_t>((this->_bus->_memory.IE() & (0b1 << static_cast<std::uint8_t>(i))) > 0);
}

bool cpu::interrupt_requested(const INTERRUPT& i)
{
	return static_cast<std::uint8_t>((this->_bus->_memory.IF() & (0b1 << static_cast<std::uint8_t>(i))) > 0);
}

void cpu::IME(const bool& b)
{
	//std::uint8_t& IE = this->_bus->_memory.IE();
	//for (auto& i : cpu::INTERRUPTS)
	//{
	//	b ? this->set_bit(static_cast<std::uint8_t>(i), IE) : this->reset_bit(static_cast<std::uint8_t>(i), IE);
	//}

	this->_ime = b;
}

const std::uint8_t& cpu::DI()
{
	this->_registers.PC += 1;

	this->IME(false);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::DI);
}

const std::uint8_t& cpu::EI()
{
	this->_registers.PC += 1;

	this->IME(true);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::EI);
}

const std::uint8_t& cpu::DAA()
{
	this->_registers.PC += 1;

	//bool C = (this->_registers.A / 10 > 9);
	//this->_registers.A = (((this->_registers.A / 10) & 0x0F) << 4) + (this->_registers.A % 10);
	
	std::uint8_t& A = this->_registers.A; // 0x9A
	std::uint8_t _A = 0x00;

	bool C = false;

	if (this->get_flag(cpu::FLAG::H) || (!this->get_flag(cpu::FLAG::N) && ((A & 0x0F) > 0x09)))
	{
		_A += 0x06;
	}

	if (this->get_flag(cpu::FLAG::C) || (!this->get_flag(cpu::FLAG::N) && ((A & 0xFF) > 0x99)))
	{
		_A += 0x60;
		C = true;
	}

	A += this->get_flag(cpu::FLAG::N) ? -_A : _A;

	this->_registers.A == 0 ? this->set_flag(cpu::FLAG::Z) : this->reset_flag(cpu::FLAG::Z);
	this->reset_flag(cpu::FLAG::H);
	C ? this->set_flag(cpu::FLAG::C) : this->reset_flag(cpu::FLAG::C);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::DAA);
}

const std::uint8_t& cpu::CPL()
{
	this->_registers.PC += 1;

	this->_registers.A ^= 0xFF;

	this->set_flag(FLAG::N);
	this->set_flag(FLAG::H);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::CPL);
}

const std::uint8_t& cpu::CCF()
{
	this->_registers.PC += 1;

	this->reset_flag(FLAG::N);
	this->reset_flag(FLAG::H);
	this->get_flag(FLAG::C) ? this->reset_flag(FLAG::C) : this->set_flag(FLAG::C);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::CCF);
}

const std::uint8_t& cpu::SCF()
{
	this->_registers.PC += 1;

	this->reset_flag(FLAG::N);
	this->reset_flag(FLAG::H);
	this->set_flag(FLAG::C);

	return cpu::TEMPLATED_OPCODE_CYCLES.at(cpu::TEMPLATED_OPCODE::SCF);
}


void cpu::print_opcode(const cpu::OPCODE& opcode, const std::uint16_t& pc)
{
	std::cout << hex(4) << static_cast<int>(pc) << "   ────  " << " " << hex(2) << static_cast<int>(opcode) << ": " << cpu::OPCODE_MNEMONIC.at(opcode) << std::endl;
}

void cpu::print_opcode(const cpu::PREFIXED_OPCODE& prefixed_opcode, const std::uint16_t& pc)
{
	std::cout << "    " << "   ────  " << "*" << hex(2) << static_cast<int>(prefixed_opcode) << ": " << cpu::PREFIXED_OPCODE_MNEMONIC.at(prefixed_opcode) << std::endl;
}

void cpu::print_argument(const std::uint8_t& u8)
{
	if (this->_bus->CPU_OPS)
	{
		std::cout << "                                " << hex(2) << static_cast<int>(u8) << std::endl;
	}
}

void cpu::print_argument(const std::uint16_t& u16)
{
	if (this->_bus->CPU_OPS)
	{
		std::cout << "                              " << hex(4) << static_cast<int>(u16) << std::endl;
	}
}

void cpu::print_argument(const std::int8_t& s8)
{
	if (this->_bus->CPU_OPS)
	{
		if (s8 >= 0)
		{
			std::cerr << "                               +" << hex(2) << static_cast<int>(s8) << std::endl;
		}
		else
		{
			std::cerr << "                               -" << hex(2) << static_cast<int>(-s8) << std::endl;
		}
	}
}

void cpu::registers::print(void) const
{
	std::cout << " ┌───────┬───────┬───────┬───────╥──────────┐" << std::endl;
	std::cout << " │ A: " << hex(2) << static_cast<int>(this->A) << " │ B: " << hex(2) << static_cast<int>(this->B) << " │ D: " << hex(2) << static_cast<int>(this->D) << " │ H: " << hex(2) << static_cast<int>(this->H) << " ║ SP: " << hex(4) << static_cast<int>(this->SP) << " │" << std::endl;
	std::cout << " ├───────┼───────┼───────┼───────╫──────────┤" << std::endl;
	std::cout << " │ F: " << hex(2) << static_cast<int>(this->F) << " │ C: " << hex(2) << static_cast<int>(this->C) << " │ E: " << hex(2) << static_cast<int>(this->E) << " │ L: " << hex(2) << static_cast<int>(this->L) << " ║ PC: " << hex(4) << static_cast<int>(this->PC) << " │" << std::endl;
	std::cout << " └───────┴───────┴───────┴───────╨──────────┘" << std::endl;
}

void cpu::run(void)
{
	while (true)
	{
		this->next();
	}
}

const std::uint16_t& cpu::PC(void)
{
	return this->_registers.PC;
}

std::uint8_t cpu::next(void)
{
	if (this->_bus->DEBUG_MODE)
	{
		// Produce Gameboy Doctor Log
		//
		this->_bus->get_u8_memory_value(memory::$::LY) = 0x90;

		// Format: `A:00 F:11 B:22 C:33 D:44 E:55 H:66 L:77 SP:8888 PC:9999 PCMEM:AA,BB,CC,DD`
		std::cerr << "A:" << hex(2) << (int)this->_registers.A << " ";
		std::cerr << "F:" << hex(2) << (int)this->_registers.F << " ";
		std::cerr << "B:" << hex(2) << (int)this->_registers.B << " ";
		std::cerr << "C:" << hex(2) << (int)this->_registers.C << " ";
		std::cerr << "D:" << hex(2) << (int)this->_registers.D << " ";
		std::cerr << "E:" << hex(2) << (int)this->_registers.E << " ";
		std::cerr << "H:" << hex(2) << (int)this->_registers.H << " ";
		std::cerr << "L:" << hex(2) << (int)this->_registers.L << " ";
		std::cerr << "SP:" << hex(4) << (int)this->_registers.SP << " ";
		std::cerr << "PC:" << hex(4) << (int)this->_registers.PC << " ";
		std::cerr << "PCMEM:";
		std::cerr << hex(2) << (int)this->_bus->get_u8_memory_value(this->_registers.PC+0) << ",";
		std::cerr << hex(2) << (int)this->_bus->get_u8_memory_value(this->_registers.PC+1) << ",";
		std::cerr << hex(2) << (int)this->_bus->get_u8_memory_value(this->_registers.PC+2) << ",";
		std::cerr << hex(2) << (int)this->_bus->get_u8_memory_value(this->_registers.PC+3) << '\n';
		// ---
	}

	std::uint8_t cycles = this->execute_instruction(this->_bus->CPU_OPS);
	//this->_registers.print();
	//std::cerr << "Z=" << hex(2) << (int)this->get_flag(cpu::FLAG::Z) << ", ";
	//std::cerr << "N=" << hex(2) << (int)this->get_flag(cpu::FLAG::N) << ", ";
	//std::cerr << "H=" << hex(2) << (int)this->get_flag(cpu::FLAG::H) << ", ";
	//std::cerr << "C=" << hex(2) << (int)this->get_flag(cpu::FLAG::C) << "";
	//std::cerr << std::endl;

	return cycles;
}

void cpu::initialise(const std::uint8_t& A, const std::uint8_t& F, const std::uint8_t& B, const std::uint8_t& C, const std::uint8_t& D, const std::uint8_t& E, const std::uint8_t& H, const std::uint8_t& L, const std::uint16_t& SP, const std::uint16_t& PC)
{
	this->_registers.A = A;
	this->_registers.F = F;
	this->_registers.B = B;
	this->_registers.C = C;
	this->_registers.D = D;
	this->_registers.E = E;
	this->_registers.H = H;
	this->_registers.L = L;
	this->_registers.SP = SP;
	this->_registers.PC = PC;
}

void cpu::dump(std::ofstream& file)
{
	std::array<std::uint8_t, 12> _registers;
	_registers[0] = this->_registers.A;
	_registers[1] = this->_registers.F;
	_registers[2] = this->_registers.B;
	_registers[3] = this->_registers.C;
	_registers[4] = this->_registers.D;
	_registers[5] = this->_registers.E;
	_registers[6] = this->_registers.H;
	_registers[7] = this->_registers.L;
	*reinterpret_cast<std::uint16_t*>(&_registers[8]) = this->_registers.SP;
	*reinterpret_cast<std::uint16_t*>(&_registers[10]) = this->_registers.PC;

	std::copy(_registers.begin(), _registers.end(), std::ostreambuf_iterator<char>(file));
}

void cpu::load_dump(std::ifstream& file)
{
	std::array<std::uint8_t, 12> _registers;
	
	std::vector<std::uint8_t> _dump = std::vector<std::uint8_t>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	std::copy_n(_dump.begin(), 12, _registers.begin());

	this->_registers.A = _registers[0];
	this->_registers.F = _registers[1];
	this->_registers.B = _registers[2];
	this->_registers.C = _registers[3];
	this->_registers.D = _registers[4];
	this->_registers.E = _registers[5];
	this->_registers.H = _registers[6];
	this->_registers.L = _registers[7];
	this->_registers.SP = *reinterpret_cast<std::uint16_t*>(&_registers[8]);
	this->_registers.PC = *reinterpret_cast<std::uint16_t*>(&_registers[10]);

	//this->_registers.print();
}

void cpu::hook(void)
{
	//this->_registers.print();
}
