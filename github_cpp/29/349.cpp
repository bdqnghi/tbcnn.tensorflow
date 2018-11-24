/*######     Copyright (c) 1997-2013 Ufasoft  http://ufasoft.com  mailto:support@ufasoft.com,  Sergey Pavlov  mailto:dev@ufasoft.com #######################################
#                                                                                                                                                                          #
# This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;  #
# either version 3, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      #
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU #
# General Public License along with this program; If not, see <http://www.gnu.org/licenses/>                                                                               #
##########################################################################################################################################################################*/

#include <el/ext.h>

#include "bloom-filter.h"

namespace Ext { namespace Crypto {

bool BloomFilter::Contains(const ConstBuf& key) const {
	for (int i=0; i<HashNum; ++i)
		if (!Bitset[Hash(key, i)])
			return false;
	return true;
}

void BloomFilter::Insert(const ConstBuf& key) {
	for (int i=0; i<HashNum; ++i)
		Bitset.set(Hash(key, i));
}




}} // Ext::Crypto::


