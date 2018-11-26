/*
 * UniCrypt
 *
 *  UniCrypt(tm): Cryptographical framework allowing the implementation of cryptographic protocols e.g. e-voting
 *  Copyright (c) 2016 Bern University of Applied Sciences (BFH), Research Institute for
 *  Security in the Information Society (RISIS), E-Voting Group (EVG)
 *  Quellgasse 21, CH-2501 Biel, Switzerland
 *
 *  Licensed under Dual License consisting of:
 *  1. GNU Affero General Public License (AGPL) v3
 *  and
 *  2. Commercial license
 *
 *
 *  1. This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Affero General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Affero General Public License for more details.
 *
 *   You should have received a copy of the GNU Affero General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 *  2. Licensees holding valid commercial licenses for UniCrypt may use this file in
 *   accordance with the commercial license agreement provided with the
 *   Software or, alternatively, in accordance with the terms contained in
 *   a written agreement between you and Bern University of Applied Sciences (BFH), Research Institute for
 *   Security in the Information Society (RISIS), E-Voting Group (EVG)
 *   Quellgasse 21, CH-2501 Biel, Switzerland.
 *
 *
 *   For further information contact <e-mail: unicrypt@bfh.ch>
 *
 *
 * Redistributions of files must retain the above copyright notice.
 */
package ch.bfh.unicrypt.helper.converter.classes.string;

import ch.bfh.unicrypt.helper.converter.abstracts.AbstractStringConverter;

/**
 * Instance of this class convert Java strings into Java strings. There are two operating modes, one in which the
 * strings remain unchanged and one in which they are reversed.
 * <p>
 * @author R. Haenni
 * @version 2.0
 */
public class StringToString
	   extends AbstractStringConverter<String> {
	private static final long serialVersionUID = 1L;

	private final boolean reverse;

	protected StringToString(boolean reverse) {
		super(String.class);
		this.reverse = reverse;
	}

	/**
	 * Returns a new default {@link StringToString} converter, which leaves the strings unchanged.
	 * <p>
	 * @return The default converter
	 */
	public static StringToString getInstance() {
		return StringToString.getInstance(false);
	}

	/**
	 * Returns a new {@link StringToString} converter for a given flag {@code reverse} indicating if the input strings
	 * are reversed.
	 * <p>
	 * @param reverse The flag indicating if the input strings are reversed
	 * @return The new converter
	 */
	public static StringToString getInstance(boolean reverse) {
		return new StringToString(reverse);
	}

	@Override
	protected String abstractConvert(String string) {
		if (this.reverse) {
			return new StringBuffer(string).reverse().toString();
		}
		return string;
	}

	@Override
	protected String abstractReconvert(String string) {
		if (this.reverse) {
			return new StringBuffer(string).reverse().toString();
		}
		return string;
	}

}
