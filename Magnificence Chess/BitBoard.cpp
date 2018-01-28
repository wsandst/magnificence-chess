#include "stdafx.h"
#include "BitBoard.h"
#include "Board.h"
#include <iostream>

using namespace std;

BitBoard::BitBoard()
{
	SetUp();
}


BitBoard::~BitBoard()
{
}

BitBoard::BitBoard(string fen)
{
	SetUp();
	SetState(fen);
}

void BitBoard::SetState(string fen)
{
	int i = 0;
	int pos = 0;
	//pieces
	while (i < fen.size() && fen[i] != ' ')
	{
		switch (fen[i])
		{
		case 'r':
			mailBox[pos] = 10;
			pos++;
			break;
		case 'n':
			mailBox[pos] = 11;
			pos++;
			break;
		case 'b':
			mailBox[pos] = 9;
			pos++;
			break;
		case 'q':
			mailBox[pos] = 8;
			pos++;
			break;
		case 'p':
			mailBox[pos] = 12;
			pos++;
			break;
		case 'k':
			mailBox[pos] = 7;
			pos++;
			break;
		case 'R':
			mailBox[pos] = 3;
			pos++;
			break;
		case 'N':
			mailBox[pos] = 4;
			pos++;
			break;
		case 'B':
			mailBox[pos] = 2;
			pos++;
			break;
		case 'Q':
			mailBox[pos] = 1;
			pos++;
			break;
		case 'P':
			mailBox[pos] = 5;
			pos++;
			break;
		case 'K':
			mailBox[pos] = 0;
			pos++;
			break;
		case '1':
			for (int i = 0; i < 1; i++)
			{
				mailBox[pos] = 14;
				pos++;
			}
			break;
		case '2':
			for (int i = 0; i < 2; i++)
			{
				mailBox[pos] = 14;
				pos++;
			}
			break;
		case '3':
			for (int i = 0; i < 3; i++)
			{
				mailBox[pos] = 14;
				pos++;
			}
			break;
		case '4':
			for (int i = 0; i < 4; i++)
			{
				mailBox[pos] = 14;
				pos++;
			}
			break;
		case '5':
			for (int i = 0; i < 5; i++)
			{
				mailBox[pos] = 14;
				pos++;
			}
			break;
		case '6':
			for (int i = 0; i < 6; i++)
			{
				mailBox[pos] = 14;
				pos++;
			}
			break;
		case '7':
			for (int i = 0; i < 7; i++)
			{
				mailBox[pos] = 14;
				pos++;
			}
			break;
		case '8':
			for (int i = 0; i < 8; i++)
			{
				mailBox[pos] = 14;
				pos++;
			}
			break;
		default:
			break;
		}
		i++;
	};
	i++;
	//turn
	while (i < fen.size() && fen[i] != ' ')
	{
		i++;
	}
	i++;
	for (int i = 0; i < 64; i++)
	{
		u8 value = mailBox[i];
		if (i > 47)
		{
			u8 jfasdf = mailBox[i];
		}
	}
	//rockad rights
	rockad = 0;
	while (i < fen.size() && fen[i] != ' ')
	{
		switch (fen[i])
		{
		case 'K':
			rockad |= 8;
			break;
		case 'k':
			rockad |= 2;
			break;
		case 'Q':
			rockad |= 4;
			break;
		case 'q':
			rockad |= 1;
			break;
		default:
			break;
		}
		i++;
	}
	i++;
	//Ein Passant
	EP = 0;
	switch (i < fen.size() && fen[i])
	{
	case 'a':
		EP = 128;
		break;
	case 'b':
		EP = 64;
		break;
	case 'c':
		EP = 32;
		break;
	case 'd':
		EP = 16;
		break;
	case 'e':
		EP = 8;
		break;
	case 'f':
		EP = 4;
		break;
	case 'g':
		EP = 2;
		break;
	case 'h':
		EP = 1;
		break;
	default:
		break;
	}
	//Find next thing
	while (i < fen.size() && fen[i] != ' ')
	{
		i++;
	}
	i++;
	while (i < fen.size() && fen[i] != ' ')
	{
		i++;
	}
	i--;
	//silent moves
	u8 mult = 1;
	silent = 0;
	while (i < fen.size() && fen[i] != ' ')
	{
		switch (fen[i])
		{
		case '0':
			break;
		case '1':
			silent += 1 * mult;
			break;
		case '2':
			silent += 2 * mult;
			break;
		case '3':
			silent += 3 * mult;
			break;
		case '4':
			silent += 4 * mult;
			break;
		case '5':
			silent += 5 * mult;
			break;
		case '6':
			silent += 6 * mult;
			break;
		case '7':
			silent += 7 * mult;
			break;
		case '8':
			silent += 8 * mult;
			break;
		case '9':
			silent += 9 * mult;
			break;
		default:
			break;
		}
		mult = 10;
		i--;
	}
	for (int i = 0; i < 32; i++)
	{
		u64 mem = mailBox[i];
		mailBox[i] = mailBox[63 - i];
		mailBox[63 - i] = mem;
	}
	for (int i = 0; i < 15; i++)
	{
		Pieces[i] = 0;
	}
	for (int i = 0; i < 64; i++)
	{
		Pieces[mailBox[i]] |= one << i;
	}
	for (int i = 0; i < 6; i++)
	{
		Pieces[6] |= Pieces[i];
	}
	for (int i = 7; i < 13; i++)
	{
		Pieces[13] |= Pieces[i];
	}
}

void BitBoard::SetUp()
{
	MRook = new Magic[64];
	MBishop = new Magic[64];
	rows = new u64[8];
	nRows = new u64[8];
	nColumns = new u64[8];
	columns = new u64[8];
	//KingSet = new u64[64];
	KnightSet = new u64[64];
	Pieces = new u64[15];
	mailBox = new u8[64];
	UL = new u64[64];
	UR = new u64[64];
	DL = new u64[64];
	DR = new u64[64];
	U = new u64[64];
	D = new u64[64];
	R = new u64[64];
	L = new u64[64];
	//creating rows and columns tables
	for (int i = 0; i < 8; i++)
	{
		columns[i] = one << i;
		columns[i] = columns[i] << 8 | columns[i];
		columns[i] = columns[i] << 16 | columns[i];
		columns[i] = columns[i] << 32 | columns[i];
		rows[i] = one << (i * 8);
		rows[i] = rows[i] << 1 | rows[i];
		rows[i] = rows[i] << 2 | rows[i];
		rows[i] = rows[i] << 4 | rows[i];
		nRows[i] = ~rows[i];
		nColumns[i] = ~columns[i];
	}
	//Generate King and knight sets + magics + vectors
	for (int i = 0; i < 64; i++)
	{
		//Generate King and knight sets
		{
			u64 start = one << i;
			KingSet[i] = start << 8 | start >> 8;
			KingSet[i] |= (start << 1 | start << 9 | start >> 7) & nColumns[0];
			KingSet[i] |= (start >> 1 | start >> 9 | start << 7) & nColumns[7];
			KnightSet[i] = (((start << 10) | (start >> 6)) & ~(columns[0] | columns[1])) | (((start << 17) | (start >> 15)) & (~(columns[0])))
				| (((start << 6) | (start >> 10)) & ~(columns[7] | columns[6])) | (((start << 15) | (start >> 17)) & ~(columns[7]));
		};
		//generate RookTables
		//check RookTables
		{
			u32 index;
			u64 pos = one << i, mask;
			mask = ((rows[i / 8] ^ pos) & (~(columns[0] ^ columns[7])));
			mask |= ((columns[i % 8] ^ pos) & (~(rows[0] ^ rows[7])));
			u64 attacks = 0, pattern = 0, count = 0, memory = mask;
			vector<u64> out;
			vector<u32> indexes;
			while (memory)
			{
				count++;
				_BitScanForward64(&index, memory);
				memory = memory & (memory - 1);
				indexes.push_back(index);
			}
			allVariations(mask, indexes, 0, count - 1, &out);
			int size = out.size();
			u64 *ptr = new u64[size];
			for (int i2 = 0; i2 < size; i2++)
			{
				u64 ocupancy = out[i2];
				{
					pos = one << i;
					attacks = 0;
					while (pos)
					{
						pos = pos << 8;
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = pos >> 8;
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos >> 1) & (~columns[7]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos << 1) & (~columns[0]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
				};
				ptr[_pext_u64(ocupancy, mask)] = attacks;
			}
			for (int i2 = 0; i2 < size; i2++)
			{
				u64 ocupancy = out[i2];
				{
					pos = one << i;
					attacks = 0;
					while (pos)
					{
						pos = pos << 8;
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = pos >> 8;
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos >> 1) & (~columns[7]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos << 1) & (~columns[0]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
				};
				if (ptr[_pext_u64(ocupancy, mask)] != attacks)
				{
					int q = 5;
				}
				else
				{
					MRook[i].mask = mask;
					MRook[i].table = ptr;
				};
			}
		};
		//Generate BishopTables
		//check BishopTables
		{
			u32 index;
			u64 pos, mask = 0;
			pos = one << i;
			while (pos)
			{
				pos = (pos << 9) & (~(columns[7] | rows[7] | columns[0]));
				mask |= pos;
			}
			pos = one << i;
			while (pos)
			{
				pos = (pos >> 7) & (~(columns[7] | rows[0] | columns[0]));
				mask |= pos;
			}
			pos = one << i;
			while (pos)
			{
				pos = (pos >> 9) & (~(columns[0] | rows[0] | columns[7]));
				mask |= pos;
			}
			pos = one << i;
			while (pos)
			{
				pos = (pos << 7) & (~(columns[0] | rows[7] | columns[7]));
				mask |= pos;
			}
			u64 attacks = 0, pattern = 0, count = 0, memory = mask;
			vector<u64> out;
			vector<u32> indexes;
			while (memory)
			{
				count++;
				_BitScanForward64(&index, memory);
				memory = memory & (memory - 1);
				indexes.push_back(index);
			}
			allVariations(mask, indexes, 0, count - 1, &out);
			int size = out.size();
			u64 *ptr = new u64[size];
			for (int i2 = 0; i2 < size; i2++)
			{
				u64 ocupancy = out[i2];
				attacks = 0;
				{
					pos = one << i;
					while (pos)
					{
						pos = (pos << 9) & (~columns[0]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos >> 7) & (~columns[0]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos << 7) & (~columns[7]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos >> 9) & (~columns[7]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
				}
				ptr[_pext_u64(ocupancy, mask)] = attacks;
			}
			for (int i2 = 0; i2 < size; i2++)
			{
				u64 ocupancy = out[i2];
				attacks = 0;
				{
					pos = one << i;
					while (pos)
					{
						pos = (pos << 9) & (~columns[0]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos >> 7) & (~columns[0]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos << 7) & (~columns[7]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
					pos = one << i;
					while (pos)
					{
						pos = (pos >> 9) & (~columns[7]);
						attacks |= pos;
						pos = pos & (~ocupancy);
					}
				}
				if (ptr[_pext_u64(ocupancy, mask)] != attacks)
				{
					int q = 5;
				}
				else
				{
					MBishop[i].mask = mask;
					MBishop[i].table = ptr;
				};
			}
		};
		//Generate vectors
		{
			u64 pos = one << i;
			U[i] = 0;
			while (pos)
			{
				pos = pos << 8;
				U[i] |= pos;
			}
			pos = one << i;
			D[i] = 0;
			while (pos)
			{
				pos = pos >> 8;
				D[i] |= pos;
			}
			pos = one << i;
			L[i] = 0;
			while (pos)
			{
				pos = (pos << 1) & (~columns[0]);
				L[i] |= pos;
			}
			pos = one << i;
			R[i] = 0;
			while (pos)
			{
				pos = (pos >> 1) & nColumns[7];
				R[i] |= pos;
			}
			pos = one << i;
			DR[i] = 0;
			while (pos)
			{
				pos = (pos >> 9) & nColumns[7];
				DR[i] |= pos;
			}
			pos = one << i;
			UR[i] = 0;
			while (pos)
			{
				pos = (pos << 7) & nColumns[7];
				UR[i] |= pos;
			}
			pos = one << i;
			UL[i] = 0;
			while (pos)
			{
				pos = (pos << 9) & (~columns[0]);
				UL[i] |= pos;
			}
			pos = one << i;
			DL[i] = 0;
			while (pos)
			{
				pos = (pos >> 7) & (~columns[0]);
				DL[i] |= pos;
			}
		}
	}
}
//Piece taken 4, ein pasant 1, rockad 1, upgrade 1, upgrade to 4, to 6, from 6
//Ein Pasant state 8
//move encoding					TTTTNUBBBBRE00000000ttttttffffff
// extracting special moves	  0b00001000000000000000000000000000
//							  0b00000100000000000000000000000000
//							  0b00000000001000000000000000000000
//Piece taken [4] = T ( << 28), non silent [1] = N (<< 27), upgrade [1] = U (<<26)
//Upgrade to [4] = B ( << 22), Rockad [1] = R ( << 21), einpassant [1] = E ( << 20);
//to [6] = t (<< 6), from[6] = f (<< 0);
//0 = patt;
//universal = matt

vector<u32> BitBoard::WhiteLegalMoves()
{
	vector<u32> result;
	result.reserve(30);
	u32 kingIndex;
	u64 occupancy = Pieces[6] | Pieces[13], PinnedPieces = 0,
		legalTargets = 0, ownPieces = Pieces[6], king = Pieces[0],
		nOccupancy = ~occupancy;
	int checks = 0;
	//Find checks and pinned pieces and king moves
	{
		//pawns
		u64 EPiece = Pieces[11];
		u64 ThreatenedSquaresO = ((Pieces[12] >> 9) & nColumns[7]);
		if (ThreatenedSquaresO & king)
		{
			checks++;
			legalTargets |= (ThreatenedSquaresO & king) << 9;
		}
		ThreatenedSquaresO |= ((Pieces[12] >> 7) & nColumns[0]);
		if (ThreatenedSquaresO & king && checks == 0)
		{
			checks++;
			legalTargets |= (ThreatenedSquaresO & king) << 7;
		}
		u32 index;
		//Knights
		while (EPiece)
		{
			_BitScanForward64(&index, EPiece);
			EPiece &= EPiece - 1;
			ThreatenedSquaresO |= KnightSet[index];
			if (KnightSet[index] & king)
			{
				checks++;
				legalTargets |= one << index;
			}
		}
		//king
		_BitScanForward64(&index, Pieces[7]);
		ThreatenedSquaresO |= KingSet[index];
		//rooks + queens
		EPiece = Pieces[8] | Pieces[10];
		_BitScanForward64(&kingIndex, king);
		u64 kingAttacks = MagicRook(king, occupancy);
		u64 NKOccupancy = occupancy ^ king;
		u64 memory;
		if (kingIndex > 63)
		{
			cout << king;
		}
		else
		{
			memory = EPiece & (U[kingIndex]);
		}
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicRook(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & U[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & U[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & (D[kingIndex]);
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicRook(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & D[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & D[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & (L[kingIndex]);
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicRook(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & L[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & L[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & (R[kingIndex]);
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicRook(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & R[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & R[kingIndex];
			}
			memory &= memory - 1;
		}
		while (EPiece)
		{
			ThreatenedSquaresO |= MagicRook(EPiece, NKOccupancy);
			EPiece &= EPiece - 1;
		}
		//bishops + queens
		EPiece = Pieces[8] | Pieces[9];
		kingAttacks = MagicBishop(king, occupancy);
		memory = EPiece & UL[kingIndex];
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicBishop(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & UL[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & UL[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & UR[kingIndex];
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicBishop(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & UR[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & UR[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & DR[kingIndex];
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicBishop(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & DR[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & DR[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & DL[kingIndex];
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicBishop(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & DL[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & DL[kingIndex];
			}
			memory &= memory - 1;
		}
		while (EPiece)
		{
			ThreatenedSquaresO |= MagicBishop(EPiece, NKOccupancy);;
			EPiece &= EPiece - 1;
		}
		u64 kingMoves = KingSet[kingIndex] & (~ThreatenedSquaresO) & (~ownPieces);
		extractMoves(kingMoves, kingIndex, &result);
		if (checks > 1)
		{
			if (result.size() < 1)
			{
				result.push_back(universal);
			}
			return result;
		}
		else if (checks == 0)
		{
			legalTargets = universal ^ ownPieces;
			if ((rockad & 8) && !((14) & ThreatenedSquaresO) && !(6 & occupancy))
			{
				u32 move = 3 | (1 << 6) | one << 21 | (((u64)EP) << 12) | ((u32)14) << 28;
				result.push_back(move);
			}
			if ((rockad & 4) && !((56) & ThreatenedSquaresO) && !(112 & occupancy))
			{
				u32 move = 3 | (5 << 6) | one << 21 | (((u64)EP) << 12) | ((u32)14) << 28;
				result.push_back(move);
			}
		}
	}; 
	//Pawn Move
	{
		u64 pawns = Pieces[5] & PinnedPieces, EPieces = Pieces[13];
		u32 index;
		while (pawns)
		{
			u64 res;
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if ((UL[index] | DR[index]) & king)
			{
				res = (((one << (index + 9)) & nColumns[0]) & Pieces[6]);
			}
			else if ((UR[index] | DL[index]) & king)
			{
				res = (((one << (index + 7)) & nColumns[7]) & Pieces[6]);
			}
			else
			{
				res = (((one << (index + 8))) & nOccupancy);
				if (res & rows[2])
				{
					res |= ((res << 8) & nOccupancy);
				}
			}
			res &= legalTargets;
			extractPawnMoves(res, index, &result);
		}
		pawns = ((Pieces[5] & ~(PinnedPieces)) << 9) & nColumns[0] & EPieces & legalTargets;
		while (pawns)
		{
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if (index < 56)
			{
				result.push_back(index << 6 | (index - 9) | one << 27 | mailBox[index] << 28);
			}
			else
			{
				u32 move = index << 6 | (index - 9) | one << 27 | mailBox[index] << 28 | one << 26;
				for (int i = 1; i < 5; i++)
				{
					result.push_back(move | (i << 26));
				}
			}
		}
		pawns = ((Pieces[5] & ~(PinnedPieces)) << 7) & nColumns[7] & EPieces & legalTargets;
		while (pawns)
		{
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if (index < 56)
			{
				result.push_back(index << 6 | (index - 7) | one << 27 | mailBox[index] << 28);
			}
			else
			{
				u32 move = index << 6 | (index - 7) | one << 27 | mailBox[index] << 28 | one << 26;
				for (int i = 1; i < 5; i++)
				{
					result.push_back(move | (i << 26));
				}
			}
		}
		pawns = ((Pieces[5] & ~(PinnedPieces)) << 8) & nOccupancy;
		u64 mem = ((pawns & rows[2]) << 8) & nOccupancy & legalTargets;
		pawns &= legalTargets;
		while (pawns)
		{
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if (index < 56)
			{
				result.push_back(index << 6 | (index + 8) | one << 27 | mailBox[index] << 28);
			}
			else
			{
				u32 move = index << 6 | (index - 8) | one << 27 | mailBox[index] << 28 | one << 26;
				for (int i = 1; i < 5; i++)
				{
					result.push_back(move | (i << 26));
				}
			}
		}
		pawns = mem;
		while (pawns)
		{
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if (index > 7)
			{
				result.push_back(index << 6 | (index - 16) | one << 27 | mailBox[index] << 28);
			}
		}
	}
	return result;
}

vector<u32> BitBoard::BlackLegalMoves()
{
	vector<u32> result;
	result.reserve(35);
	u32 kingIndex;
	u64 occupancy = Pieces[6] | Pieces[13], PinnedPieces = 0,
		legalTargets = 0, ownPieces = Pieces[13], king = Pieces[7],
		nOccupancy = ~occupancy;
	int checks = 0;
	//Find checks and pinned pieces
	{
		//pawns
		u64 EPiece = Pieces[4];
		u64 ThreatenedSquaresO = ((Pieces[5] << 7) & nColumns[7]);
		if (ThreatenedSquaresO & king)
		{
			checks++;
			legalTargets |= (ThreatenedSquaresO & king) >> 7;
		}
		ThreatenedSquaresO |= ((Pieces[5] << 9) & nColumns[0]);
		if (ThreatenedSquaresO & king && checks == 0)
		{
			checks++;
			legalTargets |= (ThreatenedSquaresO & king) >> 9;
		}
		u32 index = 0;
		//Knights
		while (EPiece)
		{
			_BitScanForward64(&index, EPiece);
			EPiece &= EPiece - 1;
			ThreatenedSquaresO |= KnightSet[index];
			if (KnightSet[index] & king)
			{
				checks++;
				legalTargets |= one << index;
			}
		}
		//king
		_BitScanForward64(&index, Pieces[0]);
		//queen + rooks
		EPiece = Pieces[1] | Pieces[3];
		_BitScanForward64(&kingIndex, king);
		u64 kingAttacks = MagicRook(king, occupancy);
		u64 NKOccupancy = occupancy ^ king;
		ThreatenedSquaresO |= KingSet[index];
		u64 memory = EPiece & (U[kingIndex]);
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicRook(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & U[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & U[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & (D[kingIndex]);
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicRook(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & D[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & D[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & (L[kingIndex]);
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicRook(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & L[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & L[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & (R[kingIndex]);
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicRook(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & R[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & R[kingIndex];
			}
			memory &= memory - 1;
		}
		while (EPiece)
		{
			ThreatenedSquaresO |= MagicRook(EPiece, NKOccupancy);
			EPiece &= EPiece - 1;
		}
		//Queen + bishops
		EPiece = Pieces[1] | Pieces[2];
		kingAttacks = MagicBishop(king, occupancy);
		memory = EPiece & UL[kingIndex];
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicBishop(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & UL[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & UL[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & UR[kingIndex];
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicBishop(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & UR[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & UR[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & DR[kingIndex];
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicBishop(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & DR[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & DR[kingIndex];
			}
			memory &= memory - 1;
		}
		memory = EPiece & DL[kingIndex];
		EPiece = EPiece ^ memory;
		while (memory)
		{
			u64 ret = MagicBishop(memory, NKOccupancy);
			ThreatenedSquaresO |= ret;
			if (ret & king)
			{
				legalTargets |= kingAttacks & DL[kingIndex];
				checks++;
			}
			else
			{
				ret = MagicRook(memory, occupancy);
				PinnedPieces |= ret & kingAttacks & DL[kingIndex];
			}
			memory &= memory - 1;
		}
		while (EPiece)
		{
			ThreatenedSquaresO |= MagicBishop(EPiece, NKOccupancy);;
			EPiece &= EPiece - 1;
		}
		u64 kingMoves = KingSet[kingIndex] & (~ThreatenedSquaresO) & (~ownPieces);
		extractMoves(kingMoves, kingIndex, &result);
		if (checks > 1)
		{
			if (result.size() < 1)
			{
				result.push_back(universal);
			}
			return result;
		}
		else if (checks == 0)
		{
			legalTargets = universal ^ ownPieces;
			if ((rockad & 2) && !((((u64)14) << 56) & ThreatenedSquaresO) && !((((u64)6) << 56) & occupancy))
			{
				u32 move = 59 | (57 << 6) | one << 21 | (((u64)EP) << 12) | ((u32)14) << 28;
				result.push_back(move);
			}
			if ((rockad & 1) && !((((u64)56) << 56) & ThreatenedSquaresO) && !((((u64)112) << 56) & occupancy))
			{
				u32 move = 59 | (61 << 6) | one << 21 | (((u64)EP) << 12) | ((u32)14) << 28;
				result.push_back(move);
			}
		}
	};
	//Pawn Move
	{
		u64 pawns = Pieces[12] & PinnedPieces, EPieces = Pieces[6];
		u32 index;
		while (pawns)
		{
			u64 res;
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if ((UL[index] | DR[index]) & king)
			{
				res = (((one << (index - 9)) & nColumns[7]) & EPieces);
			}
			else if ((UR[index] | DL[index]) & king)
			{
				res = (((one << (index - 7)) & nColumns[0]) & EPieces);
			}
			else
			{
				res = (((one << (index - 8))) & nOccupancy);
				if (res & rows[5])
				{
					res |= ((res >> 8) & nOccupancy);
				}
			}
			res &= legalTargets;
			extractPawnMoves(res, index, &result);
		}
		pawns = ((Pieces[12] & ~(PinnedPieces)) >> 9) & nColumns[7] & EPieces & legalTargets;
		while (pawns)
		{
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if (index > 7)
			{
				result.push_back(index << 6 | (index + 9) | one << 27 | mailBox[index] << 28);
			}
			else
			{
				u32 move = index << 6 | (index + 9) | one << 27 | mailBox[index] << 28 | one << 26;
				for (int i = 1; i < 5; i++)
				{
					result.push_back(move | (i << 26));
				}
			}
		}
		pawns = ((Pieces[12] & ~(PinnedPieces)) >> 7) & nColumns[0] & EPieces & legalTargets;
		while (pawns)
		{
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if (index > 7)
			{
				result.push_back(index << 6 | (index + 7) | one << 27 | mailBox[index] << 28);
			}
			else
			{
				u32 move = index << 6 | (index + 7) | one << 27 | mailBox[index] << 28 | one << 26;
				for (int i = 1; i < 5; i++)
				{
					result.push_back(move | (i << 26));
				}
			}
		}
		pawns = ((Pieces[12] & ~(PinnedPieces)) >> 8) & nOccupancy;
		u64 mem = ((pawns & rows[5]) >> 8) & nOccupancy & legalTargets;
		pawns &= legalTargets;
		while (pawns)
		{
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if (index > 7)
			{
				result.push_back(index << 6 | (index + 8) | one << 27 | mailBox[index] << 28);
			}
			else
			{
				u32 move = index << 6 | (index + 8) | one << 27 | mailBox[index] << 28 | one << 26;
				for (int i = 1; i < 5; i++)
				{
					result.push_back(move | (i << 26));
				}
			}
		}
		pawns = mem;
		while (pawns)
		{
			_BitScanForward64(&index, pawns);
			pawns &= pawns - 1;
			if (index > 7)
			{
				result.push_back(index << 6 | (index + 16) | one << 27 | mailBox[index] << 28);
			}
		}
	}
	return result;
}

void BitBoard::MakeMove(u32 move)
{
	SilentMemory.push_back(silent);
	RockadMemory.push_back(rockad);
	EPMemory.push_back(EP);
	EP = 0;
	if (move & 0b00001000000000000000000000000000)
	{
		silent = 0;
	}
	else
	{
		silent++;
	}
	u8 from = (0b111111 & move), to = 0b111111 & (move >> 6);
	u8 moved = mailBox[from];
	u8 taken = mailBox[to];
	u64 ToSet = (one << to), NFromSet = ~(one << from), NToSet = ~ToSet;
	if (from == 0 || to == 0)
	{
		rockad &= (0b0111);
	}
	if (from == 7 || to == 7)
	{
		rockad &= (0b1011);
	}
	if (from == 63 || to == 63)
	{
		rockad &= (0b1110);
	}
	if (from == 56 || to == 56)
	{
		rockad &= (0b1101);
	}
	Pieces[moved] &= NFromSet;
	Pieces[moved] |= ToSet;
	Pieces[taken] &= NToSet;
	if (taken < 6)
	{
		Pieces[6] &= NToSet;
	}
	else if (taken < 13)
	{
		Pieces[13] &= NToSet;
	}
	mailBox[to] = mailBox[from];
	mailBox[from] = 14;
	switch (moved)
	{
	case 5://white pawn
		if (move & (one << 26))
		{
			Pieces[5] &= NToSet;
			Pieces[(move >> 22) & 0b1111] |= ToSet;
			mailBox[to] = (move >> 22) & 0b1111;
		}
		if (to - from > 9)
		{
			EP = from & 0b111;
		}
		break;
	case 12://black pawn
		if (move & (one << 26))
		{
			Pieces[12] &= NToSet;
			Pieces[(move >> 22) & 0b1111 + 7] |= ToSet;
			mailBox[to] = ((move >> 22) & 0b1111) + 7;
		}
		if (from - to > 9)
		{
			EP = from & 0b111;
		}
		break;
	case 0://white king
		rockad &= 0b11;
		break;
	case 7://black king
		rockad &= 0b1100;
		break;
	default:
		break;
	}
	if (move & 0b00000000001000000000000000000000)
	{
		u64 mask, NMask;
		switch (to)
		{
		case 1:	//white kingside
			mask = 0b100, NMask = (~(0b001));
			mailBox[0] = 14;
			mailBox[2] = 3;
			Pieces[3] &= NMask;
			Pieces[3] |= mask;
			break;
		case 5:	//White Queen side
			mask = one << 4, NMask = (~(one << 7));
			mailBox[7] = 14;
			mailBox[4] = 3;
			Pieces[3] &= NMask;
			Pieces[3] |= mask;
			break;
		case 57://Black king sides
			mask = one << 58
				, NMask = (~(one << 56));
			mailBox[56] = 14;
			mailBox[58] = 10;
			Pieces[10] &= NMask;
			Pieces[10] |= mask;
			break;
		case 61://Black Queen side
			mask = one << 60
				, NMask = ~(one << 63);
			mailBox[63] = 14;
			mailBox[60] = 10;
			Pieces[10] &= NMask;
			Pieces[10] |= mask;
			break;
		default:
			break;
		}
	}
}

void BitBoard::UnMakeMove(u32 move)
{
	silent = SilentMemory.back();
	EP = EPMemory.back();
	rockad = RockadMemory.back();
	SilentMemory.pop_back();
	EPMemory.pop_back();
	RockadMemory.pop_back();
	u8 from = (0b111111 & move), to = 0b111111 & (move >> 6);
	u8 moved = mailBox[to];
	u8 taken = move >> 28;
	u64 ToSet = (one << to), FromSet = (one << from), NToSet = ~ToSet;
	switch (moved)
	{
	case 5://white pawn
		if (move & (one << 20))
		{
			
		}
		else
		{
			mailBox[from] = mailBox[to];
			mailBox[to] = taken;
			Pieces[moved] &= NToSet;
			Pieces[moved] |= FromSet;
			Pieces[taken] |= ToSet;
		}
		break;
	case 12://black pawn
		if (move & (one << 20))
		{

		}
		else
		{
			mailBox[from] = mailBox[to];
			mailBox[to] = taken;
			Pieces[moved] &= NToSet;
			Pieces[moved] |= FromSet;
			Pieces[taken] |= ToSet;
		}
		break;
	default:
		//std
		if (move & (one << 26))
		{
			u8 pawn;
			if (moved < 6)
			{
				pawn = 5;
			}
			else
			{
				pawn = 12;
			}
			mailBox[from] = pawn;
			mailBox[to] = taken;
			Pieces[moved] &= NToSet;
			Pieces[pawn] |= FromSet;
			Pieces[taken] |= ToSet;
		}
		else
		{
			mailBox[from] = mailBox[to];
			mailBox[to] = taken;
			Pieces[moved] &= NToSet;
			Pieces[moved] |= FromSet;
			Pieces[taken] |= ToSet;
		}
		//rockad
		if (move & 0b00000000001000000000000000000000)
		{
			u64 mask, NMask;
			switch (to)
			{
			case 1:	//white kingside
				mask = 0b001, NMask = (~(0b100));
				mailBox[0] = 3;
				mailBox[2] = 14;
				Pieces[3] &= NMask;
				Pieces[3] |= mask;
				break;
			case 5:	//White Queen side
				mask = one << 7, NMask = (~(one << 4));
				mailBox[7] = 3;
				mailBox[4] = 14;
				Pieces[3] &= NMask;
				Pieces[3] |= mask;
				break;
			case 57://Black king sides
				mask = one << 56
					, NMask = (~(one << 58));
				mailBox[56] = 10;
				mailBox[58] = 14;
				Pieces[10] &= NMask;
				Pieces[10] |= mask;
				break;
			case 61://Black Queen side
				mask = one << 63
					, NMask = ~(one << 60);
				mailBox[63] = 10;
				mailBox[60] = 14;
				Pieces[10] &= NMask;
				Pieces[10] |= mask;
				break;
			default:
				break;
			}
		}
		break;
	}
}