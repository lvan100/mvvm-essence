package com.mvvm.model;

import com.mvvm.notify.IPropertyChangedSupport;

/**
 * 数据模型，操作数据的存储和读取，当修改数据时通知其变化。
 *
 * @param <T>
 */
interface ModelInterface<T> extends IPropertyChangedSupport {

    /**
     * 获取数据模型的值
     */
    T getValue();

    /**
     * 设置数据模型的值
     */
    void setValue(T value);

    /**
     * 是否只读
     */
    boolean isReadOnly();

    /**
     * 设置是否只读
     */
    void setReadOnly(boolean readOnly);

}
