package adapter;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.hitek.serial.R;

import java.util.List;

import bean.AlarmRecordData;
import bean.HistoryData;

/**
 * Created by zuheng.lv on 2016/6/11.
 */
public class AlarmRecordRecycleViewAdapter extends RecyclerView.Adapter<AlarmRecordRecycleViewAdapter.ViewHolder>{


    private List<AlarmRecordData> list;
    private Context context;
    public AlarmRecordRecycleViewAdapter(Context context , List<AlarmRecordData> list){
        super();
        this.context = context;
        this.list = list;
    }
    @Override
    public AlarmRecordRecycleViewAdapter.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(context).inflate(R.layout.alarmrecord_recycleview_layout,null);
       ViewHolder holder = new ViewHolder(view);
        return holder;
    }

    @Override
    public void onBindViewHolder(AlarmRecordRecycleViewAdapter.ViewHolder holder, int position) {
        holder.record_date.setText(list.get(position).getDate());
        holder.record_time.setText(list.get(position).getTime());
        holder.record_type.setText(list.get(position).getType());
        holder.record_data.setText(list.get(position).getData());
        holder.record_explain.setText(list.get(position).getExplain());
        holder.record_cancel.setText(list.get(position).getCancel());
    }

    @Override
    public int getItemCount() {
        return list.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        TextView record_date;
        TextView record_time;
        TextView record_type;
        TextView record_data;
        TextView record_explain;
        TextView record_cancel;
        public ViewHolder(View itemView) {
            super(itemView);
            record_date = (TextView) itemView.findViewById(R.id.record_date);
            record_time = (TextView) itemView.findViewById(R.id.record_time);
            record_type = (TextView) itemView.findViewById(R.id.record_type);
            record_data = (TextView) itemView.findViewById(R.id.record_data);
            record_explain = (TextView) itemView.findViewById(R.id.record_explain);
            record_cancel = (TextView) itemView.findViewById(R.id.record_cancel);
        }
    }
}
