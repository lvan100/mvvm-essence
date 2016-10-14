package com.mvvm.notify;

/**
 * 值变化通知接口
 *
 * @param <T>
 */
public interface INotifyValueChanged<T> {

    /**
     * 添加值变化监视器
     */
    void addValueChanged(OnValueChanged<T> valueChanged);

    /**
     * 移除值变化监视器
     */
    void removeValueChanged(OnValueChanged<T> valueChanged);

}
