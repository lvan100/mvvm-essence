package com.mvvm.view;

import com.mvvm.binding.DataBinding;

/**
 * 视图控件接口
 */
public interface View {

    /**
     * 获取视图控件ID
     */
    String getId();

    /**
     * 设置视图控件ID
     */
    void setId(String id);

    /**
     * 设置数据绑定对象
     *
     * @param propertyName 待绑定的属性
     * @param binding      数据绑定对象
     */
    void setDataBinding(String propertyName, DataBinding<?> binding);

    /**
     * 刷新控件视图
     */
    void show();

}
