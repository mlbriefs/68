// Copyright 2012-2014 Nicolas Normand <Nicolas.Normand@polytech.univ-nantes.fr>
// 
// This file is part of LUTBasedNSDistanceTransform.
// 
// LUTBasedNSDistanceTransform is free software: you can redistribute it and/or
// modify it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// LUTBasedNSDistanceTransform is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
// Public License for more details.
// 
// You should have received a copy of the GNU General Public License along with
// LUTBasedNSDistanceTransform.  If not, see <http://www.gnu.org/licenses/>.
//
// $Id: RationalBeattySequence.h 150 2014-02-26 08:59:35Z Nicolas.Normand $

#include <stdio.h>
extern "C" {
typedef struct RationalBeattySequence RationalBeattySequence;

RationalBeattySequence *RationalBeattySequenceCreate(int num, int den, int dir);

RationalBeattySequence *RationalBeattySequenceCreateInverse(RationalBeattySequence *seq);

RationalBeattySequence *RationalBeattySequenceCreateComplement(RationalBeattySequence *seq);

void RationalBeattySequenceFree(RationalBeattySequence *seq);

int RationalBeattySequenceValueAtIndex(RationalBeattySequence *seq, int i);

void RationalBeattySequencePrint(RationalBeattySequence *seq);

int RationalBeattySequenceEquals(RationalBeattySequence *seq1, RationalBeattySequence *seq2);
}

class RationalBeattySeq {
private:
    int num;
    int den;
    int offset;

public:
    RationalBeattySeq(int num, int den, int offset) :
    num(num),
    den(den),
    offset(offset) { }

    RationalBeattySeq invert() const {
	return RationalBeattySeq(den, num, -offset - 1);
    }

    RationalBeattySeq complement() const {
	return RationalBeattySeq(num, num - den, -offset - 1);
    }

    int operator()(int n) const {
	//assert(n >= 0);
	// Floor dir: floor(n*tau) -> (n*num)/den
	// Ceil dir: ceil(n*tau - 1) -> (n*num+den-1)/den - 1 -> (n*num-1)/den
	return (num * n + offset) / den;
    }

    void print() const {
	printf("⌊(%d*n",num);
	if (offset!=0)
	    printf("%+d", offset);
	printf(")/%d⌋\n", den);
	//printf("num: %d, den: %d, dir: %d\n", num, den, offset);
    }

    bool equals(RationalBeattySeq &otherSeq) const {
	return num == otherSeq.num &&
	       den == otherSeq.den &&
	       offset == otherSeq.offset;
    }
};
