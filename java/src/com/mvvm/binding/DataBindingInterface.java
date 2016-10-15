package com.mvvm.binding;

import com.mvvm.notify.IPropertyChangedSupport;

/**
 * 数据绑定接口。
 *
 * @param <T>
 */
interface DataBindingInterface<T> {

    /**
     * 获取数据绑定的类型
     */
    BindingType getType();

    /**
     * 设置数据绑定的类型
     */
    void setType(BindingType type);

    /**
     * 获取源绑定对象，要求实现 IPropertyChangedSupport 接口。
     */
    IPropertyChangedSupport getSource();

    /**
     * 设置源绑定对象
     *
     * @param source 源绑定对象，要求实现 IPropertyChangedSupport 接口。
     */
    void setSource(IPropertyChangedSupport source);

    /**
     * 获取源绑定对象的绑定属性
     */
    String getSourcePropertyName();

    /**
     * 设置源绑定对象的绑定属性
     */
    void setSourcePropertyName(String propertyName);

    /**
     * 获取目标绑定对象，必须是 DependencyObject 对象。
     */
    DependencyObject<T> getTarget();

    /**
     * 设置目标绑定对象，必须是 DependencyObject 对象。
     */
    void setTarget(DependencyObject<T> target);

}
