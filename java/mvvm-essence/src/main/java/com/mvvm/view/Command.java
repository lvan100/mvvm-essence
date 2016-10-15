package com.mvvm.view;

/**
 * 命令事件接口，用于连接View层和ViewModel层。
 */
public interface Command {

    void onCommand(View source);

}
