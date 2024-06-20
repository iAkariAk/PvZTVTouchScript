package com.fairy.tv.script;

import android.graphics.Color;
import android.graphics.Typeface;
import android.view.ViewGroup;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.google.android.material.textview.MaterialTextView;

import java.util.List;

public class LogBufferItemAdapter extends RecyclerView.Adapter<LogBufferItemAdapter.MyHolder> {
    private final List<LogMessage> logMessageList;

    public LogBufferItemAdapter(List<LogMessage> logMessageList) {
        this.logMessageList = logMessageList;
    }

    @NonNull
    @Override
    public MyHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        return new MyHolder(new MaterialTextView(parent.getContext()));
    }

    @Override
    public void onBindViewHolder(@NonNull MyHolder holder, int position) {
        var logMessage = logMessageList.get(position);
        holder.itemView.setText(logMessage.message());
        holder.itemView.setTextColor(switch (logMessage.level()) {
            case Debug -> Color.BLUE;
            case Info -> Color.GREEN;
            case Error -> Color.RED;
            case Warning -> Color.YELLOW;
        });
    }

    @Override
    public int getItemCount() {
        return logMessageList.size();
    }

    public static class MyHolder extends RecyclerView.ViewHolder {
        public final MaterialTextView itemView;

        public MyHolder(@NonNull MaterialTextView itemView) {
            super(itemView);
            this.itemView = itemView;
            itemView.setTypeface(Typeface.MONOSPACE);
            itemView.setTextSize(13);

        }
    }
}
