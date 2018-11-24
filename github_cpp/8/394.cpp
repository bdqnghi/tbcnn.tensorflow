#include <string>
#include <sstream>
#include "PractRand/config.h"
#include "PractRand/rng_basics.h"
#include "PractRand/rng_helpers.h"
#include "PractRand/rng_internals.h"

#include "PractRand/RNGs/mt19937.h"
#include "PractRand/RNGs/other/fibonacci.h"

using namespace PractRand;
using namespace PractRand::Internals;

namespace PractRand {
	namespace RNGs {
		namespace Polymorphic {
			namespace NotRecommended {
				Uint8 lfsr_medium::raw8() {
					if (used < SIZE) return cbuf[used++];
					for (int i = 0; i < LAG; i++) {
						cbuf[i] ^= cbuf[i+(SIZE-LAG)] ^ table1[cbuf[i+1]] ^ table2[cbuf[i+2]];
					}
					for (int i = LAG; i < SIZE-2; i++) {
						cbuf[i] ^= cbuf[i-LAG] ^ table1[cbuf[i+1]] ^ table2[cbuf[i+2]];
					}
					cbuf[SIZE-2] ^= cbuf[SIZE-2-LAG] ^ table1[cbuf[SIZE-1]] ^ table2[cbuf[0]];
					cbuf[SIZE-1] ^= cbuf[SIZE-1-LAG] ^ table1[cbuf[0]] ^ table2[1];
					used = 1;
					return cbuf[0];
				}
				std::string lfsr_medium::get_name() const {return "lfsr_medium";}
				void lfsr_medium::walk_state(StateWalkingObject *walker) {
					for (int i = 0; i < SIZE; i++) walker->handle(cbuf[i]);
					walker->handle(used);
					if (used >= SIZE) used = 0;
				}
				lfsr_medium::lfsr_medium() {
					used = 0;
					Uint8 vartaps = 1+2;//255 - 16;
					for (Uint32 i = 0; i < 256; i++) {
						Uint8 low = 0;
						Uint8 high = 0;
						for (int b = 0; b < 8; b++) {
							if ((vartaps >> b) & 1) {
								low ^= i >> b;
								if (b) high ^= i << (8-b);
							}

						}
						table1[i] = low;
						table2[i] = high;
					}
				}

				//Mitchell-Moore: LFib32(Uint32, 55, 24, ADD)
				Uint32 mm32::raw32() {
					Uint32 tmp;
					tmp = cbuf[index1] += cbuf[index2];
					if ( ++index1 == 55 ) index1 = 0;
					if ( ++index2 == 55 ) index2 = 0;
					return tmp;
				}
				std::string mm32::get_name() const {return "mm32";}
				void mm32::walk_state(StateWalkingObject *walker) {
					walker->handle(index1);
					for (int i = 0; i < 55; i++) walker->handle(cbuf[i]);
					if (index1 >= 55) index1 %= 55;
					index2 = index1 - 24;
					if (index2 >= 55) index2 += 55;
				}
				//Mitchell-Moore modified: LFib16(Uint32, 55, 24, ADD) >> 16
				Uint16 mm16of32::raw16() {
					Uint32 tmp;
					tmp = cbuf[index1] += cbuf[index2];
					if ( ++index1 == 55 ) index1 = 0;
					if ( ++index2 == 55 ) index2 = 0;
					return tmp >> 16;
				}
				std::string mm16of32::get_name() const {return "mm16of32";}
				void mm16of32::walk_state(StateWalkingObject *walker) {
					walker->handle(index1);
					for (int i = 0; i < 55; i++) walker->handle(cbuf[i]);
					if (index1 >= 55) index1 %= 55;
					index2 = index1 - 24;
					if (index2 >= 55) index2 += 55;
				}
				//Mitchell-Moore modified: LFib32(Uint32, 55, 24, ADD) >> 16
				Uint32 mm32_awc::raw32() {
					Uint32 tmp1, tmp2, tmp3;
					tmp1 = cbuf[index1];
					tmp2 = cbuf[index2];
					tmp3 = tmp1 + tmp2 + carry;
					cbuf[index1] = tmp3;
					carry = (tmp3 - tmp1) >> 31;
					if ((tmp3 == tmp1) && tmp2) carry = 1;
					if ( ++index1 == 55 ) index1 = 0;
					if ( ++index2 == 55 ) index2 = 0;
					return tmp3;
				}
				std::string mm32_awc::get_name() const {return "mm32_awc";}
				void mm32_awc::walk_state(StateWalkingObject *walker) {
					walker->handle(carry);
					walker->handle(index1);
					for (int i = 0; i < 55; i++) walker->handle(cbuf[i]);
					if (index1 >= 55) index1 %= 55;
					index2 = index1 - 24;
					if (index2 >= 55) index2 += 55;
					carry &= 1;
				}

				//used by Marsaglia in KISS4691 (2010)
				Uint32 mwc4691::raw32() {
					index = (index < 4691-1) ? index + 1 : 0;
					Uint32 x, t;
					x = cbuf[index];
					t = (x << 13) + carry + x;
					carry = (x>>19) + (t<=x);
					if (!t && !x) carry--;
					cbuf[index] = t;
					return t;
				}
				std::string mwc4691::get_name() const {return "mwc4691";}
				void mwc4691::walk_state(StateWalkingObject *walker) {
					walker->handle(index);
					walker->handle(carry);
					for (int i = 0; i < 4691; i++) walker->handle(cbuf[i]);
				}
				
				//
				Uint32 cbuf_accum::raw32() {
					Uint32 tmp = cbuf[--index];
					accum = ((accum << 11) | (accum >> 21)) + ~tmp;
					cbuf[index] = accum;
					if ( !index ) index = L;
					return accum;
				}
				std::string cbuf_accum::get_name() const {return "cbuf_accum";}
				void cbuf_accum::walk_state(StateWalkingObject *walker) {
					walker->handle(index);
					walker->handle(accum);
					for (int i = 0; i < L; i++) walker->handle(cbuf[i]);
					if (index >= L) index %= L;
				}
				Uint32 dual_cbuf::raw32() {
					Uint32 tmp1, tmp2;
					tmp1 = cbuf1[--index1];
					tmp2 = cbuf2[--index2];
					cbuf1[index1] = tmp1 + tmp2;
					cbuf2[index2] = ((tmp1 << 11) | (tmp1 >> 21)) ^ tmp2;
					if ( !index1 ) index1 = L1;
					if ( !index2 ) index2 = L2;
					return tmp1 + tmp2;
				}
				std::string dual_cbuf::get_name() const {return "dual_cbuf";}
				void dual_cbuf::walk_state(StateWalkingObject *walker) {
					walker->handle(index1);
					walker->handle(index2);
					for (int i = 0; i < L1; i++) walker->handle(cbuf1[i]);
					for (int i = 0; i < L2; i++) walker->handle(cbuf2[i]);
					if (index1 > L1) index1 %= L1;
					if (!index1) index1 = L1;
					if (index2 > L2) index2 %= L2;
					if (!index2) index2 = L2;
				}
				Uint32 dual_cbuf_accum::raw32() {
					Uint32 tmp1, tmp2;
					tmp1 = cbuf1[--index1];
					tmp2 = cbuf2[--index2];
					accum = ((accum << 11) | (accum >> 21)) + tmp1;
					cbuf1[index1] = tmp1 ^ tmp2;
					cbuf2[index2] = accum;
					if ( !index1 ) index1 = L1;
					if ( !index2 ) index2 = L2;
					return accum;
				}
				std::string dual_cbuf_accum::get_name() const {return "dual_cbuf_accum";}
				void dual_cbuf_accum::walk_state(StateWalkingObject *walker) {
					walker->handle(index1);
					walker->handle(index2);
					walker->handle(accum);
					for (int i = 0; i < L1; i++) walker->handle(cbuf1[i]);
					for (int i = 0; i < L2; i++) walker->handle(cbuf2[i]);
					if (index1 > L1) index1 %= L1;
					if (index2 > L2) index2 %= L2;
					if ( !index1 ) index1 = L1;
					if ( !index2 ) index2 = L2;
				}


				Uint32 ranrot32::raw32() {
					if (position) return buffer[--position];
					for (unsigned long i = 0; i < LAG2; i++) {
						buffer[i] = 
							((buffer[i+LAG1-LAG1] << ROT1) | (buffer[i+LAG1-LAG1] >> (sizeof(buffer[0])*8-ROT1))) +
							((buffer[i+LAG1-LAG2] << ROT2) | (buffer[i+LAG1-LAG2] >> (sizeof(buffer[0])*8-ROT2)));
					}
					for (unsigned long i = LAG2; i < LAG1; i++) {
						buffer[i] = 
							((buffer[i-   0] << ROT1) | (buffer[i-   0] >> (sizeof(buffer[0])*8-ROT1))) +
							((buffer[i-LAG2] << ROT2) | (buffer[i-LAG2] >> (sizeof(buffer[0])*8-ROT2)));
					}
					position = LAG1;
					return buffer[--position];
				}
				std::string ranrot32::get_name() const {return "ranrot32";}
				void ranrot32::walk_state(StateWalkingObject *walker) {
					walker->handle(position);
					for (int i = 0; i < LAG1; i++) walker->handle(buffer[i]);
					if (position >= LAG1) position %= LAG1;
				}

				Uint16 fibmul16of32::raw16() {
					if (position) return Uint16(buffer[--position] >> 16);
					for (unsigned long i = 0; i < LAG2; i++) {
						buffer[i] = buffer[i+LAG1-LAG1] * buffer[i+LAG1-LAG2];
					}
					for (unsigned long i = LAG2; i < LAG1; i++) {
						buffer[i] = buffer[i] * buffer[i-LAG2];
					}
					position = LAG1;
					return Uint16(buffer[--position] >> 16);
				}
				std::string fibmul16of32::get_name() const {return "fibmul16of32";}
				void fibmul16of32::walk_state(StateWalkingObject *walker) {
					walker->handle(position);
					for (int i = 0; i < LAG1; i++) walker->handle(buffer[i]);
					if (position >= LAG1) position %= LAG1;
					for (int i = 0; i < LAG1; i++) buffer[i] |= 1;
				}
				Uint32 fibmul32of64::raw32() {
					if (position) return Uint32(buffer[--position] >> 32);
					for (unsigned long i = 0; i < LAG2; i++) {
						buffer[i] = buffer[i+LAG1-LAG1] * buffer[i+LAG1-LAG2];
					}
					for (unsigned long i = LAG2; i < LAG1; i++) {
						buffer[i] = buffer[i] * buffer[i-LAG2];
					}
					position = LAG1;
					return Uint32(buffer[--position] >> 32);
				}
				std::string fibmul32of64::get_name() const {return "fibmul32of64";}
				void fibmul32of64::walk_state(StateWalkingObject *walker) {
					walker->handle(position);
					for (int i = 0; i < LAG1; i++) walker->handle(buffer[i]);
					if (position >= LAG1) position %= LAG1;
					for (int i = 0; i < LAG1; i++) buffer[i] |= 1;
				}



				Uint32 ranrot3tap32::func(Uint32 a, Uint32 b, Uint32 c) {
//					return rotate(a, 3) + rotate(b, 17) + rotate(c, 9);
//					return (rotate(a, 0) * 293) ^ rotate(b, 17) ^ rotate(c, 9);// 33 @ 7/5
//					return (a ^ rotate(b, 9)) + c;// >40 @ 17/9, 34 @ 7/5, 35 @ 8/5, 35 @ 9/7, 38 @ 11/7
//					return (a ^ rotate(b, 1)) + c;// 33 @ 7/5
//					return (a ^ rotate(b, 2)) + c;// 34 @ 7/5
//					return (a ^ rotate(b, 3)) + c;// 34 @ 7/5
//					return (a ^ b) + rotate(c,9);// 34 @ 7/5, 38 @11/7
//					return (a ^ rotate(b,13)) + rotate(c,9);// 34 @ 7/5, 38 @11/7
					return rotate(a, ROT1) + rotate(b, ROT2) + rotate(c, ROT3);//30 @ 7/5, 36 @ 11/7, 36 @ 17/9
				}
				Uint32 ranrot3tap32::raw32() {
					if (position) return buffer[--position];
					Uint32 old = buffer[LAG1-1];
					for (unsigned long i = 0; i < LAG2; i++) {
						buffer[i] = old = func(buffer[i+LAG1-LAG1], buffer[i+LAG1-LAG2], old);
					}
					for (unsigned long i = LAG2; i < LAG1; i++) {
						buffer[i] = old = func(buffer[i], buffer[i-LAG2], old);
					}
					position = LAG1;
					return buffer[--position];
				}
				std::string ranrot3tap32::get_name() const {return "ranrot3tap32";}
				void ranrot3tap32::walk_state(StateWalkingObject *walker) {
					walker->handle(position);
					for (int i = 0; i < LAG1; i++) walker->handle(buffer[i]);
					if (position >= LAG1) position %= LAG1;
				}

				Uint32 mt19937_unhashed::raw32() {
					return implementation.untempered_raw32();
				}
				std::string mt19937_unhashed::get_name() const {return "mt19937_unhashed";}
				void mt19937_unhashed::walk_state(StateWalkingObject *walker) {
					implementation.walk_state(walker);
				}
			}
		}
	}
}
