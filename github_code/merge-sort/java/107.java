import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MainPanel extends JPanel implements ActionListener {

    private static JButton _selectionSortButton;
    private static JLabel _selectionSortTime;
    private static JLabel _selectionComparisons;
    private static JButton _mergeSortButton;
    private static JLabel _mergeSortTime;
    private static JLabel _mergeComparisons;

    public MainPanel() {

        _selectionSortButton = new JButton("Selection Sort");
        _selectionSortTime = new JLabel();
        _selectionComparisons = new JLabel();
        _mergeSortButton = new JButton("Merge Sort");
        _mergeSortTime = new JLabel();
        _mergeComparisons = new JLabel();

        _selectionSortButton.setFont(new Font("Arial", Font.PLAIN, 22));
        _selectionSortTime.setFont(new Font("Arial", Font.PLAIN, 18));
        _selectionComparisons.setFont(new Font("Arial", Font.PLAIN, 18));
        _mergeSortButton.setFont(new Font("Arial", Font.PLAIN, 22));
        _mergeSortTime.setFont(new Font("Arial", Font.PLAIN, 18));
        _mergeComparisons.setFont(new Font("Arial", Font.PLAIN, 18));

        _selectionSortButton.setPreferredSize(new Dimension(250, _selectionSortButton.getHeight()));

        _selectionSortButton.addActionListener(this);
        _mergeSortButton.addActionListener(this);

        setLayout(new GridLayout(2, 2));

        add(_selectionSortButton);
        add(_selectionSortTime);
        add(_selectionComparisons);
        add(_mergeSortButton);
        add(_mergeSortTime);
        add(_mergeComparisons);

        updateText();
    }

    // update JLabel text to show number status, sort time, and number of comparisons
    public static void updateText() {
        Thread thread = new Thread(() -> {
            while (true) {
                _selectionSortTime.setText("Sort Time: " + SelectionSorter.selectionSortTime);
                _selectionComparisons.setText(String.format("Comparisons: %,d", SelectionSorter.selectionSortComparisons));
                _mergeSortTime.setText("Sort Time: " + MergeSorter.mergeSortTime);
                _mergeComparisons.setText(String.format("Comparisons: %,d", MergeSorter.mergeSortComparisons));
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
        thread.start();
    }

    // enable respective button (called after sorting complete)
    public static void enableSelectionSortButton() {
        _selectionSortButton.setEnabled(true);
    }

    public static void enableMergeSortButton() {
        _mergeSortButton.setEnabled(true);
    }

    // get which button was clicked; disable button while sorting; call respective sort
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == _selectionSortButton) {
            _selectionSortButton.setEnabled(false);
            SelectionSorter.performSelectionSort();
        } else if (e.getSource() == _mergeSortButton) {
            _mergeSortButton.setEnabled(false);
            MergeSorter.performMergeSort();
        }
    }
}
