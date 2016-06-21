package bean;

import android.content.Context;
import android.support.v7.widget.GridLayoutManager;
import android.support.v7.widget.RecyclerView;

/**
 * Created by zuheng.lv on 2016/6/9.
 */
public class GLayoutManager extends GridLayoutManager {


public GLayoutManager(Context context, int spanCount) {
        super(context, spanCount);
        }

@Override
public void onLayoutChildren(RecyclerView.Recycler recycler, RecyclerView.State state) {
        try {
        super.onLayoutChildren(recycler, state);
        } catch (IndexOutOfBoundsException e) {

        }
        }
        }