package cn.intersteller.darkintersteller.custview;

import android.animation.Animator;
import android.animation.ValueAnimator;
import android.content.Context;
import android.graphics.Canvas;
import android.util.AttributeSet;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import java.util.Arrays;

import cn.intersteller.darkintersteller.R;

public class BubbleSortViewByAddView extends ViewGroup {
    private ValueAnimator valueAnimator;
    private int bubble_sort_view_child_width;
    private int bubble_sort_view_child_height;
    private int bubble_sort_view_child_margin;
    private int bubble_sort_view_arrow_height;
    private int h;
    private int i;

    public BubbleSortViewByAddView(Context context) {
        this(context, null);
    }

    public BubbleSortViewByAddView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);

    }

    public BubbleSortViewByAddView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
        h = -1;
        i = -1;
        init1();
    }

    private void init1() {
        setWillNotDraw(false);
        bubble_sort_view_child_width = getResources().getDimensionPixelSize(R.dimen.bubble_sort_view_child_width);
        bubble_sort_view_child_height = getResources().getDimensionPixelOffset(R.dimen.bubble_sort_view_child_height);
        bubble_sort_view_child_margin = getResources().getDimensionPixelOffset(R.dimen.bubble_sort_view_child_margin);
        bubble_sort_view_arrow_height = getResources().getDimensionPixelOffset(R.dimen.bubble_sort_view_arrow_height);
        valueAnimator = ValueAnimator.ofFloat(new float[]{0.0f, 1.0f});
        valueAnimator.setDuration(1000);
        valueAnimator.addUpdateListener(new MyBSViewAnimUpdateListener(this));
        valueAnimator.addListener(new MyBSAnimatorListener(this));

    }

    public void startBond(int[] array) {
        removeAllViews();
        bundTextViewWhitNum(array);
    }

    private void bundTextViewWhitNum(int[] array) {
        Log.i("deng", "array[] = " + Arrays.toString(array));
        for (int i = 0; i < array.length; i++) {
            createBubbleTextView(array[i]);
        }
    }

    public void createBubbleTextView(int num) {
//        Log.i("deng","num = "+num);
        TextView textView = (TextView) LayoutInflater.from(getContext()).inflate(R.layout.include_bubble_sort_child, null);
        textView.setText(String.valueOf(num));
        textView.setLayoutParams(new LayoutParams(bubble_sort_view_child_width, bubble_sort_view_child_height));
        addView(textView);
    }


    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        int childCount = getChildCount();
        if (childCount == 0) {
//            Log.i("deng", "childcount =  0");
            super.onMeasure(widthMeasureSpec, heightMeasureSpec);
            return;
        }
//        Log.i("deng", "childcount =  " + childCount);
        measureChildren(widthMeasureSpec, heightMeasureSpec);
        setMeasuredDimension(((childCount - 1) *
                        bubble_sort_view_child_margin) + (bubble_sort_view_child_width * childCount),
                bubble_sort_view_arrow_height + bubble_sort_view_child_height);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
    }

    @Override
    protected void onLayout(boolean changed, int l, int t, int r, int b) {
        int childCount = getChildCount();
        int conuted = 0;
//        int i6 = bubble_sort_view_arrow_height;
        int i7 = 0;
        while (conuted < childCount) {
            View childAt = getChildAt(conuted);
            int i8 = (int) (((float) ((l - this.h) * (bubble_sort_view_child_width + bubble_sort_view_child_margin))) * 1);
            if (conuted == this.h) {
                childAt.layout(i7 + i8, bubble_sort_view_arrow_height, (i8 + i7) + bubble_sort_view_child_width, bubble_sort_view_child_height + bubble_sort_view_arrow_height);
            } else if (conuted == this.i) {
                childAt.layout(i7 - i8, bubble_sort_view_arrow_height, (this.bubble_sort_view_child_width + i7) - i8, this.bubble_sort_view_child_height + bubble_sort_view_arrow_height);
            } else {
                childAt.layout(i7, bubble_sort_view_arrow_height, this.bubble_sort_view_child_width + i7, this.bubble_sort_view_child_height + bubble_sort_view_arrow_height);
            }
            i7 += this.bubble_sort_view_child_width + this.bubble_sort_view_child_margin;
            conuted++;
        }
    }

    class MyBSViewAnimUpdateListener implements ValueAnimator.AnimatorUpdateListener {
        final BubbleSortViewByAddView bubbleSortView;

        MyBSViewAnimUpdateListener(BubbleSortViewByAddView bubbleSortView) {
            this.bubbleSortView = bubbleSortView;
        }

        public void onAnimationUpdate(ValueAnimator valueAnimator) {
            float v = ((Float) valueAnimator.getAnimatedValue()).floatValue();
            this.bubbleSortView.requestLayout();
        }
    }

    class MyBSAnimatorListener implements Animator.AnimatorListener {
        final BubbleSortViewByAddView bubbleSortView;

        MyBSAnimatorListener(BubbleSortViewByAddView bubbleSortView) {
            this.bubbleSortView = bubbleSortView;
        }


        @Override
        public void onAnimationStart(Animator animation) {

        }

        @Override
        public void onAnimationEnd(Animator animation) {

        }

        @Override
        public void onAnimationCancel(Animator animation) {

        }

        @Override
        public void onAnimationRepeat(Animator animation) {

        }
    }
}
