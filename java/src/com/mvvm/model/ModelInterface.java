package com.mvvm.model;

import com.mvvm.notify.INotifyValueChanged;

/**
 * 数据模型，操作数据的存储和读取，当修改数据时通知其变化。
 *
 * @param <T>
 */
interface ModelInterface<T> extends INotifyValueChanged<T> {

    /**
     * 刷新数据模型
     */
    void refresh();

    /**
     * 获取数据模型的值
     */
    T getValue();

    /**
     * 设置数据模型的值
     *
     * @throws IllegalAccessException 只读模式下调用此方法会抛出此异常
     */
    void setValue(T value) throws IllegalAccessException;

    /**
     * 是否只读
     */
    boolean isReadOnly();

    /**
     * 设置是否只读
     */
    void setReadOnly(boolean readOnly);

}
