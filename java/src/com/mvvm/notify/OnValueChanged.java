package com.mvvm.notify;

/**
 * 值变化响应接口
 *
 * @param <T>
 */
public interface OnValueChanged<T> {

    void onValueChanged(T newValue);

}
