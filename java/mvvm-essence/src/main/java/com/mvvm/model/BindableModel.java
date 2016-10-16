package com.mvvm.model;

/**
 * 可绑定的数据模型
 */
public interface BindableModel<T> {

    /**
     * 获取数据模型的值
     */
    T getValue();

    /**
     * 设置数据模型的值
     */
    void setValue(Object value);

    /**
     * 绑定其他的数据模型
     */
    void bindModel(BindableModel model);

    /**
     * 和已绑定的数据模型解绑
     */
    void unbindModel(BindableModel model);

    /**
     * 响应其他数据模型的值变化事件
     */
    void onValueChanged(BindableModel source);

}
