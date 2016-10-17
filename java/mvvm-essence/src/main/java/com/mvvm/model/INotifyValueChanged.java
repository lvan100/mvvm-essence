package com.mvvm.model;

/**
 * 数据模型值变化通知接口
 */
public interface INotifyValueChanged {

    /**
     * 响应数据模型值变化事件
     *
     * @param model 发生值变化的数据模型
     */
    void onValueChanged(Model model);

}
