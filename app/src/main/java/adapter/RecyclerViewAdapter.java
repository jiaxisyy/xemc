package adapter;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.hitek.serial.R;

import java.util.List;

import bean.HistoryData;

/**
 * Created by zuheng.lv on 2016/6/3.
 */
public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder> {

    private List<HistoryData> list;
    private Context context;
    public RecyclerViewAdapter (Context context,List<HistoryData> list){
        super();
        this.list =list;
        this.context = context;
    }
    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.history_recycle_layout,parent,false);
        ViewHolder viewHolder = new ViewHolder(view);
        return viewHolder;
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position) {
        holder.recycle_date.setText(list.get(position).getDate());
        holder.recycle_time.setText(list.get(position).getTime());
        holder.recycle_pressure.setText(list.get(position).getPressure());
        holder.recycle_concentration.setText(list.get(position).getConcentration());
        holder.recycle_flow.setText(list.get(position).getFlow());
        holder.recycle_totalflow.setText(list.get(position).getTotalflow());
    }

    @Override
    public int getItemCount() {
        return list.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
         TextView recycle_date;
         TextView recycle_time;
         TextView recycle_pressure;
         TextView recycle_concentration;
         TextView recycle_flow;
         TextView recycle_totalflow;
         ViewHolder(View itemView) {
            super(itemView);
            recycle_date = (TextView)itemView.findViewById(R.id.recycle_date);
            recycle_time = (TextView)itemView.findViewById(R.id.recycle_time);
            recycle_pressure = (TextView)itemView.findViewById(R.id.recycle_pressure);
            recycle_concentration = (TextView)itemView.findViewById(R.id.recycle_concentration);
            recycle_flow = (TextView)itemView.findViewById(R.id.recycle_flow);
            recycle_totalflow = (TextView)itemView.findViewById(R.id.recycle_totalflow);
        }
    }
}
