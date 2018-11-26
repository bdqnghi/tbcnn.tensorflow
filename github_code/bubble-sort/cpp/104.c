/*
 * factorial.cpp
 *
 *  Created on: May 15, 2017
 *      Author: zollder
 */

template <typename NodeSequence>
class BubbleSort {

	public:
		/**
		 * Rank-based bubble-sort implementation.
		 */
		void bubbleSort1(NodeSequence& seq) {
			int n = seq.size();
			for (int i = 0; i < n; i++) {
				for (int j = 1; j < n-i; j++) {
					if (seq.getValueAtRank(j-1) > seq.getValueAtRank(j)) {
						seq.swap(seq.getPositionByRank(j), seq.getPositionByRank(j-1));
					}
				}
			}
		}

		/**
		 * Position-based bubble-sort implementation.
		 */
		void bubbleSort2(NodeSequence& seq) {
			// use typename to instruct the compiler about member type access
			typedef typename NodeSequence::Position Position;
			int n = seq.size();
			for (int i = 0; i < n; i++) {
				Position preceding = seq.first();
				for (int j = 1; j < n-i; j++) {
					Position succeeding = seq.after(preceding);
					if (succeeding.getValue() < preceding.getValue()) {
						seq.swap(preceding, succeeding);
					}
					preceding = succeeding;
				}
			}
		}
};
