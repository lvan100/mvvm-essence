package com.mvvm.binding;

import com.mvvm.model.Model;
import com.mvvm.notify.INotifyValueChanged;

/**
 * 数据绑定接口。
 *
 * @param <T>
 */
interface DataBindingInterface<T> extends INotifyValueChanged<T> {

    /**
     * 获取数据绑定的类型
     */
    BindingType getType();

    /**
     * 设置数据绑定的类型
     */
    DataBindingInterface<T> setType(BindingType type);

    /**
     * 修改源绑定对象的值
     *
     * @throws IllegalAccessException 单向绑定时调用此方法会抛出该异常。
     */
    void setSourceValue(T value) throws IllegalAccessException;

    /**
     * 修改目标绑定对象的值
     */
    void setTargetValue(T value);

    /**
     * 获取源绑定对象
     */
    Model<T> getSource();

    /**
     * 设置源绑定对象
     */
    DataBindingInterface<T> setSource(Model<T> source);

    /**
     * 获取目标绑定对象
     */
    Model<T> getTarget();

    /**
     * 设置目标绑定对象
     */
    DataBindingInterface<T> setTarget(Model<T> target);

}
