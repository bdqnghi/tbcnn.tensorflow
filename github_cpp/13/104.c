

template <typename NodeSequence>
class BubbleSort {

	public:
		
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

		
		void bubbleSort2(NodeSequence& seq) {
			
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
