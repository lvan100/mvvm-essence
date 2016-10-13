package com.mvvm.model;

import com.mvvm.notify.NotifyValueChanged;

/**
 * 数据模型的实现
 */
public class Model<T> extends NotifyValueChanged<T> implements ModelInterface<T> {

    /**
     * 客户端值
     */
    private T value;

    /**
     * 是否只能读取
     */
    private boolean readOnly = false;

    public Model(T value) {
        this.value = value;
    }

    public Model(boolean readOnly, T value) {
        this.readOnly = readOnly;
        this.value = value;
    }

    @Override
    public void refresh() {
        System.out.println(this.toString() + ":refresh");
        notifyValueChanged(value);
    }

    @Override
    public T getValue() {
        System.out.println(this.toString() + ":getValue=" + value);
        return value;
    }

    @Override
    public void setValue(T value) throws IllegalAccessException {
        if (readOnly) {
            throw new IllegalAccessException();
        }

        if (this.value == value) {
            System.out.println(this.toString() + ":value is equal");
            return; /*值相等的时候什么也不做，很重要！*/
        }

        System.out.println(this.toString() + ":setValue=" + this.value + "->" + value);
        this.value = value;

        // 通知其值已经发生变化
        notifyValueChanged(value);
    }

    @Override
    public boolean isReadOnly() {
        return readOnly;
    }

    @Override
    public void setReadOnly(boolean readOnly) {
        this.readOnly = readOnly;
    }

}
